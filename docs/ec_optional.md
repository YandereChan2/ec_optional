# Yc::ec_optional

在文件 `"ec_optional.h"` 定义

```C++
template<
    class T,
    class ErrorCode,
    ErrorCode no_error = ErrorCode{0}
>class ec_optional;
```

`ec_optional` 是对出参-错误码风格结果的轻量化封装。`ec_optional` 的任何实例在同一个时间点要么 _含值_ ，要么 _出错_ 。如果对象 _出错_ 那么它保有一个确定的错误码，不能是 `no_error` 。如果对象 _含值_ 那么获取其错误码会得到 `no_error` 。

如果一个 `ec_optional` 含值，那么保证该值内嵌于 `ec_optional` 对象。因此，`ec_optional` 对象模拟的是对象而非指针，尽管定义了 `operator*()` 和 `operator->()` 运算符。

当一个 `ec_optional<T, ErrorCode, no_error>` 类型的对象被按语境转换到 `bool` 时，对象含值的情况下转换返回 `true`，出错的情况下返回 `false`。

`ec_optional` 对象在被以 `T` 类型的值或另一含值的 `ec_optional` 初始化/赋值的时候 _含值_ ，在被以错误码或者 `std::nullopt_t` 类型的值或 _出错_ 的 `ec_optional` 对象初始化/赋值，或调用了成员函数 `reset()` 时会 _出错_ 。

`ec_optional` 的值不能是数组，引用或者（可有 cv 限定的） `void` ：如果以这些类型实例化 `ec_optional`，那么程序非良构。另外，如果以（可有 cv 限定的）标签类型 `std::nullopt_t` 或 `std::in_place_t` 实例化 `ec_optional` ，那么程序非良构。

## 模板参数

| | |
|-:|:-|
|`T`|要为之管理值的类型。该类型必须满足 [_可析构 (Destructible)_](https://zh.cppreference.com/w/cpp/named_req/Destructible) 的要求。（特别是不允许数组和引用类型）|
|`ErrorCode`|错误码的类型，必须是整数类型或者枚举类型。|
|`no_error`|表示对象 _含值_ 的特殊错误码值，默认为使用字面量 `0` 初始化的值，以匹配C语言错误处理的实践。|

## 成员类型

|成员类型|定义|
|-:|:-|
|`value_type`|`T`|
|`error_code_type`|`ErrorCode`|

## 成员常量

| | |
|-:|:-|
|`no_error`|对象 _含值_ 时使用的错误码。|

## 数据成员

| | |
|-:|:-|
|_`ec`_|表示对象是否 _含值_ ，以及 _出错_ 时存储错误码于此。（仅用于阐释的成员对象）|

## 成员函数

| | |
|:-|:-|
|（构造函数）|构造 `ec_optional` <br>（公开成员函数）|
|[（析构函数）](destructor.md)|析构 `ec_optional` <br>（公开成员函数）|
|`operator=`|对内容赋值<br>(公开成员函数)|

### 观察器

| | |
|:-|:-|
|[`operator->`<br>`operator*`](operator_star.md)|访问所含值<br>（公开成员函数）|
|`operator bool`<br>`has_value`|检查对象是否 _含值_ <br>（公开成员函数）|
|`value`|返回所含值<br>（公开成员函数）|
|`error_code`|返回错误码<br>（公开成员函数）|

### 修改器

| | |
|:-|:-|
|`swap`|交换内容<br>（公开成员函数）<br>（公开成员函数）|
|`reset`|销毁所含值，并设置对象为 _出错_<br>（公开成员函数）|
|`emplace`|原位构造一个值，如果构造抛出异常那么它 _出错_<br>（公开成员函数）|
|`legacy_function_invoke`|使用C风格初始化其为 _含值_ 或 _出错_|

## 辅助类

| | |
|:-|:-|
|`legacy_function_tag_t`|指示 `ec_optional` 构造函数使用C风格方式初始化<br>（类）|

## 辅助对象

| | |
|:-|:-|
|`legacy_function_tag`|`legacy_function_tag_t` 类型的对象<br>（常量）|
