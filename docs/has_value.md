# `Yc::ec_optional<T,ErrorCode,no_error>::operator bool`,`Yc::ec_optional<T,ErrorCode,no_error>::has_value`

```C++
constexpr explicit operator bool()const noexcept;
```

```C++
constexpr bool has_value()const noexcept;
```

检查 `*this` 是否含值。

## 参数

（无）

## 返回值

如果 _含值_ ，则返回 `true` ，如果 _出错_ ，则返回 `false` 。
