# 🖥️ Qt桌面应用开发指南

## 📋 概述

Qt桌面应用作为植物监测系统的用户界面，提供实时数据监控、历史数据查看、设备控制等功能。

## 🏗️ 技术架构

### 开发框架
- **Qt版本**: Qt 5.12+ 或 Qt 6.x
- **编程语言**: C++
- **GUI框架**: Qt Widgets
- **网络通信**: QTcpSocket
- **图表显示**: QCustomPlot (可选)

### 应用架构
```
Qt Application
├── main.cpp                    # 应用程序入口
├── plant_monitor.h/.cpp        # 主窗口类
├── plant_monitor.ui            # UI界面设计
├── plant_monitor.pro           # qmake项目文件
├── plant_monitor_zh_CN.ts      # 中文翻译文件
├── image.qrc                   # 资源文件
└── picture/                    # 图片资源
```

## 🔨 开发环境搭建

### 软件要求

#### Qt开发环境
- **Qt Creator** 4.11+ (推荐使用最新版本)
- **Qt Framework** 5.12+ 或 6.x
- **编译器**:
  - Windows: MSVC 2017+ 或 MinGW
  - Linux: GCC 7.5+
  - macOS: Clang (Xcode命令行工具)

#### 第三方库 (可选)
- **QCustomPlot**: 用于高级图表显示
- **QWT**: 科学计算图表库

### 安装Qt

#### 在线安装器 (推荐)
1. 下载Qt在线安装器: https://www.qt.io/download-qt-installer
2. 运行安装器并选择组件:
   - Qt 5.15.2 或 Qt 6.4+ 
   - Qt Creator
   - 对应平台的编译器

#### 离线安装
```bash
# Ubuntu/Debian
sudo apt-get install qt5-default qtcreator qtbase5-dev qttools5-dev

# CentOS/RHEL
sudo yum install qt5-qtbase-devel qt-creator

# macOS (使用Homebrew)
brew install qt5
brew install --cask qt-creator

# Windows
# 下载离线安装包并安装
```

## 📝 项目结构详解

### 主要文件说明

#### 1. main.cpp - 应用程序入口
```cpp
#include "plant_monitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 设置应用程序信息
    a.setApplicationName("Plant Monitor");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("PlantMonitor Team");
    
    plant_monitor w;
    w.show();
    
    return a.exec();
}
```

#### 2. plant_monitor.h - 主窗口类声明
```cpp
#ifndef PLANT_MONITOR_H
#define PLANT_MONITOR_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QLabel>
#include <QChart>
#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class plant_monitor; }
QT_END_NAMESPACE

class plant_monitor : public QMainWindow
{
    Q_OBJECT

public:
    plant_monitor(QWidget *parent = nullptr);
    ~plant_monitor();

private slots:
    void on_connectButton_clicked();           // 连接按钮点击
    void on_disconnectButton_clicked();        // 断开连接按钮
    void readData();                          // 读取TCP数据
    void handleError(QAbstractSocket::SocketError error); // 错误处理
    void updateCharts();                      // 更新图表
    void saveSettings();                      // 保存设置
    void loadSettings();                      // 加载设置

private:
    Ui::plant_monitor *ui;
    QTcpSocket *tcpSocket;                   // TCP客户端
    QTimer *updateTimer;                     // 更新定时器
    
    // 数据存储
    QList<double> temperatureData;
    QList<double> humidityData;
    QList<double> soilMoistureData;
    QList<double> lightData;
    QList<QDateTime> timeStamps;
    
    // 图表相关
    QChart *temperatureChart;
    QLineSeries *temperatureSeries;
    // ... 其他图表组件
    
    // 状态显示
    QLabel *connectionStatus;
    QLabel *dataStatus;
    
    void setupUI();                          // 界面初始化
    void setupCharts();                      // 图表初始化
    void parseData(const QString &data);     // 解析传感器数据
    void updateStatusBar();                  // 更新状态栏
};

#endif // PLANT_MONITOR_H
```

