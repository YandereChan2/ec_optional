# `Yc::ec_optional<T,ErrorCode,no_error>::swap`

```C++
constexpr void swap(ec_optional& other)noexcept(std::is_nothrow_move_constructible_v<T>&&std::is_nothrow_swappable_v<T>);
```

与 `other` 交换内容。

 - 若 `*this` 和 `other` 均 _出错_ ，那么交换错误码。
 - 若 `*this` 与 `other` 仅有一个 _含值_（称此对象为 `in`，另一者为 `un`），则从 [`std::move(*in)`](https://zh.cppreference.com/w/cpp/utility/move) [直接初始化](https://zh.cppreference.com/w/cpp/language/direct_initialization) `un` 所含值，随后如同通过 `in->T::~T()` 析构 `in` 所含值。此调用后，`in` _出错_，错误码为 `un` 原先的错误码， `un` _含值_ 。
 - 若 `*this` 与 `other` 均 _含值_ ，则如同通过 [`using std::swap;`](https://zh.cppreference.com/w/cpp/utility/swap) `swap(**this, *other);` 交换所含值。

除非 `T` [_可交换 (Swappable)_](https://zh.cppreference.com/w/cpp/named_req/Swappable) 且 [`std::is_move_constructible_v<T>`](https://zh.cppreference.com/w/cpp/types/is_move_constructible) 是 `true` ，否则程序非良构。

## 参数

||||
|-:|-|:-|
|`other`|-|要与之交换内容的 `ec_optional` 对象|

## 返回值

（无）

## 异常

`noexcept` 说明：  
    `noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_swappable_v<T>)`

在抛异常的情况下，`*this` 和 `other` 所含值的状态由 `T` 的 `swap` 或 `T` 的移动构造函数的[异常安全](https://zh.cppreference.com/w/cpp/language/exceptions)保证决定，取决于调用的是哪个。对于 `*this` 和 `other` ，若对象 _含值_ ，则令它继续 _含值_ ，反之亦然，且 _出错_ 的对象错误码不变。
