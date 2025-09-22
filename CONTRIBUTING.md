# 🤝 贡献指南 (CONTRIBUTING)

欢迎参与智能农业植物生长监测系统的开发！本指南将帮助您了解如何为项目做出贡献。

## 📋 项目概述

这是一个开源的植物监测系统，包含STM32固件、ESP32固件和Qt桌面应用三个主要组件。我们欢迎各种形式的贡献，包括代码、文档、测试、建议等。

## 🚀 如何开始

### 1. 环境准备

请先阅读 [完整编译指南](./docs/BUILD_GUIDE.md) 来设置开发环境。

### 2. Fork 项目

1. 点击页面右上角的 "Fork" 按钮
2. 将项目 fork 到您的 GitHub 账户
3. 克隆您的 fork 到本地

```bash
git clone https://github.com/你的用户名/plant_monitor.git
cd plant_monitor
git remote add upstream https://github.com/longzheng268/plant_monitor.git
```

### 3. 创建分支

为您的贡献创建一个新分支：

```bash
git checkout -b feature/your-feature-name
# 或
git checkout -b bugfix/issue-number
```

## 🔧 贡献类型

### 1. 代码贡献

#### STM32固件开发
- **位置**: `STM32F103ZET6/plant_monitor/`
- **开发环境**: STM32CubeIDE 或 Keil MDK
- **编码规范**: 
  - 使用4个空格缩进
  - 函数名使用PascalCase
  - 变量名使用camelCase
  - 添加详细注释

```c
// 良好的代码示例
/**
 * @brief 读取ADC传感器数据
 * @param channel ADC通道号
 * @return uint16_t ADC原始值
 */
uint16_t ReadSensorData(uint8_t channel) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    return HAL_ADC_GetValue(&hadc1);
}
```

#### ESP32固件开发
- **位置**: `ESP-IDF/plant_monitor/`
- **开发环境**: ESP-IDF v4.4+
- **编码规范**:
  - 遵循ESP-IDF编码规范
  - 使用snake_case命名
  - 适当的错误处理
  - 添加ESP_LOG日志

```c
// 良好的代码示例
static const char *TAG = "TCP_SERVER";

esp_err_t tcp_server_init(void) {
    ESP_LOGI(TAG, "Starting TCP server on port %d", TCP_PORT);
    
    int listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (listen_sock < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        return ESP_FAIL;
    }
    
    // ... 其他代码
    return ESP_OK;
}
```

#### Qt应用开发
- **位置**: `Qt/plant_monitor/`
- **开发环境**: Qt 5.12+ 和 Qt Creator
- **编码规范**:
  - 遵循Qt编码规范
  - 使用camelCase命名
  - 信号槽机制的正确使用
  - 适当的内存管理

```cpp
// 良好的代码示例
void PlantMonitor::onDataReceived(const QString &data) {
    qDebug() << "Received data:" << data;
    
    if (!validateDataFormat(data)) {
        qWarning() << "Invalid data format received";
        return;
    }
    
    parseAndDisplayData(data);
}
```

### 2. 文档贡献

#### 文档类型
- **README**: 项目介绍和快速开始
- **API文档**: 函数和接口说明
- **用户指南**: 使用教程和故障排除
- **开发指南**: 开发环境和编码规范

#### 文档规范
- 使用Markdown格式
- 添加适当的标题层级
- 包含代码示例
- 添加截图和图表
- 保持中英文对照

### 3. 测试贡献

#### 测试类型
- **单元测试**: 单个函数的测试
- **集成测试**: 模块间交互测试
- **硬件测试**: 在实际硬件上的测试
- **性能测试**: 系统性能和稳定性测试

#### 测试指南
```cpp
// Qt单元测试示例
class TestDataParser : public QObject {
    Q_OBJECT
private slots:
    void testValidDataParsing();
    void testInvalidDataHandling();
};

void TestDataParser::testValidDataParsing() {
    DataParser parser;
    QString testData = "h25.5,60.0,75.0,350~";
    SensorData result = parser.parse(testData);
    
    QCOMPARE(result.temperature, 25.5);
    QCOMPARE(result.humidity, 60.0);
    QVERIFY(result.isValid());
}
```

## 📝 提交规范

### Commit Message 格式

使用以下格式的提交信息：

```
<type>(<scope>): <subject>

<body>

<footer>
```

#### Type类型
- `feat`: 新功能
- `fix`: Bug修复
- `docs`: 文档更新
- `style`: 代码格式调整
- `refactor`: 代码重构
- `test`: 测试相关
- `chore`: 构建或辅助工具

#### 示例
```
feat(stm32): add soil moisture sensor support

- Add ADC channel configuration for soil moisture sensor
- Implement sensor data calibration algorithm
- Update data transmission protocol

Closes #123
```

### Pull Request 流程

1. **确保代码质量**
   ```bash
   # 运行测试
   make test
   
   # 检查编译
   make clean && make
   
   # 代码格式检查
   clang-format -i *.c *.h
   ```

