# 🔨 完整编译指南

## 📋 概述

本指南详细介绍如何从源码编译整个植物监测系统的所有组件，包括STM32固件、ESP32固件和Qt桌面应用。

## 🛠️ 系统要求

### 硬件要求
- **CPU**: Intel i5或AMD同等处理器 (推荐i7或更高)
- **内存**: 最少4GB RAM (推荐8GB+)
- **存储**: 至少5GB可用空间
- **USB端口**: 用于连接开发板烧录

### 操作系统支持
- Windows 10/11 (x64)
- Ubuntu 18.04+ / Debian 10+
- macOS 10.14+ (Mojave)
- CentOS 7+ / RHEL 7+

## 🚀 快速开始

### 方法1: 使用预编译固件 (推荐新手)

如果您只想快速体验系统功能，可以直接使用预编译的固件：

1. **下载固件文件**
   ```bash
   # 创建下载目录
   mkdir plant_monitor_binaries
   cd plant_monitor_binaries
   
   # 下载STM32固件
   wget https://github.com/longzheng268/plant_monitor/raw/main/assets/binaries/STM32/serial2_ADC.hex
   
   # 下载ESP32固件
   wget https://github.com/longzheng268/plant_monitor/raw/main/assets/binaries/ESP32/AP_TCPServer.bin
   wget https://github.com/longzheng268/plant_monitor/raw/main/assets/binaries/ESP32/bootloader.bin
   ```

2. **烧录固件**
   - STM32: 使用STM32CubeProgrammer烧录 `serial2_ADC.hex`
   - ESP32: 使用esptool烧录 `bootloader.bin` 和 `AP_TCPServer.bin`

3. **编译Qt应用** (仍需要从源码编译)
   ```bash
   git clone https://github.com/longzheng268/plant_monitor.git
   cd plant_monitor/Qt/plant_monitor
   qmake plant_monitor.pro
   make
   ```

### 方法2: 完整源码编译

如果您需要修改代码或了解完整的开发过程，请按照以下详细步骤进行。

## 📦 开发环境安装

### Windows 开发环境

#### 1. 安装基础工具

```powershell
# 安装Chocolatey包管理器 (以管理员身份运行PowerShell)
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))

# 安装基础工具
choco install git python3 cmake ninja
```

#### 2. 安装STM32开发环境

1. **STM32CubeIDE**
   - 下载: https://www.st.com/en/development-tools/stm32cubeide.html
   - 安装并注册免费账户

2. **STM32CubeProgrammer**
   - 下载: https://www.st.com/en/development-tools/stm32cubeprog.html
   - 安装到默认路径

#### 3. 安装ESP32开发环境

```bash
# 下载ESP-IDF Windows安装器
# https://dl.espressif.com/dl/esp-idf-tools-setup-2.9.exe
# 运行安装器，选择ESP32-C3支持
```

#### 4. 安装Qt开发环境

```bash
# 下载Qt在线安装器
# https://www.qt.io/download-qt-installer
# 选择Qt 5.15.2 LTS和Qt Creator
```

### Linux 开发环境 (Ubuntu 20.04示例)

#### 1. 更新系统和安装基础工具

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install -y git cmake ninja-build python3 python3-pip curl wget
sudo apt install -y build-essential libssl-dev libffi-dev
```

#### 2. 安装STM32开发环境

```bash
# 下载STM32CubeIDE
wget https://www.st.com/content/ccc/resource/technical/software/sw_development_suite/group0/0b/05/9b/7e/9e/4b/46/83/stm32cubeide_deb/files/st-stm32cubeide_1.10.1_13696_20220707_1635_amd64.deb_bundle.sh.zip

# 安装
unzip st-stm32cubeide_*.zip
chmod +x st-stm32cubeide_*.sh
sudo ./st-stm32cubeide_*.sh

# 安装USB驱动
sudo apt install -y libusb-1.0-0-dev
sudo usermod -a -G dialout $USER
```

#### 3. 安装ESP-IDF

```bash
# 克隆ESP-IDF
git clone --recursive https://github.com/espressif/esp-idf.git ~/esp-idf
cd ~/esp-idf

# 安装工具链
./install.sh esp32c3

