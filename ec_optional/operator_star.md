# `Yc::ec_optional<T,ErrorCode,no_error>::operator->`,`Yc::ec_optional<T,ErrorCode,no_error>::operator*`

```C++
constexpr T* operator->()noexcept; //(1)
```

```C++
constexpr const T* operator->()const noexcept; //(2)
```

```C++
constexpr T& operator*()& noexcept; //(3)
```

```C++
constexpr const T& operator*()const & noexcept; //(4)
```

```C++
constexpr T&& operator*() && noexcept; //(5)
```

```C++
constexpr const T&& operator*()const && noexcept; //(6)
```

访问所含值

 - (1,2) 返回所含值的地址。
 - (3-6) 返回所含值的引用。

如果对象 _出错_ ，那么行为未定义。

## 返回值

 - (1,2) 所含值的地址
 - (3,4) 所含值的左值引用
 - (5,6) 所含值的右值引用

## 注意

这些运算符重载不会检查 `*this` 是否 _含值_ ，可以通过 `has_value` 或 `operator bool` 自行检查，或者通过 `error_code` 查看错误码确定 _出错_ 状态。另外，也可以使用 `value` 来安全的访问所含值，它在实际 _出错_ 时会抛出异常。