#### 3. plant_monitor.cpp - 主要功能实现
```cpp
#include "plant_monitor.h"
#include "ui_plant_monitor.h"
#include <QMessageBox>
#include <QSettings>
#include <QDateTime>
#include <QDebug>

plant_monitor::plant_monitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::plant_monitor)
    , tcpSocket(new QTcpSocket(this))
    , updateTimer(new QTimer(this))
{
    ui->setupUi(this);
    setupUI();
    setupCharts();
    loadSettings();
    
    // 连接信号和槽
    connect(tcpSocket, &QTcpSocket::readyRead, this, &plant_monitor::readData);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &plant_monitor::handleError);
    connect(updateTimer, &QTimer::timeout, this, &plant_monitor::updateCharts);
    
    updateTimer->start(1000); // 每秒更新一次
}

void plant_monitor::on_connectButton_clicked()
{
    QString host = ui->hostLineEdit->text();
    quint16 port = ui->portSpinBox->value();
    
    tcpSocket->connectToHost(host, port);
    
    if (tcpSocket->waitForConnected(3000)) {
        ui->statusLabel->setText("已连接");
        ui->connectButton->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
        qDebug() << "Connected to" << host << ":" << port;
    } else {
        QMessageBox::warning(this, "连接失败", 
                           "无法连接到服务器\n请检查IP地址和端口号");
    }
}

void plant_monitor::readData()
{
    QByteArray data = tcpSocket->readAll();
    QString dataString = QString::fromUtf8(data);
    
    qDebug() << "Received data:" << dataString;
    
    // 解析数据格式: h温度,湿度,土壤湿度,光照~
    if (dataString.startsWith('h') && dataString.endsWith('~')) {
        parseData(dataString);
    }
}

void plant_monitor::parseData(const QString &data)
{
    // 移除开头的'h'和结尾的'~'
    QString cleanData = data.mid(1, data.length() - 2);
    QStringList values = cleanData.split(',');
    
    if (values.size() >= 4) {
        bool ok;
        double temperature = values[0].toDouble(&ok);
        if (ok) {
            temperatureData.append(temperature);
            ui->temperatureLabel->setText(QString::number(temperature, 'f', 1) + "°C");
        }
        
        double humidity = values[1].toDouble(&ok);
        if (ok) {
            humidityData.append(humidity);
            ui->humidityLabel->setText(QString::number(humidity, 'f', 1) + "%");
        }
        
        double soilMoisture = values[2].toDouble(&ok);
        if (ok) {
            soilMoistureData.append(soilMoisture);
            ui->soilMoistureLabel->setText(QString::number(soilMoisture, 'f', 1) + "%");
        }
        
        double light = values[3].toDouble(&ok);
        if (ok) {
            lightData.append(light);
            ui->lightLabel->setText(QString::number(light, 'f', 0) + " Lux");
        }
        
        timeStamps.append(QDateTime::currentDateTime());
        
        // 限制数据点数量 (保留最近100个点)
        if (temperatureData.size() > 100) {
            temperatureData.removeFirst();
            humidityData.removeFirst();
            soilMoistureData.removeFirst();
            lightData.removeFirst();
            timeStamps.removeFirst();
        }
        
        updateStatusBar();
    }
}
```

### 4. plant_monitor.ui - 界面设计

界面包含以下主要组件:
- **连接设置区域**: IP地址输入、端口设置、连接/断开按钮
- **实时数据显示**: 温度、湿度、土壤湿度、光照强度数值显示
- **图表区域**: 历史数据趋势图表
- **控制区域**: 设备控制按钮 (未来功能)
- **状态栏**: 连接状态、数据接收状态

## 🔧 编译和运行

### 使用Qt Creator (推荐)

1. **打开项目**
   - 启动Qt Creator
   - File -> Open File or Project
   - 选择 `plant_monitor.pro` 文件

2. **配置编译套件**
   - 确保选择了正确的Qt版本和编译器
   - Projects -> Build & Run -> 选择合适的Kit

3. **编译运行**
   - 点击绿色运行按钮
   - 或按 Ctrl+R (Windows/Linux) / Cmd+R (macOS)

### 使用命令行编译

```bash
cd Qt/plant_monitor

# 生成Makefile
qmake plant_monitor.pro

# 编译
make          # Linux/macOS
nmake         # Windows (Visual Studio)
mingw32-make  # Windows (MinGW)

# 运行
./plant_monitor     # Linux/macOS
plant_monitor.exe   # Windows
```

### 交叉编译 (嵌入式Linux)

```bash
# 设置交叉编译环境
export PATH=/opt/arm-linux-gnueabihf/bin:$PATH
export CC=arm-linux-gnueabihf-gcc
export CXX=arm-linux-gnueabihf-g++

# 使用交叉编译版本的qmake
/opt/qt5-arm/bin/qmake plant_monitor.pro
make
```

## 📊 功能模块详解

### 1. 网络通信模块

```cpp
// TCP连接管理
class NetworkManager : public QObject
{
    Q_OBJECT
    
public:
    NetworkManager(QObject *parent = nullptr);
    void connectToDevice(const QString &host, quint16 port);
    void disconnectFromDevice();
    bool isConnected() const;
    
signals:
    void dataReceived(const QString &data);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &error);
    
private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
    
private:
    QTcpSocket *socket;
    QTimer *heartbeatTimer;
};
```

