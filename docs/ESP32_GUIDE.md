# 📡 ESP32 开发指南

## 📋 概述

ESP32模块负责WiFi连接和TCP通信服务，接收STM32发送的传感器数据并转发给Qt桌面应用程序。

## 🏗️ 硬件规格

### ESP32-C3 规格 (推荐)
- **CPU**: RISC-V 32位单核 @ 160MHz
- **WiFi**: 802.11 b/g/n (2.4GHz)
- **蓝牙**: Bluetooth 5.0 LE
- **Flash**: 4MB
- **SRAM**: 400KB
- **GPIO**: 22个数字I/O引脚

### 引脚配置
- **UART0**: USB调试端口
- **UART1**: 与STM32通信
  - TX: GPIO21
  - RX: GPIO20
- **状态LED**: GPIO2

## 🔨 开发环境搭建

### 软件要求
- ESP-IDF v4.4 或更高版本
- Python 3.7+
- Git

### ESP-IDF安装

#### Windows
```bash
# 下载ESP-IDF安装程序
# 从 https://dl.espressif.com/dl/esp-idf-tools-setup-2.9.exe
# 运行安装程序并按照向导完成安装
```

#### Linux/macOS
```bash
# 安装依赖
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

# 克隆ESP-IDF
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh esp32c3

# 设置环境变量
. $HOME/esp-idf/export.sh
```

### 项目配置

```bash
cd ESP-IDF/plant_monitor

# 设置目标芯片
idf.py set-target esp32c3

# 配置项目
idf.py menuconfig
```

## ⚙️ 项目配置

### WiFi配置

在 `menuconfig` 中配置：
```
Example Configuration --->
    [*] WiFi SSID: "PlantMonitor_AP"
    [*] WiFi Password: "12345678"
    [*] WiFi Mode: AP (Access Point)
    [*] Max Connections: 4
```

### TCP服务器配置
```
Example Configuration --->
    [*] TCP Server Port: 8080
    [*] Max Clients: 4
    [*] Keep Alive Enable: Yes
```

## 📝 代码结构

```
ESP-IDF/plant_monitor/
├── main/
│   ├── main.c                  # 主程序入口
│   ├── wifi_sta_init.h/.c      # WiFi初始化
│   ├── uart_init.h/.c          # UART初始化
│   ├── tcp_server.h/.c         # TCP服务器
│   └── CMakeLists.txt
├── components/                 # 自定义组件
├── build/                      # 编译输出
├── sdkconfig                   # 项目配置
├── CMakeLists.txt             # 主CMake文件
└── README.md                   # ESP32项目说明
```

## 🚀 主要功能模块

### 1. WiFi热点模式

```c
// wifi_sta_init.c
void wifi_init_softap(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .channel = WIFI_CHANNEL,
            .password = WIFI_PASS,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}
```

### 2. TCP服务器

```c
// tcp_server.c
static void tcp_server_task(void *pvParameters) {
    char addr_str[128];
    int addr_family = AF_INET;
    int ip_protocol = 0;
    int keepAlive = 1;
    int keepIdle = KEEPALIVE_IDLE;
    int keepInterval = KEEPALIVE_INTERVAL;
    int keepCount = KEEPALIVE_COUNT;

    struct sockaddr_storage dest_addr;
    struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
    dest_addr_ip4->sin_addr.s_addr = htonl(INADDR_ANY);
    dest_addr_ip4->sin_family = AF_INET;
    dest_addr_ip4->sin_port = htons(PORT);
    ip_protocol = IPPROTO_IP;

    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
    ESP_ERROR_CHECK(bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)));
    ESP_ERROR_CHECK(listen(listen_sock, 1));

    while (1) {
        struct sockaddr_storage source_addr;
        socklen_t addr_len = sizeof(source_addr);
        int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
        
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
            break;
        }

        // 设置keep-alive选项
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));

        // 处理客户端连接
        do_retransmit(sock);
        shutdown(sock, 0);
        close(sock);
    }
}
```

### 3. UART数据转发

```c
// uart_init.c
void uart_data_handler(void) {
    char data[128];
    int length = uart_read_bytes(ECHO_UART_PORT_NUM, data, sizeof(data)-1, 20 / portTICK_PERIOD_MS);
    
    if (length > 0) {
        data[length] = '\0';
        
        // 检查数据格式是否正确 (以'h'开头，以'~'结尾)
        if (data[0] == 'h' && data[length-1] == '~') {
            // 发送到所有连接的TCP客户端
            send_to_all_clients(data, length);
            ESP_LOGI(TAG, "Data forwarded: %s", data);
        }
    }
}
```

## 🔧 编译和烧录

### 编译项目

```bash
cd ESP-IDF/plant_monitor

# 清理之前的编译
idf.py clean

# 编译项目
idf.py build
```

### 烧录固件