# 设置环境变量 (添加到~/.bashrc)
echo 'alias get_idf=". $HOME/esp-idf/export.sh"' >> ~/.bashrc
source ~/.bashrc
```

#### 4. 安装Qt

```bash
# 方法1: 使用包管理器 (简单但版本可能较旧)
sudo apt install -y qtbase5-dev qttools5-dev qtcreator

# 方法2: 下载Qt在线安装器 (推荐)
wget https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
chmod +x qt-unified-linux-x64-online.run
./qt-unified-linux-x64-online.run
```

### macOS 开发环境

#### 1. 安装Xcode命令行工具

```bash
xcode-select --install
```

#### 2. 安装Homebrew

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### 3. 安装开发工具

```bash
# 基础工具
brew install git cmake ninja python3 wget

# Qt开发环境
brew install qt5
brew install --cask qt-creator

# ESP-IDF
git clone --recursive https://github.com/espressif/esp-idf.git ~/esp-idf
cd ~/esp-idf
./install.sh esp32c3
echo 'alias get_idf=". $HOME/esp-idf/export.sh"' >> ~/.zshrc
```

## 🔧 编译步骤

### 1. 获取源码

```bash
# 克隆项目仓库
git clone https://github.com/longzheng268/plant_monitor.git
cd plant_monitor

# 查看项目结构
tree -L 2
```

### 2. 编译STM32固件

#### 使用STM32CubeIDE (推荐)

```bash
# 启动STM32CubeIDE
stm32cubeide # Linux
# 或从开始菜单启动 (Windows)
# 或从Applications启动 (macOS)

# 导入项目:
# File -> Import -> General -> Existing Projects into Workspace
# 选择: STM32F103ZET6/plant_monitor
```

1. **配置项目**
   - 双击 `serial2_ADC.ioc` 打开STM32CubeMX配置
   - 检查引脚配置和外设设置
   - 点击 "Generate Code" 生成HAL代码

2. **编译固件**
   - 右键项目 -> Build Project
   - 等待编译完成

3. **生成HEX文件**
   ```bash
   # 在项目目录下生成hex文件
   arm-none-eabi-objcopy -O ihex serial2_ADC.elf serial2_ADC.hex
   ```

#### 使用命令行编译 (高级用户)

```bash
cd STM32F103ZET6/plant_monitor

# 设置工具链路径
export PATH="/opt/st/stm32cubeide_1.10.1/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_2.0.0.202105311346/tools/bin:$PATH"

# 编译
make -j$(nproc)

# 生成hex文件
arm-none-eabi-objcopy -O ihex build/serial2_ADC.elf build/serial2_ADC.hex
```

### 3. 编译ESP32固件

```bash
cd ESP-IDF/plant_monitor

# 激活ESP-IDF环境
get_idf  # Linux/macOS
# 或在Windows ESP-IDF命令提示符中操作

# 设置目标芯片
idf.py set-target esp32c3

# 配置项目 (可选)
idf.py menuconfig
# 在 "Example Configuration" 中设置WiFi参数

# 清理并编译
idf.py clean
idf.py build