### 2. 数据管理模块

```cpp
// 传感器数据结构
struct SensorData {
    QDateTime timestamp;
    double temperature;
    double humidity;
    double soilMoisture;
    double lightIntensity;
    
    bool isValid() const {
        return timestamp.isValid() && 
               temperature >= -40 && temperature <= 80 &&
               humidity >= 0 && humidity <= 100 &&
               soilMoisture >= 0 && soilMoisture <= 100 &&
               lightIntensity >= 0;
    }
};

// 数据管理器
class DataManager : public QObject
{
    Q_OBJECT
    
public:
    void addData(const SensorData &data);
    QList<SensorData> getRecentData(int count = 100) const;
    QList<SensorData> getDataByTimeRange(const QDateTime &start, const QDateTime &end) const;
    void saveToFile(const QString &filename) const;
    void loadFromFile(const QString &filename);
    
signals:
    void dataAdded(const SensorData &data);
    void dataChanged();
    
private:
    QList<SensorData> dataList;
    mutable QMutex dataMutex;
};
```

### 3. 图表显示模块

```cpp
// 图表管理器
class ChartManager : public QObject
{
    Q_OBJECT
    
public:
    ChartManager(QWidget *parent = nullptr);
    void setupCharts();
    void updateCharts(const QList<SensorData> &data);
    void setChartTheme(QChart::ChartTheme theme);
    
private:
    void createTemperatureChart();
    void createHumidityChart();
    void createSoilMoistureChart();
    void createLightChart();
    
    QChartView *temperatureView;
    QChartView *humidityView;
    QChartView *soilMoistureView;
    QChartView *lightView;
    
    QLineSeries *temperatureSeries;
    QLineSeries *humiditySeries;
    QLineSeries *soilMoistureSeries;
    QLineSeries *lightSeries;
};
```

## ⚙️ 配置和设置

### 应用程序设置

```cpp
// 设置管理
void plant_monitor::saveSettings()
{
    QSettings settings;
    settings.beginGroup("Connection");
    settings.setValue("host", ui->hostLineEdit->text());
    settings.setValue("port", ui->portSpinBox->value());
    settings.endGroup();
    
    settings.beginGroup("Display");
    settings.setValue("updateInterval", updateTimer->interval());
    settings.setValue("maxDataPoints", 100);
    settings.endGroup();
    
    settings.beginGroup("Alerts");
    settings.setValue("temperatureMin", ui->tempMinSpinBox->value());
    settings.setValue("temperatureMax", ui->tempMaxSpinBox->value());
    settings.setValue("humidityMin", ui->humidityMinSpinBox->value());
    settings.setValue("humidityMax", ui->humidityMaxSpinBox->value());
    settings.endGroup();
}

void plant_monitor::loadSettings()
{
    QSettings settings;
    settings.beginGroup("Connection");
    ui->hostLineEdit->setText(settings.value("host", "192.168.4.1").toString());
    ui->portSpinBox->setValue(settings.value("port", 8080).toInt());
    settings.endGroup();
    
    settings.beginGroup("Display");
    int interval = settings.value("updateInterval", 1000).toInt();
    updateTimer->setInterval(interval);
    settings.endGroup();
    
    settings.beginGroup("Alerts");
    ui->tempMinSpinBox->setValue(settings.value("temperatureMin", 10).toDouble());
    ui->tempMaxSpinBox->setValue(settings.value("temperatureMax", 35).toDouble());
    ui->humidityMinSpinBox->setValue(settings.value("humidityMin", 30).toDouble());
    ui->humidityMaxSpinBox->setValue(settings.value("humidityMax", 80).toDouble());
    settings.endGroup();
}
```

### 国际化支持

```bash
# 生成翻译文件
lupdate plant_monitor.pro

# 翻译字符串 (使用Qt Linguist)
linguist plant_monitor_zh_CN.ts

# 发布翻译文件
lrelease plant_monitor.pro
```

## 🎨 界面定制

### 样式表定制

