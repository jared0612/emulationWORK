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
//找到x的最小二次幂
static int pow2gt (int x) {
    --x;
    x|=x>>1;
    x|=x>>2;
    x|=x>>4;
    x|=x>>8;
    x|=x>>16;
    return x + 1;
}

typedef struct {
    char* buffer;
    int length;
    int offset;
}printbuffer;

static char* ensure(printbuffer *p, int needed) {
    char *newbuffer;
    int newsize;
    if(!p || !p->buffer) return 0;
    needed += p->offset;
    if(needed <= p->length) return p->buffer + p->offset;

    newsize = pow2gt(needed);
    newbuffer = (char*) cJSON_malloc(newsize);
    if(!newbuffer) {
        cJSON_free(p->buffer);
        p->length = 0;
        p->offset = 0;
        return 0;
    } else {
        memcpy(newbuffer, p->buffer, p->length);
    }
    cJSON_free(p->buffer);
    p->length = newsize;
    p->buffer = newbuffer;
    return newbuffer+p->offset;
}

static int update(printbuffer *p) {
    char *str;
    if(!p || !p->buffer) return 0;
    str = p->buffer + p->offset;
    return p->offset + strlen(str);
}

static char* print_number(cJSON *item, printbuffer *p) {
    char *str = 0;
    double d = item->valuedouble;
    if(d == 0) {
        if(p) str = ensure(p, 2);
        else str = (char*) cJSON_malloc(2);
        if(str) strcpy(str, "0");//分配空间，并填充为0；
    } else if (fabs(((double)item->valueint) - d) <= DBL_EPSILON && d <= INT_MAX && d >= INT_MIN) {
        if(p) str = ensure(p, 21);
        else str = (char*) cJSON_malloc(21);
        if(str) sprintf(str, "%d", item->valueint);
    } else {
        if(p) str = ensure(p, 64);
        else str = (char*) cJSON_malloc(64);
        if(str) {
            if(fabs(floor(d) - d) <= DBL_EPSILON && fabs(d) < 1.0e60) sprintf(str, "%.0f", d);
            else if(fabs(d) < 1.0e-6|| fabs(d) > 1.0e9) sprintf(str, "%e", d);
            else sprintf(str, "%f", d);
        }
    }
    return str;
}

static unsigned parse_hex4(const char *str) {
    unsigned h = 0;
    if(*str >= '0' && *str <= '9') h += (*str - '0'); else if (*str >= 'A' && *str <= 'F') h += 10 + (*str - 'A'); else if (*str >= 'a' && *str <= 'f') h += 10 + (*str - 'a'); else {return 0;}
    h = h << 4; 
    str++;
    if(*str >= '0' && *str <= '9') h += (*str - '0'); else if (*str >= 'A' && *str <= 'F') h += 10 + (*str - 'A'); else if (*str >= 'a' && *str <= 'f') h += 10 + (*str - 'a'); else {return 0;}
    h = h << 4; 
    str++;
    if(*str >= '0' && *str <= '9') h += (*str - '0'); else if (*str >= 'A' && *str <= 'F') h += 10 + (*str - 'A'); else if (*str >= 'a' && *str <= 'f') h += 10 + (*str - 'a'); else {return 0;}
    h = h << 4; 
    str++;
    if(*str >= '0' && *str <= '9') h += (*str - '0'); else if (*str >= 'A' && *str <= 'F') h += 10 + (*str - 'A'); else if (*str >= 'a' && *str <= 'f') h += 10 + (*str - 'a'); else {return 0;}
    return h;
}

