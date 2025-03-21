# cJSON 需求文档与开发文档

## 需求文档

### 1. 项目概述

#### 1.1 项目背景
cJSON 是一个轻量级的 C 语言 JSON 解析和生成库，旨在提供简单易用的 JSON 处理功能。该库采用 MIT 许可证，可以在商业和非商业项目中自由使用。

#### 1.2 项目目标
开发一个高效、易用、可靠的 JSON 解析和生成库，满足企业级应用对 JSON 数据处理的需求。

### 2. 功能需求

#### 2.1 核心功能
| 功能ID | 功能描述                | 优先级 | 状态   |
| ------ | ----------------------- | ------ | ------ |
| F001   | JSON 文本解析           | 高     | 已实现 |
| F002   | JSON 文本生成           | 高     | 已实现 |
| F003   | 支持所有 JSON 数据类型  | 高     | 已实现 |
| F004   | JSON 节点的增删改查操作 | 高     | 已实现 |
| F005   | 格式化和非格式化输出    | 中     | 已实现 |
| F006   | 自定义内存管理          | 中     | 已实现 |
| F007   | UTF-8 编码支持          | 中     | 已实现 |
| F008   | JSON 文档的复制和引用   | 中     | 已实现 |
| F009   | JSON 文本最小化         | 低     | 已实现 |

#### 2.2 数据类型支持
- null
- boolean (true/false)
- number (整数和浮点数)
- string (UTF-8 编码)
- array
- object

### 3. 非功能需求

#### 3.1 性能需求
| 需求ID | 需求描述 | 指标                                     |
| ------ | -------- | ---------------------------------------- |
| NF001  | 内存占用 | 最小化内存占用，适合嵌入式系统           |
| NF002  | 解析速度 | 能够在合理时间内解析中等大小的 JSON 文档 |
| NF003  | 生成速度 | 能够在合理时间内生成中等大小的 JSON 文档 |

#### 3.2 兼容性需求
| 需求ID | 需求描述        | 指标                            |
| ------ | --------------- | ------------------------------- |
| NF004  | 编译器兼容性    | 支持 ANSI C (C89/C90)           |
| NF005  | 平台兼容性      | 支持主流操作系统和硬件平台      |
| NF006  | JSON 标准兼容性 | 符合 ECMA-404 JSON 数据交换标准 |

#### 3.3 可靠性需求
| 需求ID | 需求描述 | 指标                               |
| ------ | -------- | ---------------------------------- |
| NF007  | 错误处理 | 提供清晰的错误信息和错误位置       |
| NF008  | 内存泄漏 | 无内存泄漏                         |
| NF009  | 异常处理 | 对格式错误的 JSON 文本能够优雅处理 |

#### 3.4 可维护性需求
| 需求ID | 需求描述 | 指标                       |
| ------ | -------- | -------------------------- |
| NF010  | 代码结构 | 清晰的代码结构和模块化设计 |
| NF011  | 文档     | 完整的 API 文档和使用示例  |
| NF012  | 测试     | 单元测试覆盖率 > 80%       |

### 4. 接口需求

#### 4.1 API 接口
提供 C 语言 API 接口，包括但不限于：
- 解析函数
- 生成函数
- 节点操作函数
- 查询函数
- 内存管理函数

#### 4.2 外部依赖
- 标准 C 库
- 数学库 (math.h)

## 开发文档

### 1. 架构设计

#### 1.1 整体架构
cJSON 库采用简单的模块化设计，主要包括以下模块：
- 解析模块：负责将 JSON 文本解析为内存中的数据结构
- 生成模块：负责将内存中的数据结构转换为 JSON 文本
- 节点操作模块：负责对 JSON 节点进行增删改查操作
- 内存管理模块：负责内存的分配和释放

#### 1.2 核心数据结构
```c
typedef struct cJSON {
    struct cJSON *next, *prev;   // 双向链表，用于连接同级节点
    struct cJSON *child;         // 子节点，用于表示数组或对象的内容
    int type;                    // 节点类型，如 null、boolean、number、string、array、object
    char *valuestring;           // 字符串值
    int valueint;                // 整数值
    double valuedouble;          // 浮点数值
    char *string;                // 对象的键名
} cJSON;
```

### 2. API 详细说明

#### 2.1 解析函数

##### 2.1.1 cJSON_Parse
```c
cJSON *cJSON_Parse(const char *value);
```
**功能**：解析 JSON 文本，创建 cJSON 对象树。  
**参数**：

- value: 要解析的 JSON 文本字符串

**返回值**：
- 成功：返回 cJSON 对象树的根节点
- 失败：返回 NULL

##### 2.1.2 cJSON_ParseWithOpts
```c
cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);
```
**功能**：带选项的 JSON 解析函数。  
**参数**：

