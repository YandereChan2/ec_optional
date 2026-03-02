# `Yc::ec_optional<T,ErrorCode,no_error>::~ec_optional`

```C++
~ec_optional()
```

[析构函数](https://zh.cppreference.com/w/cpp/language/destructor)。 如果对象 _含值_ ，销毁保有值。

否则，不做任何事。

如果 `std::is_trivially_destructible_v == true` ，那么析构函数平凡。