# 编译完成后，固件位于 build/ 目录
ls build/*.bin
```

#### ESP32配置选项说明

在 `idf.py menuconfig` 中的重要配置：

1. **WiFi配置**
   ```
   Example Configuration --->
       WiFi SSID (PlantMonitor_AP)
       WiFi Password (12345678)
       WiFi Mode (AP Mode)
       Maximum STA connections (4)
   ```

2. **TCP服务器配置**
   ```
   Example Configuration --->
       TCP Port (8080)
       Keep alive enable (Yes)
       Keep alive idle time (7200)
   ```

3. **串口配置**
   ```
   Example Configuration --->
       UART port number (1)
       UART baud rate (115200)
       UART RX buffer size (1024)
   ```

### 4. 编译Qt桌面应用

#### 使用Qt Creator (推荐)

```bash
# 启动Qt Creator
qtcreator Qt/plant_monitor/plant_monitor.pro
```

1. **配置编译套件**
   - Tools -> Options -> Kits
   - 确保有可用的Qt版本和编译器

2. **编译项目**
   - 选择Release或Debug配置
   - 点击绿色运行按钮编译并运行

#### 使用命令行编译

```bash
cd Qt/plant_monitor

# 生成Makefile
qmake plant_monitor.pro

# 编译
make -j$(nproc)  # Linux/macOS
nmake            # Windows (MSVC)
mingw32-make     # Windows (MinGW)

# 运行
./plant_monitor      # Linux/macOS
plant_monitor.exe    # Windows
```

### 5. 交叉编译 (嵌入式Linux目标)

如果需要在ARM嵌入式设备上运行Qt应用：

```bash
# 设置交叉编译环境
export CROSS_COMPILE=arm-linux-gnueabihf-
export CC=${CROSS_COMPILE}gcc
export CXX=${CROSS_COMPILE}g++
export STRIP=${CROSS_COMPILE}strip

# 使用交叉编译版本的Qt
/opt/qt5-arm/bin/qmake plant_monitor.pro
make

# 复制到目标设备
scp plant_monitor user@target_device:/home/user/
```

## 🔥 烧录固件

### STM32固件烧录

#### 方法1: 使用STM32CubeProgrammer (推荐)

1. **连接硬件**
   - 使用ST-Link连接STM32开发板
   - 确保开发板上电

2. **烧录固件**
   ```bash
   # 命令行方式
   STM32_Programmer_CLI -c port=SWD -w path/to/serial2_ADC.hex -v -rst
   
   # 或使用图形界面
   STM32CubeProgrammer
   ```

#### 方法2: 使用串口烧录

```bash
# 设置BOOT0=1，复位芯片进入bootloader模式
# 使用串口烧录工具
stm32flash -w serial2_ADC.bin -v -g 0x0 /dev/ttyUSB0
```

### ESP32固件烧录

```bash
cd ESP-IDF/plant_monitor

# 查找串口设备
ls /dev/ttyUSB*  # Linux
ls /dev/cu.*     # macOS

# 烧录固件
idf.py -p /dev/ttyUSB0 flash

# 监视输出
idf.py -p /dev/ttyUSB0 monitor

# 组合命令：烧录并监视
idf.py -p /dev/ttyUSB0 flash monitor
```

#### 手动烧录ESP32 (使用esptool)

```bash
# 安装esptool
pip install esptool

# 擦除flash
esptool.py --chip esp32c3 --port /dev/ttyUSB0 erase_flash

# 烧录bootloader和应用程序
esptool.py --chip esp32c3 --port /dev/ttyUSB0 --baud 460800 write_flash \
    0x0 build/bootloader/bootloader.bin \
    0x8000 build/partition_table/partition-table.bin \
    0x10000 build/AP_TCPServer.bin
```

## 🔍 验证和测试

### 1. 硬件功能测试

#### STM32测试
```bash
# 连接串口调试工具，波特率115200
# 应该看到类似输出：
# System Initialize...
# ADC Configuration Complete
# Sensor Reading: T=25.6°C, H=65.2%, S=78.3%, L=450Lux
```

#### ESP32测试
```bash
# 监视ESP32串口输出
idf.py monitor

# 预期输出：
# I (506) wifi:mode : softAP (7c:df:a1:40:02:95)
# I (506) wifi softAP: wifi_init_softap finished. SSID:PlantMonitor_AP
# I (516) tcp_server: Starting TCP server on port 8080
```

### 2. 通信测试

#### WiFi连接测试
```bash
# 在PC上搜索WiFi热点 "PlantMonitor_AP"
# 连接密码: 12345678
# 获取IP地址: 192.168.4.2 (ESP32为192.168.4.1)

# 测试TCP连接
telnet 192.168.4.1 8080
# 或
nc 192.168.4.1 8080
```

#### 数据传输测试
```bash
# 使用网络调试工具连接到 192.168.4.1:8080
# 应该接收到格式为 "h25.6,65.2,78.3,450~" 的数据
```

### 3. Qt应用测试

1. **启动应用**
   ```bash
   ./plant_monitor
   ```

2. **连接设备**
   - 输入IP地址: `192.168.4.1`
   - 端口: `8080`
   - 点击连接按钮

3. **验证功能**
   - 检查实时数据显示
   - 验证图表更新
   - 测试设置保存

## 🛠️ 故障排除

### 编译问题

#### STM32编译错误
```bash
# 错误: arm-none-eabi-gcc: command not found
# 解决: 安装或正确配置ARM工具链
export PATH="/opt/st/stm32cubeide/plugins/.../tools/bin:$PATH"

# 错误: HAL库文件缺失
# 解决: 重新生成CubeMX代码
```

#### ESP32编译错误
```bash
# 错误: IDF_PATH not set
# 解决: 设置ESP-IDF环境
source ~/esp-idf/export.sh

# 错误: Python模块缺失
# 解决: 重新安装ESP-IDF
cd ~/esp-idf && ./install.sh esp32c3
```

#### Qt编译错误
```bash
# 错误: qmake: command not found
# 解决: 设置Qt环境变量
export PATH="/opt/Qt/5.15.2/gcc_64/bin:$PATH"

# 错误: 找不到Qt库
# 解决: 安装开发库
sudo apt install qtbase5-dev qttools5-dev
```

### 烧录问题

#### STM32烧录失败
```bash
# 检查ST-Link连接
lsusb | grep STMicroelectronics

# 检查SWD连接
STM32_Programmer_CLI -c port=SWD -l

# 设置BOOT引脚进入bootloader模式
```

#### ESP32烧录失败
```bash
# 检查串口权限
sudo usermod -a -G dialout $USER
# 重新登录

# 手动进入下载模式
# 按住BOOT按钮，按下RESET，释放RESET，释放BOOT

# 降低烧录波特率
idf.py -p /dev/ttyUSB0 -b 115200 flash
```

### 运行时问题

#### 设备连接失败
- 检查WiFi热点是否正常启动
- 确认IP地址和端口设置
- 检查防火墙设置
- 验证设备间网络连通性

#### 数据接收异常
- 检查串口连接和波特率设置
- 验证数据格式是否正确
- 查看设备日志输出
- 检查传感器连接

## 📦 部署和分发

### 创建Release包

```bash
# 创建release目录
mkdir -p release/{STM32,ESP32,Qt}/{Windows,Linux,macOS}

# 复制STM32固件
cp STM32F103ZET6/plant_monitor/Debug/serial2_ADC.hex release/STM32/

# 复制ESP32固件
cp ESP-IDF/plant_monitor/build/AP_TCPServer.bin release/ESP32/
cp ESP-IDF/plant_monitor/build/bootloader/bootloader.bin release/ESP32/

# 打包Qt应用
# Windows
windeployqt plant_monitor.exe
# Linux
linuxdeployqt plant_monitor
# macOS
macdeployqt plant_monitor.app
```

### 自动化构建脚本

```bash
#!/bin/bash
# build_all.sh - 全自动编译脚本

set -e

echo "Building Plant Monitor System..."

# 编译STM32固件
echo "Building STM32 firmware..."
cd STM32F103ZET6/plant_monitor
make clean && make -j$(nproc)
cd ../..

# 编译ESP32固件
echo "Building ESP32 firmware..."
cd ESP-IDF/plant_monitor
get_idf
idf.py clean build
cd ../..

# 编译Qt应用
echo "Building Qt application..."
cd Qt/plant_monitor
qmake && make clean && make -j$(nproc)
cd ../..

echo "Build completed successfully!"
echo "Firmware files:"
echo "  STM32: STM32F103ZET6/plant_monitor/Debug/serial2_ADC.hex"
echo "  ESP32: ESP-IDF/plant_monitor/build/AP_TCPServer.bin"
echo "  Qt App: Qt/plant_monitor/plant_monitor"
```

## 📚 参考文档

- [STM32开发指南](./STM32_GUIDE.md)
- [ESP32开发指南](./ESP32_GUIDE.md)
- [Qt应用开发指南](./QT_GUIDE.md)
- [Release文档](./RELEASES.md)

---

## 💡 开发建议

1. **版本控制**: 使用Git进行版本管理，定期提交代码
2. **代码规范**: 遵循各平台的编码规范和最佳实践
3. **测试驱动**: 在添加新功能前先编写测试用例
4. **文档更新**: 及时更新文档和注释
5. **持续集成**: 考虑使用CI/CD自动化构建和测试

## 🆘 获取帮助

如果在编译过程中遇到问题：

1. 查看对应平台的详细开发指南
2. 检查系统要求和依赖安装
3. 在GitHub Issues中搜索相似问题
4. 提交新的Issue并提供详细的错误信息
5. 加入开发者社区讨论