```cpp
// 应用自定义样式
void plant_monitor::setupUI()
{
    // 设置应用程序样式
    QString styleSheet = R"(
        QMainWindow {
            background-color: #f0f0f0;
        }
        
        QGroupBox {
            font-weight: bold;
            border: 2px solid #cccccc;
            border-radius: 5px;
            margin-top: 1ex;
            padding-top: 10px;
        }
        
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px 0 5px;
        }
        
        QPushButton {
            background-color: #4CAF50;
            border: none;
            color: white;
            padding: 8px 16px;
            text-align: center;
            font-size: 14px;
            border-radius: 4px;
        }
        
        QPushButton:hover {
            background-color: #45a049;
        }
        
        QPushButton:pressed {
            background-color: #3d8b40;
        }
        
        QPushButton:disabled {
            background-color: #cccccc;
            color: #666666;
        }
        
        QLabel#dataLabel {
            font-size: 18px;
            font-weight: bold;
            color: #2E7D32;
        }
    )";
    
    this->setStyleSheet(styleSheet);
}
```

### 图标和资源

```qrc
<!-- image.qrc -->
<RCC>
    <qresource prefix="/">
        <file>picture/icon.png</file>
        <file>picture/connect.png</file>
        <file>picture/disconnect.png</file>
        <file>picture/temperature.png</file>
        <file>picture/humidity.png</file>
        <file>picture/soil.png</file>
        <file>picture/light.png</file>
    </qresource>
</RCC>
```

## 🔍 调试和测试

### 调试技巧

```cpp
// 使用Qt的调试输出
#include <QDebug>
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(networkCategory)
Q_LOGGING_CATEGORY(networkCategory, "network")

// 在代码中使用
qCDebug(networkCategory) << "Connection established to" << host;
qCWarning(networkCategory) << "Connection timeout";
qCCritical(networkCategory) << "Network error:" << error;

// 环境变量控制日志输出
// QT_LOGGING_RULES="network.debug=true" ./plant_monitor
```

### 单元测试

```cpp
// test_datamanager.cpp
#include <QtTest>
#include "datamanager.h"

class TestDataManager : public QObject
{
    Q_OBJECT

private slots:
    void testAddData();
    void testDataValidation();
    void testTimeRangeQuery();
};

void TestDataManager::testAddData()
{
    DataManager manager;
    SensorData data;
    data.timestamp = QDateTime::currentDateTime();
    data.temperature = 25.5;
    data.humidity = 60.0;
    data.soilMoisture = 75.0;
    data.lightIntensity = 350.0;
    
    manager.addData(data);
    
    QList<SensorData> recentData = manager.getRecentData(1);
    QCOMPARE(recentData.size(), 1);
    QCOMPARE(recentData.first().temperature, 25.5);
}

QTEST_MAIN(TestDataManager)
#include "test_datamanager.moc"
```

## 📦 打包和发布

### Windows打包

```bash
# 编译Release版本
qmake CONFIG+=release plant_monitor.pro
make release

# 复制依赖库
windeployqt.exe release/plant_monitor.exe

# 创建安装包 (使用NSIS或Inno Setup)
makensis plant_monitor_installer.nsi
```

### Linux AppImage打包

```bash
# 安装linuxdeployqt
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod +x linuxdeployqt-continuous-x86_64.AppImage

# 创建AppDir结构
make install INSTALL_ROOT=appdir

# 生成AppImage
./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/plant_monitor.desktop -appimage
```

### macOS打包

```bash
# 创建app bundle
macdeployqt plant_monitor.app

# 创建DMG安装包
hdiutil create -volname "Plant Monitor" -srcfolder plant_monitor.app -ov -format UDZO plant_monitor.dmg
```

## 🚀 性能优化

### 内存优化
- 限制历史数据点数量
- 使用对象池重用频繁创建的对象
- 及时释放不再使用的图表数据

### 界面响应性优化
- 使用QTimer避免阻塞UI线程
- 数据处理放在后台线程
- 图表更新使用批量操作

### 网络优化
- 实现重连机制
- 添加心跳检测
- 数据缓存和离线模式

## 📚 参考资料

- [Qt官方文档](https://doc.qt.io/)
- [Qt Widget示例](https://doc.qt.io/qt-5/qtwidgets-examples.html)
- [QCustomPlot文档](https://www.qcustomplot.com/documentation)
- [Qt样式表参考](https://doc.qt.io/qt-5/stylesheet-reference.html)

---

## 🆘 常见问题

**Q: 编译时提示找不到Qt库？**
A: 检查Qt安装路径，确保环境变量设置正确，或在Qt Creator中选择正确的Kit。

**Q: 运行时提示缺少DLL文件？**
A: 使用windeployqt工具复制所需的Qt库文件到程序目录。

**Q: 图表显示异常或性能差？**
A: 检查数据点数量，考虑使用数据抽样或优化图表更新频率。

**Q: 网络连接不稳定？**
A: 实现重连机制，增加错误处理，检查网络环境和设备状态。