- value: 要解析的 JSON 文本字符串
- return_parse_end: 解析结束位置
- require_null_terminated: 是否要求 JSON 文本以 NULL 结尾

**返回值**：

- 成功：返回 cJSON 对象树的根节点
- 失败：返回 NULL

#### 2.2 生成函数

##### 2.2.1 cJSON_Print
```c
char *cJSON_Print(cJSON *item);
```
**功能**：生成格式化的 JSON 文本。  
**参数**：
- item: cJSON 对象树的根节点

**返回值**：
- 成功：返回格式化的 JSON 文本字符串（需要使用 cJSON_free 释放）
- 失败：返回 NULL

##### 2.2.2 cJSON_PrintUnformatted
```c
char *cJSON_PrintUnformatted(cJSON *item);
```
**功能**：生成非格式化的 JSON 文本。  
**参数**：
- item: cJSON 对象树的根节点

**返回值**：
- 成功：返回非格式化的 JSON 文本字符串（需要使用 cJSON_free 释放）
- 失败：返回 NULL

##### 2.2.3 cJSON_PrintBuffered
```c
char *cJSON_PrintBuffered(cJSON *item, int prebuffer, int fmt);
```
**功能**：使用预分配缓冲区生成 JSON 文本。  
**参数**：
- item: cJSON 对象树的根节点
- prebuffer: 预分配缓冲区大小
- fmt: 是否格式化输出

**返回值**：
- 成功：返回 JSON 文本字符串（需要使用 cJSON_free 释放）
- 失败：返回 NULL

#### 2.3 节点创建函数

| 函数名                                 | 功能描述        |
| -------------------------------------- | --------------- |
| cJSON_CreateNull()                     | 创建 null 节点  |
| cJSON_CreateTrue()                     | 创建 true 节点  |
| cJSON_CreateFalse()                    | 创建 false 节点 |
| cJSON_CreateBool(int b)                | 创建布尔节点    |
| cJSON_CreateNumber(double num)         | 创建数字节点    |
| cJSON_CreateString(const char *string) | 创建字符串节点  |
| cJSON_CreateArray()                    | 创建数组节点    |
| cJSON_CreateObject()                   | 创建对象节点    |

#### 2.4 数组操作函数

| 函数名                                                    | 功能描述             |
| --------------------------------------------------------- | -------------------- |
| cJSON_CreateIntArray(const int *numbers, int count)       | 创建整数数组         |
| cJSON_CreateFloatArray(const float *numbers, int count)   | 创建浮点数数组       |
| cJSON_CreateDoubleArray(const double *numbers, int count) | 创建双精度浮点数数组 |
| cJSON_CreateStringArray(const char **strings, int count)  | 创建字符串数组       |

#### 2.5 节点操作函数

| 函数名                                                       | 功能描述                     |
| ------------------------------------------------------------ | ---------------------------- |
| cJSON_AddItemToArray(cJSON *array, cJSON *item)              | 向数组添加项                 |
| cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item) | 向对象添加项                 |
| cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item) | 向对象添加项（字符串为常量） |
| cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item)     | 向数组添加引用               |
| cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item) | 向对象添加引用               |
| cJSON_DetachItemFromArray(cJSON *array, int which)           | 从数组分离项                 |
| cJSON_DetachItemFromObject(cJSON *object, const char *string) | 从对象分离项                 |
| cJSON_DeleteItemFromArray(cJSON *array, int which)           | 从数组删除项                 |
| cJSON_DeleteItemFromObject(cJSON *object, const char *string) | 从对象删除项                 |
| cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem) | 在数组中插入项               |
| cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem) | 替换数组中的项               |
| cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem) | 替换对象中的项               |

#### 2.6 查询函数

| 函数名                                                 | 功能描述     |
| ------------------------------------------------------ | ------------ |
| cJSON_GetArraySize(cJSON *array)                       | 获取数组大小 |
| cJSON_GetArrayItem(cJSON *array, int item)             | 获取数组项   |
| cJSON_GetObjectItem(cJSON *object, const char *string) | 获取对象项   |

#### 2.7 其他函数

| 函数名                                    | 功能描述                 |
| ----------------------------------------- | ------------------------ |
| cJSON_Duplicate(cJSON *item, int recurse) | 复制 JSON 节点           |
| cJSON_Minify(char *json)                  | 最小化 JSON 字符串       |
| cJSON_Delete(cJSON *c)                    | 删除 JSON 节点及其子节点 |
| cJSON_GetErrorPtr()                       | 获取错误位置             |
| cJSON_InitHooks(cJSON_Hooks* hooks)       | 初始化内存管理钩子       |

