#include <stdio.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

/*TO DO:
    实现头文件中声明的函数
    创建测试文件来测试json解析

*/
static const char *ep;

const char *cJSON_GetErrorPtr(void) {return ep;}

static int cJSON_strcasecmp(const char*s1, const char *s2) {
    if (!s1) return (s1==s2)?0:1; if(!s2) return 1;
    for(; tolower(*s1) == tolower(*s2); ++s1, ++s2) if (*s1 == 0) return 0;
    return tolower(*(const unsigned char *)s1) - tolower(*(const unsigned char *)s2);
}

static void *(*cJSON_malloc)(size_t sz) = malloc;
static void (*cJSON_free)(void *ptr) = free;

static char* cJSON_strup(const char* str) 
{
    size_t len;
    char* copy;

    len = strlen(str) + 1;//把\0也拷贝了；
    if (!(copy = (char*)cJSON_malloc(len))) return 0;
    memcpy(copy, str, len);//内存级别的拷贝；
    return copy;//已经在局部函数中进行了分配并没有进行释放，
}

void cJSON_InitHooks(cJSON_Hooks* hooks) 
{
    //如果传入结构体是空的
    if (!hooks) {
        cJSON_malloc = malloc;
        cJSON_free = free;
        return;
    }
    //如果传入参数不为空
    cJSON_malloc = (hooks->malloc_fn)?hooks->malloc_fn:malloc;
    cJSON_free = (hooks->free_fn)?hooks->free_fn:free;
}

static cJSON* cJSON_New_Item(void)
{
    cJSON *node = (cJSON *)cJSON_malloc(sizeof(cJSON));
    if(node) memset(node, 0, sizeof(cJSON));
    return node;
}

void cJSON_Delete(cJSON *c) 
{
    //简单的节点删除，多了验证节点类型的一步；
    cJSON *next;
    while (c) {
        next = c->next;
        if (!(c->type&cJSON_IsReference) && (c->child)) cJSON_Delete(c->child);
        if (!(c->type&cJSON_IsReference) && (c->valuestring)) cJSON_free(c->valuestring);
        if (!(c->type&cJSON_StringIsConst) && (c->string)) cJSON_free(c->string);
        cJSON_free(c);
        c = next;
    }
}

static const char *parse_number(cJSON *item, const char *num) {
    double n = 0, sign = 1, scale = 0;
    int subscale = 0, signsubscale = 1;

    if(*num == '-') sign = -1,num++;
    if(*num == '0') num++;
    if(*num >= '1' && *num <= '9') do n = (n * 10.0) + (*num++ - '0'); while (*num >= '0' && *num <= '9');
    if(*num == '.' && num[1] >= '0' && num[1] <= '9') {num++; do n = (n * 10.0) + (*num++ - '0'), scale--; while (*num >= '0' && *num <= '9');} 
    if(*num == 'e' || *num == 'E') 
    {
        num++; 
        if (*num == '+') num++;
        else if (*num == '-') signsubscale = -1, num++;
        while(*num >= '0' && *num <= '9') subscale = (subscale*10) + (*num++ - '0');
    }

    n = sign*n*pow(10.0, (scale+subscale*signsubscale));

    item->valuedouble = n;
    item->valueint = (int)n;
    item->type = cJSON_Number;

    return num;
}