static const unsigned char firstByteMark[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
static const char *parse_string(cJSON *item, const char *str) {
    //解析得到原始字符；
    const char *ptr = str + 1;
    char *ptr2;
    char *out;
    int len = 0;
    unsigned uc, uc2;

    if (*str != '\"') {
        ep = str;
        return 0;
    }
    while(*ptr != '\"' && *ptr && ++len) if(*ptr++ == '\\') ptr++;
    out = (char *)cJSON_malloc(len + 1);
    if (!out) return 0;

    ptr = str + 1;
    ptr2 = out;

    while (*ptr != '\"' && *ptr) {
        if (*ptr != '\\') *ptr2++ = *ptr++;
        else {
            ptr++;
            switch(*ptr) {
                case 'b':*ptr2++ = '\b'; break;
                case 'f':*ptr2++ = '\f'; break;
                case 'n':*ptr2++ = '\n'; break;
                case 'r':*ptr2++ = '\r'; break;
                case 't':*ptr2++ = '\t'; break;
                case 'u': {
                    uc = parse_hex4(ptr + 1); ptr += 4;

                    if ((uc>=0xDC00 && uc <= 0xDFFF) || uc == 0) break;

                    if (uc >= 0xD800 && uc <= 0xDBFF) {
                        if (ptr[1] != '\\' || ptr[2] != 'u') break;
                        uc2 = parse_hex4(ptr + 3);
                        ptr += 6;
                        if (uc2 < 0xDC00 || uc2>0xDFFF) break;
                        uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));

                    }

                    len = 4;
                    if (uc & 0x80) len = 1;
                    else if (uc < 0x800) len = 2;
                    else if (uc < 0x10000) len = 3;
                    ptr2 += len;

                    switch(len) {
                        case 4: *--ptr2 = ((uc | 0x80) & 0xBF); uc >>= 6;
                        case 3: *--ptr2 = ((uc | 0x80) & 0xBF); uc >>= 6;
                        case 2: *--ptr2 = ((uc | 0x80) & 0xBF); uc >>= 6;
                        case 1: *--ptr2 = (uc | firstByteMark[len]);
                    }
                    ptr2 += len;
                    break;
                

                }
                default:
                    *ptr2++ = *ptr;
                    break;
            }
            ptr++;
        }
    }
    *ptr2 = 0;
    if (*ptr == '\"') ptr++;
    item->valuestring = out;
    item->type = cJSON_String;
    return ptr;
}

static char *print_string_ptr(const char *str, printbuffer *p) {

}

static char *print_string(cJSON *item, printbuffer *p) {return print_string_ptr(item->valuestring, p);}


static const char *parse_value(cJSON *item, const char *value);
static char *print_value(cJSON *item, int depth, int fmt, printbuffer *p);
static const char *parse_array(cJSON *item, const char *value);
static char *print_array(cJSON *item, int depth, int fmt, printbuffer *p);
static const char *parse_object(cJSON *item, const char *value);
static char *print_object(cJSON *item, int depth, int fmt, printbuffer *p);

//跳过换行和空格，ascii码的32是空格，因此在32以下范围都进行跳过；
static const char* skip(const char *in) {while(in && *in && (unsigned char)*in <= 32) in++; return in;}

//处理的都是字符数组的格式,选择选项选择来进行处理；
cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated) {
    const char *end = 0;
    cJSON *c = cJSON_New_Item();
    ep = 0;
    if (!c) return 0;

    end = parse_value(c, skip(value));
    if(!end) {cJSON_Delete(c); return 0;}

    if(require_null_terminated) {
        end = skip(end); 
        if (*end) 
        {
            cJSON_Delete(c); 
            ep = end;
            return 0;
        }
    }
    if(return_parse_end) *return_parse_end = end;//如果需要解析多个字符，可以将结尾位置保存；
    return c;
}

//默认解析实现
const char *cJSON_Parse(const char *value) {return cJSON_ParseWithOpts(value, 0, 0);}

char *cJSON_Print(cJSON *item){ return print_value(item, 0, 1, 0);}
char *cJSON_PrintUnformatted(cJSON *item){ return print_value(item, 0, 1, 0);}

