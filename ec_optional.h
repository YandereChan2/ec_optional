#pragma once
#include <cassert>
#include <utility>
#include <memory>
#include <type_traits>
#include <optional>
#include <bit>
#include <array>
namespace Yc
{
    namespace details
    {
        template<class T, class ErrorCode, ErrorCode no_error = ErrorCode{ 0 } >
        struct ec_optional_trivially_copyable
        {
            ErrorCode ec;
            union U
            {
                T t;
            }u;
            constexpr ec_optional_trivially_copyable(ErrorCode ec)noexcept : ec{ec}
            { }
            constexpr ec_optional_trivially_copyable(const ec_optional_trivially_copyable&) = default;
            constexpr ec_optional_trivially_copyable& operator=(const ec_optional_trivially_copyable&) = default;
            ~ec_optional_trivially_copyable() = default;
        };
        template<class T, class ErrorCode, ErrorCode no_error = ErrorCode{ 0 } >
        struct ec_optional_trivially_destructable
        {
            ErrorCode ec;
            union U
            {
                T t;
                ~U() = default;
            }u;
            constexpr ec_optional_trivially_destructable(ErrorCode ec)noexcept : ec{ec}
            { }
            constexpr ec_optional_trivially_destructable(const ec_optional_trivially_destructable& other)
                noexcept(std::is_nothrow_copy_constructible_v<T>): ec{other.ec }
            {
                static_assert(std::is_copy_constructible_v<T>);
                if (other.ec == no_error)
                {
                    std::construct_at(std::addressof(u.t), other.u.t);
                }
            }
            constexpr ec_optional_trivially_destructable(ec_optional_trivially_destructable&& other)
                noexcept(std::is_nothrow_move_constructible_v<T>) : ec{ other.ec }
            {
                static_assert(std::is_move_constructible_v<T>);
                if (other.ec == no_error)
                {
                    std::construct_at(std::addressof(u.t), std::move(other.u.t));
                }
            }
            constexpr ec_optional_trivially_destructable& operator=(const ec_optional_trivially_destructable& other)
                noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_assignable_v<T>)
            {
                static_assert(std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>);
                if (this == std::addressof(other))
                {
                    return *this;
                }
                if (ec == other.ec)
                {
                    if (ec == no_error)
                    {
                        u.t = other.u.t;
                    }
                }
                else
                {
                    if (ec == no_error)
                    {
                        std::destroy_at(std::addressof(u.t));
                    }
                    else
                    {
                        if (other.ec == no_error)
                        {
                            std::construct_at(std::addressof(u.t), other.u.t);
                        }
                    }
                }
                ec = other.ec;
                return *this;
            }
            constexpr ec_optional_trivially_destructable& operator=(ec_optional_trivially_destructable&& other)
                noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)
            {
                static_assert(std::is_move_assignable_v<T>);
                if (this == std::addressof(other))
                {
                    return *this;
                }
                if (ec == other.ec)
                {
                    if (ec == no_error)
                    {
                        u.t = std::move(other.u.t);
                    }
                }
                else
                {
                    if (ec == no_error)
                    {
                        std::destroy_at(std::addressof(u.t));
                    }
                    else
                    {
                        if (other.ec == no_error)
                        {
                            std::construct_at(std::addressof(u.t), std::move(other.u.t));
                        }
                    }
                }
                ec = other.ec;
                return *this;
            }
            ~ec_optional_trivially_destructable() = default;
        };
        template<class T, class ErrorCode, ErrorCode no_error = ErrorCode{ 0 } >
        struct ec_optional_normal
        {
            ErrorCode ec;
            union U
            {
                T t;
                ~U()noexcept
                { }
            }u;
            constexpr ec_optional_normal(ErrorCode ec)noexcept : ec{ec}
            { }
            constexpr ec_optional_normal(const ec_optional_normal& other)
                noexcept(std::is_nothrow_copy_constructible_v<T>) : ec{ other.ec }
            {
                static_assert(std::is_copy_constructible_v<T>);
                if (other.ec == no_error)
                {
                    std::construct_at(std::addressof(u.t), other.u.t);
                }
            }
            constexpr ec_optional_normal(ec_optional_normal&& other)
                noexcept(std::is_nothrow_move_constructible_v<T>) : ec{ other.ec }
            {
                static_assert(std::is_move_constructible_v<T>);
                if (other.ec == no_error)
                {
                    std::construct_at(std::addressof(u.t), std::move(other.u.t));
                }
            }
            constexpr ec_optional_normal& operator=(const ec_optional_normal& other)
                noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_assignable_v<T>)
            {
                static_assert(std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>);
                if (this == std::addressof(other))
                {
                    return *this;
                }
                if (ec == other.ec)
                {
                    if (ec == no_error)
                    {
                        u.t = other.u.t;
                    }
                }
                else
                {
                    if (ec == no_error)
                    {
                        std::destroy_at(std::addressof(u.t));
                    }
                    else
                    {
                        if (other.ec == no_error)
                        {
                            std::construct_at(std::addressof(u.t), other.u.t);
                        }
                    }
                }
                ec = other.ec;
                return *this;
            }
            constexpr ec_optional_normal& operator=(ec_optional_normal&& other)
                noexcept(std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_move_assignable_v<T>)
            {
                static_assert(std::is_move_constructible_v<T> && std::is_move_assignable_v<T>);
                if (this == std::addressof(other))
                {
                    return *this;
                }
                if (ec == other.ec)
                {
                    if (ec == no_error)
                    {
                        u.t = std::move(other.u.t);
                    }
                }
                else
                {
                    if (ec == no_error)
                    {
                        std::destroy_at(std::addressof(u.t));
                    }
                    else
                    {
                        if (other.ec == no_error)
                        {
                            std::construct_at(std::addressof(u.t), std::move(other.u.t));
                        }
                    }
                }
                ec = other.ec;
                return *this;
            }
            constexpr ~ec_optional_normal()
            {
                if (ec == no_error)
                {
                    std::destroy_at(std::addressof(u.t));
                }
            }
        };
    }
    struct legacy_function_tag_t
    { };
    inline constexpr legacy_function_tag_t legacy_function_tag{};
    template<class T, class ErrorCode, ErrorCode no_error = ErrorCode{0} >
    class ec_optional
    {
        static_assert(!std::is_same_v<T, std::nullopt_t>, "T shouldn't be same as std::nullopt_t");
        static_assert(std::is_integral_v<ErrorCode> || std::is_enum_v<ErrorCode>);
        std::conditional_t<std::is_trivially_copyable_v<T>,
            details::ec_optional_trivially_copyable<T, ErrorCode, no_error>,
            std::conditional_t<std::is_trivially_destructible_v<T>,
            details::ec_optional_trivially_destructable<T, ErrorCode, no_error>,
            details::ec_optional_normal<T, ErrorCode, no_error>>> opt;
        static constexpr ErrorCode default_error()noexcept
        {
            std::array<unsigned char, sizeof(ErrorCode)> a{};
            a = std::bit_cast<std::array<unsigned char, sizeof(ErrorCode)>>(no_error);
            for (auto& uc : a)
            {
                ++uc;
            }
            return std::bit_cast<ErrorCode>(a);
        }
        static inline constexpr ErrorCode default_err = default_error();
    public:
        template<class Func>
        constexpr ec_optional(legacy_function_tag_t, Func f)noexcept : opt{no_error}
        {
            opt.ec = f(std::addressof(value.data));
        }
        constexpr ec_optional(ErrorCode ec)noexcept : opt{ec}
        {
            assert(ec != no_error);
        }
        constexpr ec_optional(std::nullopt_t, ErrorCode ec)noexcept : ec_optional(ec)
        { }
        ec_optional(const ec_optional&) = default;
        ec_optional(ec_optional&&) = default;
        template<class... Args>
        constexpr ec_optional(std::in_place_t, Args&&... args)
            noexcept(std::is_nothrow_constructible_v<T, Args...>) : opt{no_error}
        {
            opt.ec = default_err;
            std::construct_at(std::addressof(opt.u.t), std::forward<Args>(args)...);
            opt.ec = no_error;
        }
        constexpr bool has_value()const noexcept
        {
            return opt.ec == no_error;
        }
        constexpr explicit operator bool()const noexcept
        {
            return has_value();
        }
        void swap(ec_optional& other)noexcept(std::is_nothrow_move_constructible_v<T>&&
            std::is_nothrow_swappable_v<T>)
        {
            if (has_value() != other.has_value())
            {
                if (has_value())
                {
                    ErrorCode ec = other.ec;
                    other.emplace(other.ec, std::move(opt.u.t));
                    std::destroy_at(std::addressof(opt.u.t));
                    this->ec = ec;
                }
                else
                {
                    other.swap(*this);
                }
            }
            else
            {
                if (has_value())
                {
                    using std::swap;
                    swap(opt.u.t, other.opt.u.t);
                }
                std::swap(opt.ec, other.opt.ec);
            }
        }
        constexpr void reset(ErrorCode ec)noexcept
        {
            assert(ec != no_error);
            if (this->opt.ec == no_error)
            {
                std::destroy_at(std::addressof(opt.u.t));
            }
            this->opt.ec = ec;
        }
        template<class... Args>
        constexpr T& emplace(ErrorCode ec, Args&&... args)
            noexcept(std::is_nothrow_constructible_v<T, Args...>)
        {
            if constexpr (!std::is_nothrow_constructible_v<T, Args...>)
            {
                assert(ec != no_error);
            }
            struct _guard
            {
                ErrorCode* tmp{};
                ErrorCode& ec;
                ~_guard()
                {
                    if (tmp)
                    {
                        *tmp = ec;
                    }
                }
            }guard{std::addressof(opt.ec), ec};
            std::construct_at(std::addressof(opt.u.t), std::forward<Args>(args)...);
            opt.ec = no_error;
            guard.tmp = nullptr;
            return opt.u.t;
        }
        template<class Func>
        constexpr void legacy_function_invoke(Func f)noexcept // ½ûÖ¹Å×³öÒì³£
        {
            if (has_value())
            {
                std::destroy_at(std::addressof(opt.u.t));
            }
            opt.ec = f(std::addressof(opt.u.t));
        }
        ~ec_optional() = default;
        constexpr ErrorCode error_code()const noexcept
        {
            return opt.ec;
        }
        constexpr T& value()&
        {
            if (opt.ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return opt.u.t;
        }
        constexpr T&& value()&&
        {
            if (opt.ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return std::move(opt.u.t);
        }
        constexpr const T& value()const &
        {
            if (opt.ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return opt.u.t;
        }
        constexpr const T&& value()const &&
        {
            if (opt.ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return std::move(opt.u.t);
        }
        constexpr T* operator->()noexcept
        {
            return std::addressof(opt.u.t);
        }
        constexpr const T* operator->()const noexcept
        {
            return std::addressof(opt.u.t);
        }
        constexpr T& operator*()& noexcept
        {
            return opt.u.t;
        }
        constexpr T&& operator*() && noexcept
        {
            return std::move(opt.u.t);
        }
        constexpr const T& operator*()const & noexcept
        {
            return opt.u.t;
        }
        constexpr const T&& operator*()const && noexcept
        {
            return std::move(opt.u.t);
        }
    };
}
