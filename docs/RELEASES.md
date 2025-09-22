# 📦 Release Documentation

## 🚀 Latest Release - v1.0.0

**发布日期**: 2024年1月

### 📋 发布说明

这是智能农业植物生长监测系统的首个正式版本，提供完整的硬件固件和桌面应用程序。

### ✨ 主要特性

- ✅ **STM32F103ZET6固件**: 完整的传感器数据采集和处理功能
- ✅ **ESP32 WiFi模块**: 稳定的无线通信和TCP服务器
- ✅ **Qt桌面应用**: 实时数据监控和设备控制界面
- ✅ **多传感器支持**: 温湿度、土壤湿度、光照传感器
- ✅ **实时通信**: WiFi + TCP协议实现设备与PC端通信
- ✅ **数据可视化**: 图表展示历史数据和实时趋势

### 🎯 系统要求

#### 硬件要求
- STM32F103ZET6开发板
- ESP32开发板 (ESP32-C3推荐)
- 温湿度传感器 (DHT22/SHT30)
- 土壤湿度传感器
- 光照传感器 (可选)

#### 软件要求
- Windows 10/11, Linux Ubuntu 18.04+, 或 macOS 10.14+
- Qt 5.12+ (用于桌面应用)
- 串口驱动程序

### 📥 下载文件

#### 🔧 预编译固件 (推荐新手使用)

| 文件名 | 平台 | 大小 | 描述 | 下载链接 |
|--------|------|------|------|----------|
| `serial2_ADC.hex` | STM32F103ZET6 | ~45KB | 主控制器固件，包含传感器驱动和串口通信 | [⬇️ 下载](../assets/binaries/STM32/serial2_ADC.hex) |
| `AP_TCPServer.bin` | ESP32 | ~1.2MB | WiFi通信模块固件，实现TCP服务器功能 | [⬇️ 下载](../assets/binaries/ESP32/AP_TCPServer.bin) |
| `bootloader.bin` | ESP32 | ~25KB | ESP32引导程序，烧录时必需 | [⬇️ 下载](../assets/binaries/ESP32/bootloader.bin) |

#### 📱 桌面应用程序

| 平台 | 状态 | 说明 |
|------|------|------|
| Windows | 🔨 需要编译 | 请参考[编译指南](#编译指南) |
| Linux | 🔨 需要编译 | 请参考[编译指南](#编译指南) |
| macOS | 🔨 需要编译 | 请参考[编译指南](#编译指南) |

### 🛠️ 快速部署指南

#### 步骤1: 烧录STM32固件

```bash
# 方法1: 使用STM32CubeProgrammer (推荐)
# 1. 下载 serial2_ADC.hex 文件
# 2. 连接STM32开发板到电脑
# 3. 使用STM32CubeProgrammer打开hex文件并烧录

# 方法2: 使用命令行工具
STM32_Programmer_CLI -c port=SWD -w serial2_ADC.hex -v -rst
```

#### 步骤2: 烧录ESP32固件

```bash
# 安装esptool (如果还没有安装)
pip install esptool

# 下载固件文件到本地目录
# 然后执行烧录命令
esptool.py --chip esp32c3 --port COM3 --baud 460800 write_flash 0x0 bootloader.bin 0x10000 AP_TCPServer.bin

# Linux/macOS用户请替换COM3为对应的设备端口，如 /dev/ttyUSB0
```

#### 步骤3: 编译并运行Qt应用

```bash
# 克隆项目代码
git clone https://github.com/longzheng268/plant_monitor.git
cd plant_monitor/Qt/plant_monitor

# 编译应用
qmake plant_monitor.pro
make  # Linux/macOS
# Windows用户请使用 nmake 或在Qt Creator中打开项目编译
```

### ⚙️ 配置说明

#### WiFi连接配置

ESP32固件默认配置：
- **WiFi模式**: AP模式 (热点模式)
- **SSID**: `PlantMonitor_AP`
- **密码**: `12345678`
- **IP地址**: `192.168.4.1`
- **TCP端口**: `8080`

#### 自定义WiFi配置

如需连接到现有WiFi网络，请在ESP32源码中修改：
```c
// ESP-IDF/plant_monitor/main/wifi_config.h
#define WIFI_SSID "您的WiFi名称"
#define WIFI_PASS "您的WiFi密码"
```

#### Qt应用连接配置

在Qt应用中连接ESP32设备：
1. 启动Qt应用
2. 在设置中输入ESP32的IP地址 (默认: `192.168.4.1`)
3. 端口号: `8080`
4. 点击连接按钮

### 📊 功能测试

#### 硬件连接测试

1. **STM32状态指示**
   - 上电后LED应正常闪烁
   - 串口输出传感器数据 (波特率115200)

2. **ESP32连接测试**
   - WiFi热点 `PlantMonitor_AP` 应可见
   - 连接热点后可访问 `192.168.4.1`

3. **传感器数据测试**
   - 温湿度数据范围合理 (温度0-50°C，湿度20-90%)
   - 土壤湿度变化响应 (0-100%)

#### 软件功能测试

1. **Qt应用连接**
   - 应用启动正常，界面显示完整
   - 成功连接到ESP32设备
   - 实时接收传感器数据

2. **数据监控**
   - 图表正常更新
   - 历史数据保存
   - 报警功能测试

### ⚠️ 已知问题

1. **ESP32首次连接可能较慢** - 请耐心等待约30秒
2. **STM32温度传感器需要校准** - 可能需要根据实际环境调整校准参数
3. **Qt应用在高DPI显示器上可能存在界面缩放问题** - 建议设置系统缩放为100%

### 🔄 更新历史

- **v1.0.0** (2024-01-01): 初始发布版本
  - 完整的STM32和ESP32固件
  - Qt桌面监控应用
  - 基础传感器支持
  - WiFi通信功能

### 🆘 获取帮助

如果您在使用过程中遇到问题：

1. **查看故障排除指南**: [README.md#故障排除](../README.md#🔍-故障排除)
2. **提交Issue**: [GitHub Issues](https://github.com/longzheng268/plant_monitor/issues)
3. **查看详细文档**: [项目文档目录](../doc/)

### 📧 联系方式

- **项目维护者**: longzheng268
- **GitHub**: [https://github.com/longzheng268](https://github.com/longzheng268)
- **Email**: 通过GitHub Issue联系

---

## 🔮 下一版本预告 (v1.1.0)

计划新增功能：
- 🌐 Web界面支持
- 📱 移动端应用
- 🔔 微信/邮件报警通知
- 📈 更丰富的数据分析功能
- 🏠 多设备管理支持

---

<div align="center">
  <p><strong>感谢使用智能农业植物生长监测系统！</strong></p>
  <p>如果项目对您有帮助，请给个 ⭐ 支持我们的开发！</p>
</div>