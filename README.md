# 🌱 智能农业植物生长监测系统 (Plant Monitor System)

基于STM32F103ZET6的智能农业植物生长监测系统，集成了多种传感器和无线通信技术，实现植物生长环境的实时监测和远程控制。

## 📋 项目概述

本项目是一个完整的IoT农业监测解决方案，包含以下核心组件：

- **STM32F103ZET6主控板**: 负责传感器数据采集和处理
- **ESP32无线模块**: 提供WiFi连接和TCP通信
- **Qt桌面应用**: 实现数据可视化和远程控制
- **多种传感器**: 温湿度、土壤湿度、光照强度等

## 🏗️ 系统架构

```
┌─────────────────┐    WiFi/TCP    ┌─────────────────┐
│   STM32F103ZET6 │◄──────────────►│     ESP32       │
│   (主控制器)     │                │   (WiFi模块)     │
└─────────┬───────┘                └─────────────────┘
          │                                   ▲
          │ UART/ADC                         │ TCP/IP
          ▼                                   ▼
┌─────────────────┐                ┌─────────────────┐
│     传感器       │                │   Qt桌面应用     │
│  • 温湿度传感器  │                │  • 数据监控       │
│  • 土壤湿度     │                │  • 实时图表       │
│  • 光照传感器    │                │  • 远程控制       │
└─────────────────┘                └─────────────────┘
```

## 🚀 快速开始

### 📦 直接下载 (无需编译)

| 组件 | 文件 | 下载链接 | 描述 |
|------|------|----------|------|
| STM32固件 | `serial2_ADC.hex` | [下载](./assets/binaries/STM32/serial2_ADC.hex) | STM32F103ZET6主控制器固件 |
| ESP32固件 | `AP_TCPServer.bin` | [下载](./assets/binaries/ESP32/AP_TCPServer.bin) | ESP32 WiFi通信模块固件 |
| ESP32引导 | `bootloader.bin` | [下载](./assets/binaries/ESP32/bootloader.bin) | ESP32引导程序 |

### 📱 Qt桌面应用

