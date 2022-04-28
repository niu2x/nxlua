#ifndef NX_UTILS_H
#define NX_UTILS_H

#include <cstdint>
#include <cstddef>

namespace nx {

/**
 * @brief      string to int on compile time
 *
 * @param[in]  str    The string
 * @param[in]  value  default value
 *
 * @return     if str is nullptr, return default value.
 *             otherwise convert str to int.
 */
constexpr inline int stoi(const char* str, int value = 0);

inline constexpr size_t operator"" _k(const char* n)
{
    return nx::stoi(n) << 10;
}
inline constexpr size_t operator"" _m(const char* n)
{
    return nx::stoi(n) << 20;
}
inline constexpr size_t operator"" _g(const char* n)
{
    return nx::stoi(n) << 30;
}

constexpr void unused(...) { }

namespace details {
constexpr inline bool is_digit(char c) { return c <= '9' && c >= '0'; }
} // namespace details

constexpr inline int stoi(const char* str, int value)
{
    return *str ? details::is_digit(*str)
            ? stoi(str + 1, (*str - '0') + value * 10)
            : throw "compile-time-error: not a digit"
                : value;
}

} // namespace nx

#define NX_OFFSET_OF(mt, field) (ptrdiff_t)(&(((mt*)nullptr)->field))
#define NX_TYPE_OF(name)        std::decay_t<decltype(name)>
// #define NX_ALLOC_ARRAY(type, num) (type*) malloc(sizeof(type) * (num))
// #define NX_ALLOC_FREE(type, num) (type*) malloc(sizeof(type) * (num))

#endif