char *cJSON_PrintBuffered(cJSON *item, int prebuffer, int fmt) {
    printbuffer p;
    p.buffer = (char*)cJSON_malloc(prebuffer);
    p.length = prebuffer;
    p.offset = 0;
    print_value(item, 0, fmt, &p);
    return p.buffer;
}

static const char *parse_value(cJSON *item, const char *value) {
    if(!value) return 0;
    if(!strncmp(value, "null", 4)) {item->type = cJSON_Null; return value+4;}
    if(!strncmp(value, "false", 5)) {item->type = cJSON_False; return value+5;}
    if(!strncmp(value, "true", 4)) {item->type = cJSON_True; return value+4;}
    if(*value == '\"') {return parse_string(item, value);}
    if(*value == '-' || (*value >= '0' && *value <= '9')) {return parse_number(item, value);}
    if(*value == '[') {return parse_array(item, value);}
    if(*value == '{') {return parse_object(item, value);}

    ep = value;//如果从这里返回说明，出现错误了；
    return 0;
}

static char *print_value(cJSON *item, int depth, int fmt, printbuffer *p) {
    char *out;
    if (!item) return 0;
    if (p) {
        switch ((item->type) & 255)
        {
        case cJSON_Null:
            /* code */
            break;
        case cJSON_False:
            /* code */
            break;
        case cJSON_True:
            /* code */
            break;
        case cJSON_Number:
            /* code */
            break;
        case cJSON_String:
            /* code */
            break;
        case cJSON_Array:
            /* code */
            break;
        case cJSON_Object:
            /* code */
            break;
        }
    } else {
        switch ((item->type) & 255)
        {
            case cJSON_Null:
            /* code */
            out = cJSON_strup("null");
            break;
        case cJSON_False:
            /* code */
            out = cJSON_strup("false");
            break;
        case cJSON_True:
            /* code */
            out = cJSON_strup("true");
            break;
        case cJSON_Number:
            /* code */
            out = print_number(item, 0);
            break;
        case cJSON_String:
            /* code */
            out = print_string(item, 0);
            break;
        case cJSON_Array:
            /* code */
            out = print_array(item, depth, fmt, 0);
            break;
        case cJSON_Object:
            /* code */
            out = print_object(item, depth, fmt, 0);
            break;
        }
    }
    return out;
}
//TO DO core code.
static const char* parse_array(cJSON *item, const char *value){}
static print_array(cJSON *item, int depth, int fmt, printbuffer *p) {}
static const char* parse_object(const *item, const char *value){}
static char print_object(cJSON *item, int depth, int fmt, printbuffer *p ){}

int cJSON_GetArraySize(cJSON *item) {cJSON *c = item->child; int size = 0; while(c) size++, c = c->next; return size;}
//返回数组里的第item个元素
cJSON *cJSON_GetArrayItem(cJSON *array, int item) { cJSON *c = array->child; while(c && item > 0) item--, c = c->next; return c;}
//返回符合string对象的元素
cJSON *cJSON_GetObjectItem(cJSON *object, const char *string) {cJSON *c = object->child; while (c && cJSON_strcasecmp(c->string, string)) c = c->next; return c;}

static void suffix_object(cJSON *prev, cJSON *item) {prev->next = item; item->prev = prev;}
static cJSON *create_reference(cJSON *item) {
    cJSON *ref = cJSON_New_Item();
    if (!ref) return 0;
    memccpy(ref, item, sizeof(item));
    ref->string = 0;
    ref->type |= cJSON_IsReference;
    ref->next = ref->prev = 0;
    return ref; 
}

void cJSON_AddItemToArray(cJSON *array, cJSON *item) {
    cJSON *c = array->child;
    if (!item) return ;
    if (!c) {
        array->child = item;
    } else {
        while(c && c->next) {
            c = c->next;
        }
        suffix_object(c, item);
    }
}
void cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item) {
    if (!item) return;
    if (item->string) cJSON_free(item->string);
    item->string = cJSON_strup(string);
    cJSON_AddItemToArray(object, item);
}

void cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item) {
    if (!item) return;
    if(!(item->type & cJSON_StringIsConst) && item->string) cJSON_free(item->string);
    item->string = (char *)string;
    item->type |= cJSON_StringIsConst;
    cJSON_AddItemToArray(object, item);
}

void cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item) {
    cJSON_AddItemToArray(array, create_reference(item));
}
void cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item) {
    cJSON_AddItemToObject(object, string, create_reference(item));
}

cJSON *cJSON_DetachItemFromArray(cJSON *array, int which) {
    cJSON *c = array->child;
    while(c && which > 0) c = c->next, which--;
    if(!c) return 0;
    if(c->prev) c->prev->next = c->next;
    if(c->next) c->next->prev = c->prev;
    if(c == array->child) array->child = c->next;
    c->prev = c->next = 0;
    return c;
}

void cJSON_DeleteItemFromArray(cJSON *array, int which) {cJSON_Delete(cJSON_DetachItemFromArray(array, which));}
cJSON* cJSON_DetachItemFromObject(cJSON *object, const char *string) {int i = 0; cJSON *c = object->child; while(c && cJSON_strcasecmp(c->string, string)) i++, c = c->next; if(c) return cJSON_DetachItemFromArray(object,i); return 0;}
void cJSON_DeleteItemFromObject(cJSON *object, const char *string) {cJSON_Delete(cJSON_DetachItemFromObject(object, string));}


//插入到对象或数组中
void cJSON_InsertItemInArray(cJSON *array, int which,  cJSON *newitem) {
    cJSON *c= array->child; 
    while(c && which > 0) 
    c = c->next, which--; 
    if (!c) {
        cJSON_AddItemToArray(array, newitem); return;
    }
    //改变指针指向
    newitem->prev = c->prev;
    newitem->next = c;
    c->prev = newitem;
    if (c == array->child) array->child = newitem;
    else newitem->prev->next = newitem;
}

void cJSON_ReplaceItemInArray(cJSON* array, int which, cJSON* newitem) {
    cJSON *c= array->child; 
    while(c && which > 0) 
    c = c->next, which--; 
    if(!c) return;

    newitem->next = c->next;
    newitem->prev = c->prev;
    if(newitem->next) newitem->next->prev = newitem;

    if (c == array->child) array->child = newitem;
    else newitem->prev->next = newitem;    
    c->next = c->prev = 0;
    cJSON_Delete(c);
}

void cJSON_ReplaceItemInObject(cJSON *object, const char* string, cJSON *newitem){
    cJSON *c = object->child; 
    int i = 0; 
    while(c && cJSON_strcasecmp(c->string, string)) i++, c = c->next;
    if (c) 
    {
        newitem->string = cJSON_strup(string);
        cJSON_ReplaceItemInArray(object, i, newitem);
    }
}

//创建基础类型
cJSON* cJSON_CreateNull(void) {cJSON *item = cJSON_New_Item(); if (item) item->type = cJSON_Null; return item;}
cJSON* cJSON_CreateFalse(void) {cJSON *item = cJSON_New_Item(); if (item) item->type = cJSON_False; return item;}
cJSON* cJSON_CreateTrue(void) {cJSON *item = cJSON_New_Item(); if (item) item->type = cJSON_True; return item;}
cJSON* cJSON_CreateArray(void) {cJSON *item = cJSON_New_Item(); if (item) item->type = cJSON_Array; return item;}
cJSON* cJSON_CreateObject(void) {cJSON *item = cJSON_New_Item(); if (item) item->type = cJSON_Object; return item;}
cJSON* cJSON_CreateBool(int b) {cJSON *item = cJSON_New_Item(); if (item) item->type = b?cJSON_True:cJSON_False; return item;}
cJSON* cJSON_CreateNumber(double num) {cJSON *item = cJSON_New_Item(); if (item) { item->type = cJSON_Number; item->valuedouble = num; item->valueint = (int) num; }return item;}
cJSON* cJSON_CreateString(const char *string) {cJSON *item = cJSON_New_Item(); if(item) item->valuestring = cJSON_strup(string);}

