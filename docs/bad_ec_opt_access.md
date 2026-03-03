# `Yc::bad_ec_opt_access`

在文件 `"ec_optional.h"` 定义

```C++
class bad_ec_opt_access;
```

继承 [`std::exception`](https://zh.cppreference.com/w/cpp/error/exception) 的异常类型，在通过 [`value()`](value.md) 访问 _出错_ 的 [`ec_optional`](ec_optional.md) 对象时抛出，内部携带现场的错误码。

## 成员函数

| | |
|:-|:-|
|（构造函数）|构造新的 `bad_ec_opt_access` 对象<br>（公开成员函数）|
|`operator=`|替换 `bad_ec_opt_access` 对象<br>（公开成员函数）|
|`what`|返回解释字符串<br>（公开成员函数）|
|`error_code`|从内部状态提取错误码<br>（公开成员函数）|

## `Yc::bad_ec_opt_access::bad_ec_opt_access`

```C++
template<class Enum> 
bad_ec_opt_access(Enum e)noexcept; //(1)
```
```C++
bad_ec_opt_access(const bad_ec_opt_access& other)noexcept; //(2)
```

 - (1) 构造携带错误码 `e` 的异常对象，`Enum` 必须是整数或者枚举。
 - (2) 复制 `other` 的内部状态，如果 `*this` 与 `other` 均拥有动态类型 `Yc::bad_ec_opt_access` ，那么 [`std::strcmp(what(), other.what()) == 0`](https://zh.cppreference.com/w/cpp/string/byte/strcmp)，并且 `error_code<Enum>() == other.error_code<Enum>()`。

### 参数

||||
|-:|-|:-|
|`e`|-|存入的错误码|
|`other`|-|要复制的另一异常对象|

## `Yc::bad_ec_opt_access::operator=`

```C++
bad_ec_opt_access& operator=(const bad_ec_opt_access& other)noexcept;
```

复制内部状态，如果 `*this` 与 `other` 均拥有动态类型 `Yc::bad_ec_opt_access` ，那么 [`std::strcmp(what(), other.what()) == 0`](https://zh.cppreference.com/w/cpp/string/byte/strcmp)，并且 `error_code<Enum>() == other.error_code<Enum>()`。

### 参数

||||
|-:|-|:-|
|`other`|-|要复制的另一异常对象|

### 返回值

`*this`

## `Yc::bad_ec_opt_access::what`

```C++
virtual const char* what()const noexcept;
```

返回解释性字符串。

### 返回值

返回解释性空终止字符串，保证字符串生存期至少和对象本身相当。

## `Yc::bad_ec_opt_access::error_code`

```C++
template<class ErrorCode>
ErrorCode error_code()const noexcept;
```

从内部状态提取错误码，保证提取的类型和构造时的类型一致是程序员的责任。

### 返回值

内部存储的错误码。

## 继承自 [`std::exception`](https://zh.cppreference.com/w/cpp/error/exception)

### 成员函数
| | |
|:-|:-|
|[（析构函数）](https://zh.cppreference.com/w/cpp/error/exception/~exception)【虚】|销毁该异常对象<br>（[`std::exception`](https://zh.cppreference.com/w/cpp/error/exception) 的虚公开成员函数）|