```bash
# 查找串口设备
ls /dev/ttyUSB*  # Linux
ls /dev/cu.*     # macOS
# Windows通常是COM3, COM4等

# 烧录固件
idf.py -p /dev/ttyUSB0 flash

# 烧录并启动监视器
idf.py -p /dev/ttyUSB0 flash monitor
```

### 仅烧录监视器

```bash
idf.py -p /dev/ttyUSB0 monitor
```

## 📊 系统监控

### 串口输出示例

```
I (29) boot: ESP-IDF v4.4.2 2nd stage bootloader
I (29) boot: compile time 15:30:25
I (29) boot: chip revision: 3
I (33) boot.esp32c3: SPI Speed      : 80MHz
I (38) boot.esp32c3: SPI Mode       : DIO
I (42) boot.esp32c3: SPI Flash Size : 4MB
I (47) boot: Enabling RNG early entropy source...
I (52) boot: Partition Table:
I (56) boot: ## Label            Usage          Type ST Offset   Length
I (63) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (71) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (78) boot:  2 factory          factory app      00 00 00010000 00100000
I (86) boot: End of partition table
...
I (506) wifi:mode : softAP (7c:df:a1:40:02:95)
I (506) wifi softAP: wifi_init_softap finished. SSID:PlantMonitor_AP password:12345678 channel:1
I (516) tcp_server: Starting TCP server on port 8080
```

### 性能监控

```c
// 内存使用监控
void print_memory_info(void) {
    printf("Free heap: %d bytes\n", esp_get_free_heap_size());
    printf("Min free heap: %d bytes\n", esp_get_minimum_free_heap_size());
}

// WiFi状态监控
void print_wifi_info(void) {
    wifi_ap_record_t ap_info;
    if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK) {
        printf("Connected to SSID: %s\n", ap_info.ssid);
        printf("Signal strength: %d dBm\n", ap_info.rssi);
    }
}
```

## 🛠️ 故障排除

### 常见问题

#### 1. 编译错误
```bash
# 检查ESP-IDF版本
idf.py --version

# 重新安装工具链
cd $IDF_PATH
./install.sh esp32c3

# 清理并重新编译
idf.py fullclean
idf.py build
```

#### 2. 烧录失败
```bash
# 检查串口权限 (Linux)
sudo usermod -a -G dialout $USER
# 注销并重新登录

# 手动进入下载模式
# 按住BOOT按钮，按下RESET按钮，释放RESET，释放BOOT

# 降低烧录波特率
idf.py -p /dev/ttyUSB0 -b 115200 flash
```

#### 3. WiFi连接问题
```bash
# 检查WiFi配置
idf.py menuconfig

# 查看详细日志
idf.py monitor
# 按 Ctrl+] 退出监视器
```

#### 4. TCP连接问题
```c
// 增加调试日志
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"

// 检查防火墙设置
// 确保端口8080未被占用
```

### 性能优化

#### 降低功耗
```c
// 启用WiFi省电模式
esp_wifi_set_ps(WIFI_PS_MIN_MODEM);

// 降低CPU频率
esp_pm_config_esp32c3_t pm_config = {
    .max_freq_mhz = 80,
    .min_freq_mhz = 10,
    .light_sleep_enable = true
};
esp_pm_configure(&pm_config);
```

#### 优化内存使用
```c
// 减少任务栈大小
xTaskCreate(tcp_server_task, "tcp_server", 2048, NULL, 5, NULL);

// 使用静态内存分配
static StaticTask_t tcp_task_buffer;
static StackType_t tcp_task_stack[2048];
```

## 🔄 OTA更新 (未来功能)

### 配置OTA分区
```
# partitions.csv
# Name,   Type, SubType, Offset,  Size, Flags
nvs,      data, nvs,     0x9000,  0x6000,
phy_init, data, phy,     0xf000,  0x1000,
factory,  app,  factory, 0x10000, 0x100000,
ota_0,    app,  ota_0,   0x110000, 0x100000,
ota_1,    app,  ota_1,   0x210000, 0x100000,
```

### OTA更新代码框架
```c
#include "esp_ota_ops.h"
#include "esp_http_client.h"

esp_err_t perform_ota_update(const char* url) {
    esp_http_client_config_t config = {
        .url = url,
        .cert_pem = NULL,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    
    // 实现OTA更新逻辑
    // ...
    
    esp_http_client_cleanup(client);
    return ESP_OK;
}
```

## 📚 参考资料

- [ESP32-C3技术参考手册](https://www.espressif.com/sites/default/files/documentation/esp32-c3_technical_reference_manual_en.pdf)
- [ESP-IDF编程指南](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/)
- [ESP32-C3入门指南](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/get-started/)

---

## 🆘 技术支持

遇到问题时：
1. 查看串口监视器输出
2. 检查上述故障排除章节
3. 在GitHub Issues提交问题
4. 提供完整的错误日志信息