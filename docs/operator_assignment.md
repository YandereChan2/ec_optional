# `Yc::ec_optional<T,ErrorCode,no_error>::operator=`

```C++
constexpr operator=(const ec_optional& other)noexcept(/* 见下文 */) //(1)
```

```C++
constexpr operator=(ec_optional&& other)noexcept(/* 见下文 */) //(2)
```

以 `other` 的内容替换 `*this` 的内容。

|效果|`*this` _含值_|`*this` _出错_|
|-|-|-|
|`other` _含值_|调用复制赋值或移动赋值运算符进行赋值|调用复制构造函数或者移动构造函数，如果成功则 `*this` _含值_ ，否则保持之前的 _出错_ 状态|
|`other` _出错_|调用析构函数销毁值， `*this` 获得和 `other` 一样的错误码|更新 `*this` 的错误码为 `other` 的错误码|

如果 `T` 满足[_可平凡复制 (TriviallyCopyable)_](https://zh.cppreference.com/w/cpp/named_req/TriviallyCopyable)，那么这两个运算符平凡。

## 参数

||||
|-:|-|:-|
|`other`|-|要赋值其所含值的 `ec_optional` 对象|

## 返回值

`*this` 。

## 异常

传播赋值或移动过程中的异常。

 - (1)在 `std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_assignable_v<T>` 为 `true` 时 `noexcept`
 - (2)在 `std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>` 为 `true` 时 `noexcept`
