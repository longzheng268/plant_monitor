# 🔧 STM32F103ZET6 开发指南

## 📋 概述

STM32F103ZET6作为系统的主控制器，负责传感器数据采集、数据处理和与ESP32模块的串口通信。

## 🏗️ 硬件配置

### 微控制器规格
- **型号**: STM32F103ZET6
- **内核**: ARM Cortex-M3
- **主频**: 72MHz
- **Flash**: 512KB
- **SRAM**: 64KB
- **封装**: LQFP144

### 外设配置

#### ADC配置
- **ADC1**: 3通道配置
  - Channel 5 (PA5): 土壤湿度传感器
  - Channel 7 (PA7): 光照传感器
  - Channel TEMPSENSOR: 内部温度传感器
- **采样时间**: 55.5个周期
- **分辨率**: 12位

#### UART配置
- **USART1**: 与调试端口通信
  - 波特率: 115200
  - 数据位: 8
  - 停止位: 1
  - 奇偶校验: 无
- **USART3**: 与ESP32模块通信
  - 波特率: 115200
  - 数据位: 8
  - 停止位: 1
  - 奇偶校验: 无

#### GPIO配置
- **PA5**: ADC输入 - 土壤湿度传感器
- **PA7**: ADC输入 - 光照传感器
- **PA9/PA10**: USART1 TX/RX (调试)
- **PB10/PB11**: USART3 TX/RX (ESP32通信)

## 🔨 开发环境搭建

### 软件要求
- STM32CubeIDE 1.7.0+
- STM32CubeMX (集成在IDE中)
- STM32CubeProgrammer
- 或者 Keil MDK-ARM 5.29+

### 项目导入

1. **使用STM32CubeIDE** (推荐)
   ```bash
   # 打开STM32CubeIDE
   # File -> Import -> General -> Existing Projects into Workspace
   # 选择 STM32F103ZET6/plant_monitor 目录
   ```

2. **使用Keil MDK-ARM**
   ```bash
   # 打开Keil
   # Project -> Open Project
   # 选择 STM32F103ZET6/plant_monitor/MDK-ARM/serial2_ADC.uvprojx
   ```

### 编译配置

#### Debug配置
- **优化级别**: O0 (无优化)
- **调试信息**: 完整调试信息
- **断言**: 启用

#### Release配置
- **优化级别**: O2 (速度优化)
- **调试信息**: 最小调试信息
- **断言**: 禁用

## 📝 代码结构

```
STM32F103ZET6/plant_monitor/
├── Core/
│   ├── Inc/                     # 头文件
│   │   ├── main.h
│   │   ├── stm32f1xx_hal_conf.h
│   │   └── stm32f1xx_it.h
│   └── Src/                     # 源文件
│       ├── main.c               # 主程序
│       ├── stm32f1xx_hal_msp.c  # HAL MSP配置
│       ├── stm32f1xx_it.c       # 中断处理
│       └── system_stm32f1xx.c   # 系统配置
├── Drivers/                     # STM32 HAL驱动
├── MDK-ARM/                     # Keil项目文件
├── serial2_ADC.ioc             # STM32CubeMX配置文件
└── README.md                    # 本文档
```

## ⚡ 主要功能模块

### 1. 传感器数据采集

```c
// ADC初始化和数据读取
void ADC_Init(void) {
    // ADC配置代码
}

uint16_t Read_Sensor_Data(uint8_t channel) {
    // 读取指定通道的ADC值
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    return HAL_ADC_GetValue(&hadc1);
}
```

### 2. 数据处理和格式化

```c
typedef struct {
    float temperature;    // 温度 (°C)
    float humidity;       // 湿度 (%)
    float soil_moisture;  // 土壤湿度 (%)
    float light_intensity; // 光照强度 (Lux)
} SensorData_t;

void Process_Sensor_Data(SensorData_t* data) {
    // 数据处理和校准
    data->temperature = (ADC_Value * 3.3 / 4096 - 0.76) / 0.0025 + 25;
    data->soil_moisture = (ADC_Value * 100.0) / 4096;
    // ... 其他传感器数据处理
}
```

