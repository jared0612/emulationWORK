json格式作为序列化和反序列化的格式；
json库支持的操作需要：
- 支持创建、解析json消息；
- 支持增删改；
- 支持查询数据；


**解析**：字符串转换成json格式消息；
一些常见的json库：
yyjson、simdjson、sonicjson、rapidjson、
现在json库的使用单独的头文件和单独的实现文件，依靠零依赖的特性。

yyjson：解析性能高，但是使用的链表结构，导致查询速度变慢

simdjson：解析速度快，但是不支持修改解析后的json结构；

sonicjson：字节跳动自研的为c++服务的json库，




大冤种rapidjson，都拿来和它比较；最近的更新是2016年；

字符串