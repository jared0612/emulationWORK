#ifndef __cJSON_H__
#define __cJSON_H__

#ifdef __cplusplus
extern "C" 
{
#endif

// 定义 JSON 数据类型的常量
#define cJSON_False 0          // 布尔假
#define cJSON_True 1           // 布尔真
#define cJSON_Null 2           // 空值
#define cJSON_Number 3         // 数字
#define cJSON_String 4         // 字符串
#define cJSON_Array 5          // 数组
#define cJSON_Object 6         // 对象
// 添加其他类型元素

// 定义额外的标志位
#define cJSON_IsReference 256    // 是否为引用
#define cJSON_StringIsContent 512 // 字符串是否为内容

// 定义 cJSON 结构体
typedef struct cJSON {
    struct cJSON *next, *prev; // 链表指针
    struct cJSON *child;       // 子节点指针
    int type;                  // 元素类型

    char *valuestring;         // 字符串值
    int valueint;              // 整数值
    double valuedouble;        // 浮点数值

    char *string;              // 键名字符串
} cJSON;

// 创建钩子结构体
typedef struct cJSON_Hooks {
    void *(*malloc_fn)(size_t sz); // 自定义内存分配函数
    void *(*free_fn)(void *ptr);   // 自定义内存释放函数
} cJSON_Hooks;

// 初始化钩子函数
extern void cJSON_InitHooks(cJSON_Hooks *hooks);

// 解析 JSON 字符串
extern cJSON *cJSON_Parse(const char *value);

// 格式化打印 JSON 对象
extern char *cJSON_Print(cJSON *item);

// 格式化打印 JSON 对象（不带格式）
extern char *cJSON_PrintUnformatted(cJSON *item);

// 缓冲区格式化打印 JSON 对象
extern char *cJSON_PrintBuffered(cJSON *item, int prebuffer, int fmt);

// 删除 JSON 节点及其子节点
extern void *cJSON_Delete(cJSON *c);

// 获取数组大小
extern int cJSON_GetArraySize(cJSON *array);

// 获取数组中的指定项
extern cJSON *cJSON_GetArrayItem(cJSON *array, int item);

// 获取对象中的指定键对应的项
extern cJSON *cJSON_GetObjectItem(cJSON *object, const char *string);

// 获取最近一次解析错误的位置
extern const char *cJSON_GetErrorPtr(void);

// 创建一个 null 类型的 JSON 节点
extern cJSON *cJSON_CreateNull(void);

// 创建一个 false 类型的 JSON 节点
extern cJSON *cJSON_CreateFalse(void);

// 创建一个 true 类型的 JSON 节点
extern cJSON *cJSON_CreateTrue(void);

// 创建一个 bool 类型的 JSON 节点
extern cJSON *cJSON_CreateBool(int b);

// 创建一个 number 类型的 JSON 节点
extern cJSON *cJSON_CreateNumber(double num);

// 创建一个 string 类型的 JSON 节点
extern cJSON *cJSON_CreateString(const char *string);

// 创建一个 array 类型的 JSON 节点
extern cJSON *cJSON_CreateArray(void);

// 创建一个 object 类型的 JSON 节点
extern cJSON *cJSON_CreateObject(void);

// 创建一个包含整数数组的 JSON 数组
extern cJSON *cJSON_CreateIntArray(const int *numbers, int count);

// 创建一个包含浮点数数组的 JSON 数组
extern cJSON *cJSON_CreateFloatArray(const float *numbers, int count);

// 创建一个包含双精度浮点数数组的 JSON 数组
extern cJSON *cJSON_CreateDoubleArray(const double *numbers, int count);

// 创建一个包含字符串数组的 JSON 数组
extern cJSON *cJSON_CreateStringArray(const char **strings, int count);

// 将一个 JSON 节点添加到数组中
extern void cJSON_AddItemToArray(cJSON *array, cJSON *item);

// 将一个 JSON 节点添加到对象中
extern void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);

// 将一个 JSON 节点添加到对象中（使用常量字符串）
extern void cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);

// 将一个 JSON 节点的引用添加到数组中
extern void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);

// 将一个 JSON 节点的引用添加到对象中
extern void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

// 从数组中分离一个 JSON 节点
extern cJSON *cJSON_DetachItemFromArray(cJSON *array, int which);

// 从数组中删除一个 JSON 节点
extern void  cJSON_DeleteItemFromArray(cJSON *array, int which);

// 从对象中分离一个 JSON 节点
extern cJSON *cJSON_DetachItemFromObject(cJSON *object, const char *string);

// 从对象中删除一个 JSON 节点
extern void  cJSON_DeleteItemFromObject(cJSON *object, const char *string);

// 在数组中插入一个新的 JSON 节点
extern void cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem);

// 替换数组中的某个 JSON 节点
extern void cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);

// 替换对象中的某个 JSON 节点
extern void cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);

// 复制一个 JSON 节点，recurse 不为 0 时递归复制子节点
extern cJSON *cJSON_Duplicate(cJSON *item, int recurse);

// 使用选项解析 JSON 字符串
extern cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);

// 最小化 JSON 字符串
extern void cJSON_Minify(char *json);

// 向对象添加 null 类型的键值对
#define cJSON_AddNullToObject(object, name)  cJSON_AddItemToObject(object, name, cJSON_CreateNull())

// 向对象添加 true 类型的键值对
#define cJSON_AddTrueToObject(object, name)  cJSON_AddItemToObject(object, name, cJSON_CreateTrue())

// 向对象添加 false 类型的键值对
#define cJSON_AddFalseToObject(object, name) cJSON_AddItemToObject(object, name, cJSON_CreateFalse())

// 向对象添加 bool 类型的键值对
#define cJSON_AddBoolToObject(object, name, b) cJSON_AddItemToObject(object, name, cJSON_CreateBool(b))

// 向对象添加 number 类型的键值对
#define cJSON_AddNumberToObject(object, name, n) cJSON_AddItemToObject(object, name, cJSON_CreateNumber(n))

// 向对象添加 string 类型的键值对
#define cJSON_AddStringToObject(object, name, s) cJSON_AddItemToObject(object, name, cJSON_CreateString(s))

// 设置整数和浮点数值
#define cJSON_SetIntValue(object, val) ((object) && ((object)->valueint = (object)->valuedouble = (val)))

// 设置浮点数值
#define cJSON_SetNumberValue(object, val) ((object) && ((object)->valueint = (object)->valuedouble = (val)))

#ifdef __cplusplus
}
#endif

#endif