//创建不同类型的array
cJSON* cJSON_CreateIntArray(const int *numbers, int count){
    int i;
    cJSON *n = 0, *p = 0, *a = cJSON_CreateArray();
    for (i = 0; a && i < count; i++) {
        n = cJSON_CreateNumber(numbers[i]);
        if(!i)a->child = n;
        else suffix_object(p, n);
        p = n;
    }
    return a;
}
cJSON* cJSON_CreateFloatArray(const float *numbers, int count){
    int i;
    cJSON *n = 0, *p = 0, *a = cJSON_CreateArray();
    for (i = 0; a && i < count; i++) {
        n = cJSON_CreateNumber(numbers[i]);
        if(!i)a->child = n;
        else suffix_object(p, n);
        p = n;
    }
    return a;
}
cJSON* cJSON_CreateDoubelArray(const double *numbers, int count){
    int i;
    cJSON *n = 0, *p = 0, *a = cJSON_CreateArray();
    for (i = 0; a && i < count; i++) {
        n = cJSON_CreateNumber(numbers[i]);
        if(!i)a->child = n;
        else suffix_object(p, n);
        p = n;
    }
    return a;
}
cJSON* cJSON_CreateStringArray(const char **strings, int count){
    int i;
    cJSON *n = 0, *p = 0, *a = cJSON_CreateArray();
    for (i = 0; a && i < count; i++) {
        n = cJSON_CreateString(strings[i]);
        if(!i)a->child = n;
        else suffix_object(p, n);
        p = n;
    }
    return a;
}

cJSON *cJSON_Duplicate(cJSON *item, int recurse) {
    cJSON *newitem, *cptr, *nptr = 0, *newchild;
    if(!item) return 0;
    newitem = cJSON_New_Item();
    if(!newitem) return 0;
    newitem->type = item->type&(~cJSON_IsReference), newitem->valueint = item->valueint, newitem->valuedouble = item->valuedouble;
    if (item->valuestring) {
        newitem->valuestring = cJSON_strup(item->valuestring);
        if(!newitem->valuestring) {
            cJSON_Delete(newitem);
            return 0;
        }
    }
    if (item->string) {
        newitem->string = cJSON_strup(item->string);
        if(!newitem->string) {
            cJSON_Delete(newitem);
            return 0;
        }
    }
    if (!recurse) {
        return newitem;
    }
    cptr = item->child;
    while(cptr) {
        newchild = cJSON_Duplicate(cptr, 1);
        if (!newchild) {
            cJSON_Delete(newitem);
            return 0;
        }
        if(nptr) {
            nptr->next = newchild; 
            newchild->prev = nptr;
            nptr = newchild;
        } else {
            newitem->child = newchild;
            nptr = newchild;
        }
        cptr = cptr->next;
    }
    return newitem;
}

void cJSON_Minify(char *json) {
    char *into = json;
    while(*json) {
        if (*json == ' ') json++;
        else if (*json == '\t') json++;
        else if (*json == '\r') json++;
        else if (*json == '\n') json++;
        else if (*json == '/' && json[1] == '/') while(*json && *json != '\n') json++;
        else if (*json == '/' && json[1] == '*') 
        {
            while(*json && !(*json == '*' && json[1] == '/')) json++;
            json += 2;
        }
        else if (*json == '\"') {
            *into++ = *json++;
            while(*json && *json != '\"'){
                if(*json == '\\') *into++ = *json++;
                *into++ = *json++;
            }
            *into++ = *json++;
        }
        else *into++ = *json++;
    }
    *into = 0;
}