### 3. 串口通信协议

#### 数据格式
```
发送格式: h[温度],[湿度],[土壤湿度],[光照]~
示例: h25.6,65.2,78.3,450~
```

#### 通信函数
```c
void Send_Data_To_ESP32(SensorData_t* data) {
    char buffer[64];
    sprintf(buffer, "h%.1f,%.1f,%.1f,%.0f~", 
            data->temperature, 
            data->humidity, 
            data->soil_moisture, 
            data->light_intensity);
    HAL_UART_Transmit(&huart3, (uint8_t*)buffer, strlen(buffer), 1000);
}
```

## 🔧 编译和烧录

### 编译项目

#### 使用STM32CubeIDE
1. 右键项目 -> Build Project
2. 或使用快捷键 Ctrl+B

#### 使用Keil MDK-ARM
1. Project -> Build Target
2. 或使用快捷键 F7

### 烧录固件

#### 方法1: 使用ST-Link (推荐)
```bash
# 连接ST-Link调试器到STM32开发板
# 在IDE中点击 Run -> Debug 自动烧录和调试
```

#### 方法2: 使用STM32CubeProgrammer
```bash
# 连接ST-Link调试器
STM32_Programmer_CLI -c port=SWD -w serial2_ADC.hex -v -rst
```

#### 方法3: 使用串口烧录 (需要Boot引脚设置)
```bash
# 设置BOOT0=1, BOOT1=0，然后复位
# 使用串口烧录工具烧录bin文件
```

## 🛠️ 调试和测试

### 串口调试

#### 调试端口配置
- **端口**: USART1 (PA9/PA10)
- **波特率**: 115200
- **数据格式**: 8N1

#### 调试输出示例
```
System Initialize...
ADC Configuration Complete
UART Configuration Complete
Sensor Reading:
- Temperature: 25.6°C
- Humidity: 65.2%
- Soil Moisture: 78.3%
- Light: 450 Lux
Data sent to ESP32: h25.6,65.2,78.3,450~
```

### LED状态指示

| LED状态 | 含义 |
|---------|------|
| 常亮 | 系统正常运行 |
| 慢闪 (1Hz) | 正在采集数据 |
| 快闪 (5Hz) | 数据发送中 |
| 不亮 | 系统故障或未上电 |

### 常见问题排查

#### 问题1: ADC读数异常
```c
// 检查ADC校准
HAL_ADCEx_Calibration_Start(&hadc1);

// 检查参考电压
float vref = 3.3; // 应测量实际参考电压
```

#### 问题2: 串口通信失败
```c
// 检查波特率配置
// 检查引脚复用配置
// 检查串口线连接
```

#### 问题3: 系统复位或死机
```c
// 检查看门狗配置
// 检查中断优先级
// 检查栈溢出
```

## 📈 性能优化

### 功耗优化
- 使用睡眠模式降低功耗
- 按需启动外设
- 优化采样频率

### 数据处理优化
- 使用移动平均滤波
- 实现数据缓存机制
- 优化浮点运算

## 🔄 固件更新

### OTA更新 (计划功能)
- 通过ESP32接收新固件
- STM32自更新机制
- 固件校验和回滚

### 手动更新
1. 下载最新的 `.hex` 文件
2. 使用STM32CubeProgrammer烧录
3. 验证新功能

## 📚 参考资料

- [STM32F103ZET6数据手册](https://www.st.com/resource/en/datasheet/stm32f103ze.pdf)
- [STM32F1xx HAL库用户手册](https://www.st.com/resource/en/user_manual/dm00154093.pdf)
- [STM32CubeIDE用户指南](https://www.st.com/resource/en/user_manual/dm00629856.pdf)

---

## 🆘 技术支持

如有技术问题，请：
1. 查看上述故障排查部分
2. 在GitHub提交Issue
3. 加入社区讨论