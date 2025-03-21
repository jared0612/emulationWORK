#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

// 测试创建简单的 JSON 对象
void test_create_simple_object() {
    printf("\n=== 测试创建简单 JSON 对象 ===\n");
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "张三");
    cJSON_AddNumberToObject(root, "age", 25);
    cJSON_AddBoolToObject(root, "student", 1);
    
    char *printed = cJSON_Print(root);
    printf("创建的 JSON: \n%s\n", printed);
    
    free(printed);
    cJSON_Delete(root);
}

// 测试创建和解析数组
void test_array() {
    printf("\n=== 测试 JSON 数组 ===\n");
    // 创建数组
    int numbers[] = {1, 2, 3, 4, 5};
    cJSON *array = cJSON_CreateIntArray(numbers, 5);
    
    char *printed = cJSON_Print(array);
    printf("创建的数组: \n%s\n", printed);
    
    // 测试数组访问
    printf("数组元素: ");
    for(int i = 0; i < cJSON_GetArraySize(array); i++) {
        cJSON *item = cJSON_GetArrayItem(array, i);
        printf("%d ", item->valueint);
    }
    printf("\n");
    
    free(printed);
    cJSON_Delete(array);
}

// 测试解析 JSON 字符串
void test_parse() {
    printf("\n=== 测试解析 JSON ===\n");
    const char *json_string = "{\"name\":\"李四\",\"age\":30,\"scores\":[85,90,95]}";
    
    cJSON *root = cJSON_Parse(json_string);
    if (!root) {
        printf("解析错误: [%s]\n", cJSON_GetErrorPtr());
        return;
    }
    
    // 访问解析后的数据
    cJSON *name = cJSON_GetObjectItem(root, "name");
    cJSON *age = cJSON_GetObjectItem(root, "age");
    cJSON *scores = cJSON_GetObjectItem(root, "scores");
    
    printf("解析结果:\n");
    printf("姓名: %s\n", name->valuestring);
    printf("年龄: %d\n", age->valueint);
    printf("分数: ");
    for(int i = 0; i < cJSON_GetArraySize(scores); i++) {
        cJSON *score = cJSON_GetArrayItem(scores, i);
        printf("%d ", score->valueint);
    }
    printf("\n");
    
    cJSON_Delete(root);
}

// 测试嵌套对象
void test_nested_object() {
    printf("\n=== 测试嵌套对象 ===\n");
    cJSON *root = cJSON_CreateObject();
    cJSON *address = cJSON_CreateObject();
    
    cJSON_AddStringToObject(root, "name", "王五");
    cJSON_AddItemToObject(root, "address", address);
    cJSON_AddStringToObject(address, "city", "北京");
    cJSON_AddStringToObject(address, "street", "朝阳路");
    cJSON_AddNumberToObject(address, "postcode", 100025);
    
    char *printed = cJSON_Print(root);
    printf("嵌套对象: \n%s\n", printed);
    
    free(printed);
    cJSON_Delete(root);
}

int main() {
    printf("开始测试 cJSON 库...\n");
    
    test_create_simple_object();
    test_array();
    test_parse();
    test_nested_object();
    
    printf("\n所有测试完成！\n");
    return 0;
}