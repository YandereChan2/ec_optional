# `Yc::ec_optional<T,ErrorCode,no_error>::~ec_optional`

```C++
~ec_optional();
```

[析构函数](https://zh.cppreference.com/w/cpp/language/destructor)。 如果对象 _含值_ ，销毁保有值。

否则，不做任何事。

如果 [`std::is_trivially_destructible_v<T>`](https://zh.cppreference.com/w/cpp/types/is_destructible) 为 `true` ，那么析构函数[平凡](https://zh.cppreference.com/w/cpp/language/destructor#Trivial_destructor)。
