# `Yc::ec_optional<T,ErrorCode,no_error>::emplace`

```C++
template<class... Args>
constexpr T& emplace(ErrorCode ec, Args&&... args)noexcept(std::is_nothrow_constructible_v<T, Args...>);
```

以 [`std::forward<Args>(args)...`](http://zh.cppreference.com/w/cpp/utility/forward) 为参数[直接初始化](https://zh.cppreference.com/w/cpp/language/direct_initialization)（但不是直接列表初始化）所含值。若 `*this` 已在此调用前 _含值_ ，则调用其析构函数销毁所含值。如果构造抛出异常，那么设置 `*this` 为 _出错_ ，错误码为 `ec` 。

如果 [`std::is_nothrow_constructible_v<T, Args...>`](https://zh.cppreference.com/w/cpp/types/is_constructible) 为 `false` ，那么在 `ec == no_error` 时[行为未定义](https://zh.cppreference.com/w/cpp/language/ub)，也就是说，如果构造不抛异常，可以单纯使用 `emplace({}, args...)` 来调用此函数。

## 参数

||||
|-:|-|:-|
|`ec`|-|构造失败时配置的错误码|
|`args`|-|构造参数|

## 返回值

到所含值的引用。

## 异常

被选中的 `T` 构造函数所抛出的任何异常。若抛出异常，则 `*this` 在此调用后 _出错_ 并设置错误码（若先前 _含值_ ，则销毁所含值）。
