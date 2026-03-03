# `Yc::ec_optional<T,ErrorCode,no_error>::ec_optional`

```C++
constexpr ec_optional(ErrorCode ec)noexcept; //(1)
```

```C++
constexpr ec_optional(std::nullopt_t, ErrorCode ec)noexcept; //(2)
```

```C++
constexpr ec_optional(const ec_optional& other); //(3)
```

```C++
constexpr ec_optional(ec_optional&& other); //(4)
```

```C++
template<class... Args>
constexpr ec_optional(std::in_place_t, Args&&... args); //(5)
```

```C++
template<class Func>
constexpr ec_optional(legacy_function_tag_t, Func f)noexcept; //(6)
```

构造新的 `ec_optional` 对象。

## 参数

||||
|-:|-|:-|
|`ec`|-|错误码|
|`other`|-|要复制其所含值的另一 `ec_optional` 对象|
|`args...`|-|初始化所含值所用的实参|
|`f`|-|C风格的[_函数对象(FunctionObject)_](https://zh.cppreference.com/w/cpp/named_req/FunctionObject)|

## 效果

 - (1,2) 构造 _出错_ 的 `ec_optional` ，错误码由 `ec` 决定。
 - (3,4) 复制构造和移动构造，分别在 `other` _含值_ 时用 `other` 的所含值复制和移动初始化所含值，否则 _出错_ ，复制 `other` 的错误码，如果 `T` 满足[_可平凡复制 (TriviallyCopyable)_](https://zh.cppreference.com/w/cpp/named_req/TriviallyCopyable)，那么这两个构造函数平凡。
 - (5) 以 [`std::forward<Args>(args)...`](http://zh.cppreference.com/w/cpp/utility/forward) 为参数[直接初始化](https://zh.cppreference.com/w/cpp/language/direct_initialization)（但不是直接列表初始化）所含值。
 - (6) 相当于将 `ec_optional` 对象初始化为 _出错_ 后调用 [`legacy_function_invoke(f)`](legacy_function_invoke.md)。

## 异常
 - (1,2) 不抛出
 - (3,4) 如果 `T` 的复制构造或移动构造不抛出，则不抛出，否则传播复制或移动过程中的异常
 - (5) 如果 [`std::is_nothrow_constructible_v<T, Args...>`](https://zh.cppreference.com/w/cpp/types/is_constructible) 为 `true` 则不抛出，否则传播初始化所含值时的异常
 - (6) 不能抛出
