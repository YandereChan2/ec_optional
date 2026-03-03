# `Yc::ec_optional<T,ErrorCode,no_error>::value`

```C++
constexpr T& value()&; //(1)
```

```C++
constexpr const T& value()const &; //(2)
```

```C++
constexpr T&& value()&&; //(3)
```

```C++
constexpr const T&& value()const &&; //(4)
```

若 `*this` _含值_，则返回到所含值的引用。

否则，抛出 [`bad_ec_opt_access`](bad_ec_opt_access.md) 异常，该异常对象携带实际的错误码。

## 参数

（无）

## 返回值

到所含值的引用。

## 异常

若 *this _出错_ 则抛出携带[`error_code()`](error_code.md) 的 [`bad_ec_opt_access`](bad_ec_opt_access.md)。

## 注解

解引用运算符 [`operator*()`](operator_star.md) 不检查此 `ec_optional` 是否 _含值_ ，它可能比 `value()` 更有效率。
