#pragma once
#include "union_data.h"
#include <cassert>
#include <utility>
#include <memory>
#include <type_traits>
#include <optional>
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
                noexcept(std::is_nothrow_copy_assignable_v<T>)
            {
                static_assert(std::is_copy_assignable_v<T>);
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
                noexcept(std::is_nothrow_move_assignable_v<T>)
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
    }
    struct legacy_function_tag_t
    { };
    inline constexpr legacy_function_tag_t legacy_function_tag{};
    template<class T, class ErrorCode, ErrorCode no_error = ErrorCode{0} >
    class ec_optional
    {
        static_assert(!std::is_same_v<T, std::nullopt_t>, "T shouldn't be same as std::nullopt_t");
        ErrorCode ec;
        data_t<T> value;
    public:
        template<class Func>
        constexpr ec_optional(legacy_function_tag_t, Func f)noexcept : ec{f(std::addressof(value.data))}
        {}
        constexpr ec_optional(ErrorCode ec)noexcept : ec{ec}
        {
            assert(ec != no_error);
        }
        constexpr ec_optional(std::nullopt_t, ErrorCode ec)noexcept : ec_optional(ec)
        { }
        constexpr ec_optional(const ec_optional& other)noexcept(std::is_nothrow_copy_constructible_v<T>) : ec{other.ec}
        {
            if (ec == no_error)
            {
                std::construct_at(std::addressof(value.data), other.value.data);
            }
        }
        constexpr ec_optional(ec_optional&& other)noexcept(std::is_nothrow_move_constructible_v<T>) : ec{ other.ec }
        {
            if (ec == no_error)
            {
                std::construct_at(std::addressof(value.data), std::move(other.value.data));
            }
        }
        template<class... Args>
        constexpr ec_optional(std::in_place_t, Args&&... args)
            noexcept(std::is_nothrow_constructible_v<T, Args...>) : ec{no_error}
        {
            std::construct_at(std::addressof(value.data), std::forward<Args>(args)...);
        }
        constexpr bool has_value()const noexcept
        {
            return ec == no_error;
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
                    other.emplace(other.ec, std::move(value.data));
                    std::destroy_at(std::addressof(value.data));
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
                    swap(value.data, other.value.data);
                }
                std::swap(ec, other.ec);
            }
        }
        constexpr void reset(ErrorCode ec)noexcept
        {
            assert(ec != no_error);
            if (this->ec == no_error)
            {
                std::destroy_at(std::addressof(value.data));
            }
            this->ec = ec;
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
            }guard{std::addressof(this->ec), ec};
            std::construct_at(std::addressof(value.data), std::forward<Args>(args)...);
            this->ec = no_error;
            guard.tmp = nullptr;
            return value.data;
        }
        template<class Func>
        constexpr void legacy_function_invoke(Func f)noexcept // ½ûÖ¹Å×³öÒì³£
        {
            if (has_value())
            {
                std::destroy_at(std::addressof(value.data));
            }
            ec = f(std::addressof(value.data));
        }
        ~ec_optional()
        {
            if (this->ec == no_error)
            {
                std::destroy_at(std::addressof(value.data));
            }
        }
        constexpr ErrorCode error_code()const noexcept
        {
            return ec;
        }
        constexpr T& value()&
        {
            if (ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return value.data;
        }
        constexpr T&& value()&&
        {
            if (ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return std::move(value.data);
        }
        constexpr const T& value()const &
        {
            if (ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return value.data;
        }
        constexpr const T&& value()const &&
        {
            if (ec != no_error)
            {
                throw std::bad_optional_access{};
            }
            return std::move(value.data);
        }
        constexpr T* operator->()noexcept
        {
            return std::addressof(value.data);
        }
        constexpr const T* operator->()const noexcept
        {
            return std::addressof(value.data);
        }
        constexpr T& operator*()& noexcept
        {
            return value.data;
        }
        constexpr T&& operator*() && noexcept
        {
            return std::move(value.data);
        }
        constexpr const T& operator*()const & noexcept
        {
            return value.data;
        }
        constexpr const T&& operator*()const && noexcept
        {
            return std::move(value.data);
        }
    };
}