### 3. 使用示例

#### 3.1 解析 JSON 文本
```c
const char *json_text = "{\"name\":\"张三\",\"age\":25,\"skills\":[\"C\",\"Java\",\"Python\"]}";
cJSON *root = cJSON_Parse(json_text);
if (root) {
    cJSON *name = cJSON_GetObjectItem(root, "name");
    cJSON *age = cJSON_GetObjectItem(root, "age");
    cJSON *skills = cJSON_GetObjectItem(root, "skills");
    
    printf("Name: %s\n", name->valuestring);
    printf("Age: %d\n", age->valueint);
    
    printf("Skills: ");
    int skill_count = cJSON_GetArraySize(skills);
    for (int i = 0; i < skill_count; i++) {
        cJSON *skill = cJSON_GetArrayItem(skills, i);
        printf("%s", skill->valuestring);
        if (i < skill_count - 1) printf(", ");
    }
    printf("\n");
    
    cJSON_Delete(root);
}
```

#### 3.2 创建 JSON 文本
```c
cJSON *root = cJSON_CreateObject();
cJSON_AddStringToObject(root, "name", "张三");
cJSON_AddNumberToObject(root, "age", 25);

cJSON *skills = cJSON_CreateArray();
cJSON_AddItemToArray(skills, cJSON_CreateString("C"));
cJSON_AddItemToArray(skills, cJSON_CreateString("Java"));
cJSON_AddItemToArray(skills, cJSON_CreateString("Python"));
cJSON_AddItemToObject(root, "skills", skills);

char *json_text = cJSON_Print(root);
printf("%s\n", json_text);

cJSON_free(json_text);
cJSON_Delete(root);
```

#### 3.3 自定义内存管理
```c
void *my_malloc(size_t sz) {
    // 自定义内存分配函数
    return malloc(sz);
}

void my_free(void *ptr) {
    // 自定义内存释放函数
    free(ptr);
}

// 初始化自定义内存管理
cJSON_Hooks hooks;
hooks.malloc_fn = my_malloc;
hooks.free_fn = my_free;
cJSON_InitHooks(&hooks);
```

### 4. 错误处理

#### 4.1 获取错误位置
```c
const char *json_text = "{\"name\":\"张三\",\"age\":25,\"skills\":[\"C\",\"Java\",\"Python\"}";
cJSON *root = cJSON_Parse(json_text);
if (!root) {
    const char *error_ptr = cJSON_GetErrorPtr();
    printf("Error before: %s\n", error_ptr);
}
```

### 5. 性能优化建议

1. **预分配缓冲区**：使用 `cJSON_PrintBuffered` 而不是 `cJSON_Print` 可以减少内存分配次数，提高性能。

2. **减少字符串复制**：对于不需要修改的字符串，可以使用 `cJSON_AddItemToObjectCS` 而不是 `cJSON_AddItemToObject`，避免字符串复制。

3. **使用引用**：对于需要在多个地方使用相同 JSON 节点的情况，可以使用 `cJSON_AddItemReferenceToArray` 或 `cJSON_AddItemReferenceToObject`，避免复制整个节点树。

4. **自定义内存管理**：对于特定应用场景，可以实现自定义的内存分配和释放函数，以优化内存使用。

5. **批量处理**：尽量批量创建和处理 JSON 节点，减少函数调用开销。

### 6. 线程安全性

cJSON 库本身不是线程安全的。在多线程环境中使用 cJSON 时，需要采取以下措施：

1. **对象隔离**：每个线程使用自己的 cJSON 对象树。
2. **互斥锁**：在访问共享的 cJSON 对象树时，使用互斥锁保护。
3. **读写锁**：对于读多写少的场景，可以使用读写锁提高并发性能。

### 7. 内存管理

#### 7.1 内存分配与释放
cJSON 库使用以下函数进行内存管理：
- `cJSON_malloc`：分配内存
- `cJSON_free`：释放内存

默认情况下，这些函数分别映射到标准库的 `malloc` 和 `free`。可以通过 `cJSON_InitHooks` 函数自定义内存管理。

#### 7.2 内存泄漏防范
1. 每个通过 cJSON 创建的对象最终都需要使用 `cJSON_Delete` 释放。
2. 所有通过 `cJSON_Print`、`cJSON_PrintUnformatted` 或 `cJSON_PrintBuffered` 生成的字符串需要使用 `cJSON_free` 释放。
3. 使用引用节点时，只需要释放原始节点，引用节点会自动处理。

### 8. 错误处理策略

#### 8.1 解析错误
当 JSON 解析失败时，`cJSON_Parse` 和 `cJSON_ParseWithOpts` 返回 NULL，并设置错误位置指针，可以通过 `cJSON_GetErrorPtr` 获取。