2. **更新文档**
   - 更新相关的README文件
   - 添加或修改API文档
   - 更新CHANGELOG.md

3. **创建Pull Request**
   - 提供清晰的PR标题和描述
   - 列出主要变更
   - 关联相关的Issue
   - 添加测试结果截图

4. **PR模板**
   ```markdown
   ## 变更类型
   - [ ] Bug修复
   - [ ] 新功能
   - [ ] 文档更新
   - [ ] 性能优化
   - [ ] 其他

   ## 变更描述
   简要描述此PR的主要变更...

   ## 测试
   - [ ] 已在本地测试
   - [ ] 已运行单元测试
   - [ ] 已在硬件上验证

   ## 相关Issue
   Closes #123

   ## 截图
   如有界面变更，请提供截图
   ```

## 🐛 问题报告

### Issue模板

#### Bug报告
```markdown
**Bug描述**
简要描述遇到的问题...

**复现步骤**
1. 进入 '...'
2. 点击 '....'
3. 滚动到 '....'
4. 看到错误

**预期行为**
简要描述您期望发生的情况

**截图**
如适用，添加截图以帮助解释您的问题

**环境信息**
- 操作系统: [如 Windows 10]
- Qt版本: [如 5.15.2]
- ESP-IDF版本: [如 v4.4.2]
- 硬件版本: [如 STM32F103ZET6]

**其他信息**
添加任何其他相关信息
```

#### 功能请求
```markdown
**功能描述**
简要描述您希望的功能...

**用例**
描述此功能的使用场景...

**解决方案**
描述您希望如何实现此功能...

**替代方案**
描述您考虑的其他解决方案...

**其他信息**
添加任何其他相关信息或截图
```

## 🎯 开发指南

### 代码审查要点

1. **功能性**
   - 代码是否正确实现了预期功能
   - 是否处理了边界情况和错误条件
   - 是否遵循了项目的架构模式

2. **可读性**
   - 代码是否易于理解
   - 变量和函数命名是否清晰
   - 是否有适当的注释

3. **性能**
   - 是否有明显的性能问题
   - 内存使用是否合理
   - 是否有不必要的计算或I/O操作

4. **安全性**
   - 是否有安全漏洞
   - 输入验证是否充分
   - 是否正确处理敏感数据

### 最佳实践

#### STM32开发
- 使用HAL库而非直接寄存器操作
- 合理使用中断和DMA
- 注意栈大小和内存使用
- 实现看门狗机制

#### ESP32开发
- 使用FreeRTOS任务管理
- 合理设置任务优先级和栈大小
- 使用事件组和队列进行通信
- 实现错误恢复机制

#### Qt开发
- 使用信号槽机制而非直接函数调用
- 避免在主线程中进行阻塞操作
- 合理使用智能指针管理内存
- 实现适当的异常处理

## 🏷️ 版本发布

### 发布流程

1. **版本规划**
   - 确定新版本的功能和修复
   - 更新版本号 (语义化版本)
   - 更新CHANGELOG.md

2. **代码冻结**
   - 停止新功能提交
   - 专注于Bug修复和测试
   - 更新文档

3. **测试验证**
   - 在多个平台测试
   - 硬件兼容性测试
   - 性能回归测试

4. **发布准备**
   - 创建发布分支
   - 打标签和生成Release
   - 编写发布说明

### 版本号规则

使用语义化版本 (Semantic Versioning):
- **MAJOR.MINOR.PATCH** (如 1.2.3)
- **MAJOR**: 不兼容的API变更
- **MINOR**: 向后兼容的功能新增
- **PATCH**: 向后兼容的Bug修复

## 🌟 贡献者认可

### 贡献类型
- **代码贡献者**: 提交代码的开发者
- **文档贡献者**: 改进文档的贡献者
- **测试贡献者**: 提供测试和反馈的用户
- **社区贡献者**: 帮助社区讨论和支持的用户

### 认可方式
- 在CONTRIBUTORS.md中列出贡献者
- 在发布说明中感谢贡献者
- 通过GitHub Stars展示优秀贡献
- 邀请活跃贡献者成为项目维护者

## 📞 联系我们

- **GitHub Issues**: [问题讨论](https://github.com/longzheng268/plant_monitor/issues)
- **GitHub Discussions**: [社区讨论](https://github.com/longzheng268/plant_monitor/discussions)
- **项目维护者**: [@longzheng268](https://github.com/longzheng268)

---

## 📜 行为准则

我们致力于为每个人提供友好、安全和受欢迎的环境。请遵守以下原则：

1. **尊重**: 尊重不同的观点和经验
2. **包容**: 欢迎新贡献者和不同背景的人
3. **专业**: 保持专业和建设性的讨论
4. **协作**: 共同努力解决问题和改进项目

违反行为准则的行为将不被容忍，我们保留删除评论、提交和禁止用户的权利。

---

<div align="center">
  <p><strong>感谢您的贡献！</strong></p>
  <p>每一份贡献都让这个项目变得更好！</p>
</div>