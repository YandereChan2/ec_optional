# `Yc::ec_optional<T,ErrorCode,no_error>::error_code`

```C++
constexpr ErrorCode error_code()const noexcept;
```

获取储存的错误码。

## 参数

（无）

## 返回值

如果对象 _含值_ ，那么返回 `no_error` ，如果对象 _出错_ ，那么返回持有的错误码。
