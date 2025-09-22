# 📥 直接下载中心 (Direct Download Center)

无需进入assets文件夹，直接下载所有项目文件！

> **许可证提醒**: 使用前请联系 [glasswarm (琉璃)](https://github.com/glasswarm) 获取许可

## 🚀 2.0版本预编译应用 (最新)

### 📱 移动端与桌面端应用

> **🎉 全新发布！** v2.0.0版本预编译应用，无需编译直接使用  
> **📋 详细说明**: [查看完整v2.0.0发布说明](./releases/v2.0.0.md)

<div align="center">

| 平台 | 架构 | 下载链接 | 版本 | 大小 |
|------|------|----------|------|------|
| 📱 Android | ARM64 | [![Download APK](https://img.shields.io/badge/📱_Android_APK-下载_ARM64-green?style=for-the-badge&logo=android)](https://github.com/longzheng268/plant_monitor/releases/download/2.0/plant_monitor_arm64.apk) | v2.0.0 | ~15MB |
| 🖥️ Windows | AMD64 | [![Download EXE](https://img.shields.io/badge/🖥️_Windows_EXE-下载_AMD64-blue?style=for-the-badge&logo=windows)](https://github.com/longzheng268/plant_monitor/releases/download/2.0/plant_monitor_amd64.exe) | v2.0.0 | ~25MB |

</div>

#### 📱 Android应用特性
- ✨ 全新Material Design界面
- 📊 实时数据图表显示
- 🔔 智能推送通知
- 🌙 深色模式支持
- 📱 手势操作优化
- 🔄 后台数据同步

#### 🖥️ Windows应用特性  
- 🎯 现代化Fluent Design界面
- 📈 高级数据分析工具
- ⚙️ 系统参数配置面板
- 📊 多视图数据展示
- 🔐 安全连接管理
- 💾 数据导出功能

#### 📋 系统要求
- **Android**: Android 7.0+ (API 24+), ARM64架构
- **Windows**: Windows 10+ (64位), AMD64架构  
- **网络**: WiFi连接到监测系统
- **内存**: 至少2GB可用RAM

## 🚀 一键下载完整项目

### 🎯 快速开始选择

> **推荐**: 如果您只想使用应用程序，请下载上方的2.0版本预编译应用

### 完整项目包
```bash
# Git克隆（推荐）
git clone https://github.com/longzheng268/plant_monitor.git

# 或下载ZIP压缩包
https://github.com/longzheng268/plant_monitor/archive/refs/heads/main.zip
```

## 📂 分模块直接下载

### 🔧 STM32主控程序文件

**核心工程文件**:
- 🎯 [**Keil工程文件 (serial2_ADC.uvprojx)**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/MDK-ARM/serial2_ADC.uvprojx)
- 📄 [主程序源码 (main.c)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/main.c)
- 📄 [ADC驱动程序 (adc.c)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/adc.c)
- 📄 [串口通信 (usart.c)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/usart.c)
- 📄 [GPIO配置 (gpio.c)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/gpio.c)

**头文件**:
- 📄 [main.h](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Inc/main.h)
- 📄 [adc.h](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Inc/adc.h)
- 📄 [usart.h](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Inc/usart.h)

**启动和配置文件**:
- 📄 [启动文件 (startup_stm32f103xe.s)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/MDK-ARM/startup_stm32f103xe.s)
- 📄 [STM32CubeMX配置 (serial2_ADC.ioc)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/serial2_ADC.ioc)

### 📡 ESP32通信模块文件

**核心程序文件**:
- 📄 [**主程序入口 (main.c)**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/main/main.c)
- 📄 [WiFi初始化头文件](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/main/wifi_sta_init.h)
- 📄 [TCP服务器头文件](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/main/tcp_server.h)
- 📄 [串口通信头文件](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/main/uart_init.h)

**项目配置文件**:
- 📄 [**CMakeLists.txt**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/CMakeLists.txt)
- 📄 [Kconfig.projbuild](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/main/Kconfig.projbuild)
- 📄 [sdkconfig](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/sdkconfig)

### 🖥️ Qt桌面应用文件

**核心应用文件**:
- 📄 [**Qt工程文件 (plant_monitor.pro)**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/plant_monitor.pro)
- 📄 [主程序入口 (main.cpp)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/main.cpp)
- 📄 [应用程序类 (plant_monitor.cpp)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/plant_monitor.cpp)
- 📄 [头文件 (plant_monitor.h)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/plant_monitor.h)

**界面设计文件**:
- 📄 [**UI界面文件 (plant_monitor.ui)**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/plant_monitor.ui)
- 📄 [资源文件 (image.qrc)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/image.qrc)

## 📚 文档资源直接下载

### 项目说明文档
- 📖 [**完整README.md**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/README.md)
- 📜 [许可证文件 (LICENSE)](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/LICENSE)
- 📋 [v2.0.0版本发布说明](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/releases/v2.0.0.md)
- 📋 [v1.0.0版本发布说明](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/releases/v1.0.0.md)

### Word文档（需要下载查看）
- 📄 [项目说明书 (.docx)](https://github.com/longzheng268/plant_monitor/raw/main/doc/计算机硬件综合训练I-说明书-(基于STM32的智能农业植物生长监测系统).docx)
- 📄 [项目任务书 (.doc)](https://github.com/longzheng268/plant_monitor/raw/main/doc/计算机硬件综合训练I-任务书-基于STM32的智能农业植物生长监测系统.doc)

## 🖼️ 项目图片直接访问

### 硬件展示图片
- 🖼️ [**主要展示图**](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155554.JPG)
- 🖼️ [系统整体视图](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155605.JPG)
- 🖼️ [LCD显示界面](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155701.JPG)
- 🖼️ [传感器布局](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155738.JPG)
- 🖼️ [控制电路板](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155805.JPG)
- 🖼️ [系统连接图](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155828.JPG)
- 🖼️ [运行状态](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240101_155902.JPG)
- 🖼️ [监测数据](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_20240102_120629.JPG)

### 更多图片
- 🖼️ [系统硬件图1](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_7158.JPG)
- 🖼️ [系统硬件图2](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_7161.JPG)
- 🖼️ [系统硬件图3](https://raw.githubusercontent.com/longzheng268/plant_monitor/main/image/IMG_7162.JPG)

## 💾 批量下载脚本

### 🚀 2.0版本应用快速下载脚本

#### Windows PowerShell - 2.0应用下载
```powershell
# 创建下载目录
New-Item -ItemType Directory -Path "plant_monitor_v2.0_apps" -Force
Set-Location "plant_monitor_v2.0_apps"

# 下载2.0版本预编译应用
Write-Host "正在下载Android ARM64应用..." -ForegroundColor Green
Invoke-WebRequest -Uri "https://github.com/longzheng268/plant_monitor/releases/download/2.0/plant_monitor_arm64.apk" -OutFile "plant_monitor_arm64.apk"

Write-Host "正在下载Windows AMD64应用..." -ForegroundColor Blue  
Invoke-WebRequest -Uri "https://github.com/longzheng268/plant_monitor/releases/download/2.0/plant_monitor_amd64.exe" -OutFile "plant_monitor_amd64.exe"

Write-Host "2.0版本应用下载完成！" -ForegroundColor Yellow
Write-Host "Android APK: plant_monitor_arm64.apk" -ForegroundColor Green
Write-Host "Windows EXE: plant_monitor_amd64.exe" -ForegroundColor Blue
```

### Linux/macOS 批量下载脚本

#### Bash - 2.0应用下载
```bash
#!/bin/bash
# 创建下载目录
mkdir -p plant_monitor_v2.0_apps
cd plant_monitor_v2.0_apps

echo "🚀 正在下载植物监测系统2.0版本应用..."

# 下载2.0版本预编译应用
echo "📱 下载Android ARM64应用..."
wget -O plant_monitor_arm64.apk "https://github.com/longzheng268/plant_monitor/releases/download/2.0/plant_monitor_arm64.apk"

echo "🖥️ 下载Windows AMD64应用..."
wget -O plant_monitor_amd64.exe "https://github.com/longzheng268/plant_monitor/releases/download/2.0/plant_monitor_amd64.exe"

echo "✅ 2.0版本应用下载完成！"
echo "📁 文件列表："
ls -la *.apk *.exe 2>/dev/null || echo "请检查下载是否成功"
```

#### 完整项目源码下载
#### 完整项目源码下载
```bash
#!/bin/bash
# 创建下载目录
mkdir -p plant_monitor_download/{STM32,ESP32,Qt,docs,images}

# 下载STM32文件
cd plant_monitor_download/STM32
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/MDK-ARM/serial2_ADC.uvprojx
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/main.c
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/adc.c
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/Core/Src/usart.c

# 下载ESP32文件
cd ../ESP32
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/main/main.c
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/ESP-IDF/plant_monitor/CMakeLists.txt

# 下载Qt文件
cd ../Qt
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/plant_monitor.pro
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/main.cpp
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/Qt/plant_monitor/plant_monitor.ui

# 下载文档
cd ../docs
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/README.md
wget https://raw.githubusercontent.com/longzheng268/plant_monitor/main/LICENSE

echo "下载完成！"
```

### Windows PowerShell 批量下载脚本

#### 完整项目源码下载
#### 完整项目源码下载
```powershell
# 创建下载目录
New-Item -ItemType Directory -Path "plant_monitor_download" -Force
Set-Location "plant_monitor_download"

# 下载核心文件
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/longzheng268/plant_monitor/main/STM32F103ZET6/plant_monitor/MDK-ARM/serial2_ADC.uvprojx" -OutFile "serial2_ADC.uvprojx"
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/longzheng268/plant_monitor/main/README.md" -OutFile "README.md"
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/longzheng268/plant_monitor/main/LICENSE" -OutFile "LICENSE"

Write-Host "下载完成！"
```

## 🔗 相关链接

- 🏠 [项目主页](https://github.com/longzheng268/plant_monitor)
- 📖 [完整README](../README.md)
- 📜 [许可证说明](../LICENSE)
- 🐛 [问题反馈](https://github.com/longzheng268/plant_monitor/issues)
- 👨‍💻 [原作者主页](https://github.com/glasswarm)

---

## ⚠️ 使用许可提醒

本项目由 [glasswarm (琉璃)](https://github.com/glasswarm) 完全打造，使用前请联系获取许可。

**联系方式**: [https://github.com/glasswarm](https://github.com/glasswarm)

---

**© 2024 glasswarm (琉璃). All rights reserved.**