# `Yc::swap(Yc::ec_optional)`

```C++
template<class T, class ErrorCode, ErrorCode no_err>
constexpr void swap(ec_optional<T, ErrorCode, no_err>& l, ec_optional<T, ErrorCode, no_err>&r)
    noexcept(std::is_nothrow_move_constructible_v<T>&&std::is_nothrow_swappable_v<T>);
```

执行 [`l.swap(r)`](swap.md) 。

此函数适用于[实参依赖查找(ADL)](https://zh.cppreference.com/w/cpp/language/adl)。

## 参数

||||
|-:|-|:-|
|`l` , `r`|-|要交换内容的 `ec_optional` |

## 返回值

（无）

## 异常

参见 [`Yc::ec_optional::swap`](swap.md)
