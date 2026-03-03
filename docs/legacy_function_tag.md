# `Yc::legacy_function_tag_t`,`Yc::legacy_function_tag_t`

在文件 `"ec_optional.h"` 定义

```C++
struct legacy_function_tag_t
{ explicit legacy_function_tag_t() = default; };
```

```C++
inline constexpr legacy_function_tag_t legacy_function_tag{};
```

类型 `legacy_function_tag_t` 用于 `ec_optional` 构造函数选择C风格初始化的重载。`legacy_function_tag` 是它的一个值。
