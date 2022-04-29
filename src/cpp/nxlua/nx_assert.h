#ifndef NXLUA_ASSERT_H
#define NXLUA_ASSERT_H

#include "niu2x/log.h"
#include "exception.h"

#if _WIN32
    #define NX_ASSERT(condition, message)                                          \
        if (!(condition)) {                                                        \
            NX_LOG_F(message);                                                     \
            NX_THROW((message));                                                   \
        }

    #define NX_ASSERT_NO_THROW(condition, message)                                 \
        if (!(condition)) {                                                        \
            NX_LOG_F(message);                                                     \
        }
#else
    #define NX_ASSERT(condition, message, ...)                                     \
        if (!(condition)) {                                                        \
            NX_LOG_F(message, ##__VA_ARGS__);                                      \
            NX_THROW((message));                                                   \
        }

    #define NX_ASSERT_NO_THROW(condition, message, ...)                            \
        if (!(condition)) {                                                        \
            NX_LOG_F(message, ##__VA_ARGS__);                                      \
        }
#endif

#endif