#### 8.2 内存分配失败
当内存分配失败时，相关函数通常返回 NULL。应用程序应该检查返回值，并适当处理内存分配失败的情况。

#### 8.3 错误恢复
在处理大型 JSON 文档时，可以考虑分段解析，以便在部分解析失败时能够恢复并继续处理其余部分。

### 9. 测试策略

#### 9.1 单元测试
为每个主要功能编写单元测试，包括但不限于：
- 解析各种类型的 JSON 值
- 生成各种类型的 JSON 值
- 节点操作（增删改查）
- 错误处理
- 内存管理

#### 9.2 集成测试
测试 cJSON 库与其他系统组件的集成，确保能够正确处理实际应用中的 JSON 数据。

#### 9.3 性能测试
测试 cJSON 库在处理不同大小和复杂度的 JSON 文档时的性能，包括解析速度、生成速度和内存使用情况。

#### 9.4 压力测试
测试 cJSON 库在高负载情况下的稳定性，包括处理大型 JSON 文档和高频率的解析/生成操作。

### 10. 部署指南

#### 10.1 编译与链接
将 cJSON.c 和 cJSON.h 文件添加到项目中，并在编译时链接数学库：
```bash
gcc -o myapp myapp.c cJSON.c -lm
```

#### 10.2 依赖项
- 标准 C 库
- 数学库 (math.h)

#### 10.3 平台兼容性
cJSON 库设计为跨平台兼容，可以在以下平台上使用：
- Windows
- Linux
- macOS
- 嵌入式系统（需要标准 C 库支持）

### 11. 维护计划

#### 11.1 版本控制
使用语义化版本控制（Semantic Versioning）管理版本：
- 主版本号：不兼容的 API 变更
- 次版本号：向后兼容的功能性新增
- 修订号：向后兼容的问题修正

#### 11.2 问题跟踪
使用 GitHub Issues 或其他问题跟踪系统记录和跟踪 bug、功能请求和改进建议。

#### 11.3 代码审查
所有代码变更都应该经过代码审查，确保代码质量和一致性。

#### 11.4 文档更新
随着代码的变更，及时更新文档，确保文档与代码保持同步。

### 12. 安全考虑

#### 12.1 输入验证
在解析 JSON 文本时，cJSON 库会验证输入的格式，但应用程序应该在将数据传递给 cJSON 库之前进行适当的输入验证。

#### 12.2 缓冲区溢出防范
cJSON 库在处理字符串时会分配足够的内存，但应用程序应该确保不会传递过大的输入，以避免潜在的内存问题。

#### 12.3 敏感数据处理
如果 JSON 文档包含敏感数据，应用程序应该在处理完成后及时清除内存，避免敏感数据泄露。

### 13. 常见问题与解决方案

#### 13.1 解析失败
**问题**：JSON 解析失败，`cJSON_Parse` 返回 NULL。  
**解决方案**：

1. 使用 `cJSON_GetErrorPtr` 获取错误位置。
2. 检查 JSON 文本格式是否正确。
3. 确保 JSON 文本是有效的 UTF-8 编码。

#### 13.2 内存泄漏
**问题**：使用 cJSON 库后出现内存泄漏。  
**解决方案**：
1. 确保每个通过 cJSON 创建的对象都使用 `cJSON_Delete` 释放。
2. 确保所有通过 `cJSON_Print` 等函数生成的字符串都使用 `cJSON_free` 释放。
3. 使用内存泄漏检测工具（如 Valgrind）定位泄漏点。

#### 13.3 性能问题
**问题**：处理大型 JSON 文档时性能不佳。  
**解决方案**：
1. 使用 `cJSON_PrintBuffered` 预分配缓冲区。
2. 考虑使用流式解析器（cJSON 库本身不支持，可能需要其他库）。
3. 优化内存管理，使用自定义的内存分配和释放函数。

### 14. 附录

#### 14.1 完整 API 列表
提供 cJSON 库所有公开 API 的完整列表，包括函数签名、参数说明和返回值说明。

#### 14.2 JSON 格式规范
简要介绍 JSON 格式规范，包括语法、数据类型和常见用法。

#### 14.3 参考资料
- [JSON 官方网站](https://www.json.org/)
- [ECMA-404 JSON 数据交换标准](https://www.ecma-international.org/publications-and-standards/standards/ecma-404/)
- [cJSON GitHub 仓库](https://github.com/DaveGamble/cJSON)

---

这份企业级文档提供了 cJSON 库的全面信息，包括需求、设计、实现、测试、部署和维护等方面。开发团队可以根据这份文档进行开发、测试和维护工作，确保 cJSON 库能够满足企业级应用的需求。
