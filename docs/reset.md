# `Yc::ec_optional<T,ErrorCode,no_error>::reset`

```C++
constexpr void reset(ErrorCode ec)noexcept;
```

配置 `*this` 为 _出错_ 并设置错误码为 `ec` 。如果 `*this` _含值_ ，那么销毁之。如果 `ec == no_error`，那么[行为未定义](https://zh.cppreference.com/w/cpp/language/ub)。

## 参数

||||
|-:|-|:-|
|`ec`|-|想要配置的错误码|

## 返回值

（无）