Qt应用程序需要从源码编译，请参考 [Qt应用编译指南](#qt应用编译)。

## 📸 系统展示

<div align="center">
  <img src="./image/IMG_20240101_155554.JPG" width="300" alt="硬件实物图1"/>
  <img src="./image/IMG_20240101_155605.JPG" width="300" alt="硬件实物图2"/>
  <br/>
  <img src="./image/IMG_20240101_155701.JPG" width="300" alt="传感器模块"/>
  <img src="./image/IMG_20240101_155738.JPG" width="300" alt="主控板"/>
</div>

## 🔧 硬件要求

### 主要硬件组件
- **STM32F103ZET6开发板** - 主控制器
- **ESP32开发板** - WiFi通信模块  
- **温湿度传感器** (DHT22/SHT30等)
- **土壤湿度传感器**
- **光照传感器** (LDR/BH1750等)
- **LCD显示屏** (可选)
- **继电器模块** (用于控制灌溉等)

### 连接说明
- STM32与ESP32通过UART串口通信
- 传感器通过ADC/I2C/GPIO连接到STM32
- 系统支持多种传感器扩展

## 💻 软件环境

### 开发环境要求
- **STM32开发**: STM32CubeIDE 或 Keil MDK-ARM
- **ESP32开发**: ESP-IDF v4.4+
- **Qt应用开发**: Qt 5.12+ 或 Qt 6.x
- **串口调试**: 任意串口调试工具

### 支持平台
- Windows 10/11
- Linux (Ubuntu 18.04+)
- macOS 10.14+

## 🔨 编译和烧录

### STM32固件烧录

1. **使用预编译固件** (推荐)
   ```bash
   # 下载固件文件
   wget https://github.com/longzheng268/plant_monitor/raw/main/assets/binaries/STM32/serial2_ADC.hex
   
   # 使用STM32CubeProgrammer烧录
   STM32_Programmer_CLI -c port=SWD -w serial2_ADC.hex -v -rst
   ```

2. **从源码编译**
   - 打开 `STM32F103ZET6/plant_monitor/serial2_ADC.ioc`
   - 在STM32CubeIDE中生成代码
   - 编译并烧录到开发板

### ESP32固件烧录

1. **使用预编译固件** (推荐)
   ```bash
   # 安装esptool
   pip install esptool
   
   # 下载固件文件
   wget https://github.com/longzheng268/plant_monitor/raw/main/assets/binaries/ESP32/bootloader.bin
   wget https://github.com/longzheng268/plant_monitor/raw/main/assets/binaries/ESP32/AP_TCPServer.bin
   
   # 烧录固件
   esptool.py --chip esp32c3 --port COM3 --baud 460800 write_flash 0x0 bootloader.bin 0x10000 AP_TCPServer.bin
   ```

2. **从源码编译**
   ```bash
   cd ESP-IDF/plant_monitor
   idf.py set-target esp32c3
   idf.py menuconfig  # 配置WiFi参数
   idf.py build flash monitor
   ```

### Qt应用编译

```bash
cd Qt/plant_monitor
qmake plant_monitor.pro
make  # Linux/macOS
# 或者在Windows上使用nmake或在Qt Creator中直接编译
```

## ⚙️ 配置说明

### WiFi配置
在ESP32固件中配置WiFi参数：
```c
#define WIFI_SSID "your_wifi_name"
#define WIFI_PASS "your_wifi_password"
```

### 传感器配置
在STM32固件中可以配置：
- ADC采样频率
- 传感器校准参数
- 数据上传间隔

### Qt应用配置
在Qt应用中配置：
- ESP32设备IP地址
- TCP通信端口
- 数据刷新频率

## 📊 功能特性

### 数据监测
- ✅ 实时温湿度监测
- ✅ 土壤湿度检测
- ✅ 光照强度测量
- ✅ 历史数据记录
- ✅ 数据可视化图表

### 智能控制
- ✅ 自动灌溉控制
- ✅ 环境调节提醒
- ✅ 阈值报警功能
- ✅ 远程设备控制

### 通信功能
- ✅ WiFi无线连接
- ✅ TCP/IP数据传输
- ✅ 实时数据同步
- ✅ 设备状态监控

## 🔍 故障排除

### 常见问题

**Q: ESP32连接不上WiFi？**
A: 检查WiFi账号密码配置，确保信号强度良好，重启设备重新连接。

**Q: STM32与ESP32通信异常？**
A: 检查串口连接线，确认波特率配置一致，检查电源供应。

**Q: Qt应用连接不上ESP32？**
A: 确认ESP32已连接WiFi并获取IP地址，检查防火墙设置，确认端口号正确。

**Q: 传感器数据异常？**
A: 检查传感器连接，确认供电正常，校验ADC参考电压。

### 调试方法
1. 使用串口监视器查看设备日志
2. 检查LED指示灯状态
3. 使用网络调试工具测试TCP连接
4. 查看Qt应用的日志输出

## 📁 项目结构

```
plant_monitor/
├── README.md                 # 项目主文档
├── CHANGELOG.md              # 更新日志
├── CONTRIBUTING.md           # 贡献指南
├── .gitignore               # Git忽略文件配置
├── assets/                   # 资源文件
│   └── binaries/            # 预编译的二进制文件
│       ├── STM32/          # STM32固件
│       ├── ESP32/          # ESP32固件
│       └── Qt/             # Qt应用程序
├── docs/                    # 详细文档
│   ├── BUILD_GUIDE.md      # 完整编译指南
│   ├── STM32_GUIDE.md      # STM32开发指南
│   ├── ESP32_GUIDE.md      # ESP32开发指南
│   ├── QT_GUIDE.md         # Qt应用开发指南
│   └── RELEASES.md         # 发布文档
├── doc/                     # 原始设计文档
│   ├── 计算机硬件综合训练I-任务书-基于STM32的智能农业植物生长监测系统.doc
│   └── 计算机硬件综合训练I-说明书-(基于STM32的智能农业植物生长监测系统).docx
├── image/                   # 项目图片
│   ├── IMG_20240101_155554.JPG
│   └── ...
├── STM32F103ZET6/          # STM32项目文件
│   └── plant_monitor/
├── ESP-IDF/                # ESP32项目文件
│   └── plant_monitor/
└── Qt/                     # Qt桌面应用
    └── plant_monitor/
```

## 📖 详细文档

### 📚 开发指南
- [🔨 完整编译指南](./docs/BUILD_GUIDE.md) - 从零开始的完整编译教程
- [🔧 STM32开发指南](./docs/STM32_GUIDE.md) - STM32固件开发详解
- [📡 ESP32开发指南](./docs/ESP32_GUIDE.md) - ESP32固件开发详解
- [🖥️ Qt应用开发指南](./docs/QT_GUIDE.md) - Qt桌面应用开发详解

### 📦 发布文档
- [📋 Release文档](./docs/RELEASES.md) - 版本发布说明和下载链接

### 📄 设计文档
- [📋 硬件设计文档](./doc/计算机硬件综合训练I-任务书-基于STM32的智能农业植物生长监测系统.doc)
- [📝 系统说明书](./doc/计算机硬件综合训练I-说明书-(基于STM32的智能农业植物生长监测系统).docx)

## 🤝 贡献指南

欢迎提交Issue和Pull Request来改进这个项目！详细贡献指南请查看 [CONTRIBUTING.md](./CONTRIBUTING.md)。

1. Fork本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启Pull Request

### 📋 更多信息
- [📝 更新日志](./CHANGELOG.md) - 查看版本历史和更新内容
- [🤝 贡献指南](./CONTRIBUTING.md) - 详细的贡献规范和流程

## 📄 许可证

本项目基于 Apache License 2.0 许可证开源。

## 👥 作者

- **longzheng268** - *项目维护者* - [GitHub](https://github.com/longzheng268)

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者和用户！

---

<div align="center">
  <p>如果这个项目对你有帮助，请给个 ⭐ Star 支持一下！</p>
</div>