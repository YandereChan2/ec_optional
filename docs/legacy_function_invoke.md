# `Yc::ec_optional<T,ErrorCode,no_error>::legacy_function_invoke`

```C++
template<class Func>
constexpr void legacy_function_invoke(Func f)noexcept;
```

使用C风格方法设置 `ec_optional` 对象的值，这是相对于 `std::excepted` 的独有功能。

设 `ptr` 为承载所含值存储的 `T*` 类型地址。则它执行 `this->`_`ec`_` = std::move(f)(ptr)` 。因此，可以传入C风格接口，也就是返回错误码，使用指针出参执行初始化的接口的包装器。

`f` 的执行过程中不能抛出异常（否则会因为 `noexcept` 说明符导致调用 `std::terminate` 终止程序）。但是该接口不检查 `noexcept(std::move(f)(ptr))` ，以匹配C语言库往往没有 `noexcept` 说明符的实际情况。

请注意，如果返回 `no_error` ，那么它必须正确构造 `T` 对象，否则，它不能进行构造。特别的，如果 `std::is_trivially_destructible_v != true` ，那么必须确保 `ptr` 所指向的地址没有构造对象或者已经析构。

## 参数

||||
|-:|-|:-|
|`f`|-|用于设置 `ec_optional` 对象的值的函数对象。|

## 返回值

（无）

## 异常

不能抛出。
