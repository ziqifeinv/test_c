# test_c
用于测试C/C++基本功能

1.结构体中的结构体指针只计算指针大小，而不是计算结构体大小，所以初始化结构体时，其指针必须手动申请内存。

2.预编译使用枚举变量作为条件时，全部按0处理，即枚举变量不参与预编译流程。

3，数字转字符，需要加上48('0'的ASCII编码)