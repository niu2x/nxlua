#ifndef NX_LOG_H
#define NX_LOG_H

#include <boost/preprocessor.hpp>

#define NX_LOG_LEVEL_TRACE   5
#define NX_LOG_LEVEL_DEBUG   4
#define NX_LOG_LEVEL_WARNING 3
#define NX_LOG_LEVEL_ERROR   2
#define NX_LOG_LEVEL_FATAL   1

#ifndef NX_LOG_LEVEL
    #define NX_LOG_LEVEL NX_LOG_LEVEL_TRACE
#endif

#if BOOST_PP_GREATER_EQUAL(NX_LOG_LEVEL, 5)
    #define NX_LOG_T(...) NX_LOG_WRITE(5, ##__VA_ARGS__)
#else
    #define NX_LOG_T(...)
#endif

#if BOOST_PP_GREATER_EQUAL(NX_LOG_LEVEL, 4)
    #define NX_LOG_D(...) NX_LOG_WRITE(4, ##__VA_ARGS__)
#else
    #define NX_LOG_D(...)
#endif

#if BOOST_PP_GREATER_EQUAL(NX_LOG_LEVEL, 3)
    #define NX_LOG_W(...) NX_LOG_WRITE(3, ##__VA_ARGS__)
#else
    #define NX_LOG_W(...)
#endif

#if BOOST_PP_GREATER_EQUAL(NX_LOG_LEVEL, 2)
    #define NX_LOG_E(...) NX_LOG_WRITE(2, ##__VA_ARGS__)
#else
    #define NX_LOG_E(...)
#endif

#if BOOST_PP_GREATER_EQUAL(NX_LOG_LEVEL, 1)
    #define NX_LOG_F(...) NX_LOG_WRITE(1, ##__VA_ARGS__)
#else
    #define NX_LOG_F(...)
#endif

#define NX_LOG_WRITE(p_level, ...)                                             \
    nx::log::write(p_level, __FILE__, __LINE__, ##__VA_ARGS__)

namespace nx {

struct log {
    static void write(
        int lvl, const char* filename, int line, const char* message, ...);
};

} // namespace nx

#endif