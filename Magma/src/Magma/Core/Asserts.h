#pragma once

#include <Magma/Core/Platform.h>

#ifdef MG_ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

// Defined int Magma/Core/Logger.cpp
void reportAssertionFailure(const char* expression, const char* message, const char* file, int line);

#define MG_ASSERT_NO_MSG(expr)                                       \
    {                                                                \
        if (expr)                                                    \
        {                                                            \
        }                                                            \
        else                                                         \
        {                                                            \
            reportAssertionFailure(#expr, "", __FILE__, __LINE__);   \
            debugBreak();                                            \
        }                                                            \
    }

#define MG_ASSERT_MSG(expr, message)                                      \
    {                                                                     \
        if (expr)                                                         \
        {                                                                 \
        }                                                                 \
        else                                                              \
        {                                                                 \
            reportAssertionFailure(#expr, message, __FILE__, __LINE__);   \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG
#define MG_ASSERT_DEBUG(expr)                                        \
    {                                                                \
        if (expr)                                                    \
        {                                                            \
        }                                                            \
        else                                                         \
        {                                                            \
            reportAssertionFailure(#expr, "", __FILE__, __LINE__);   \
            debugBreak();                                            \
        }                                                            \
    }
#else
#define MG_ASSERT_DEBUG(expr)
#endif
#else
#define MG_ASSERT(expr)
#define MG_ASSERT_MSG(expr, message)
#define MG_ASSERT_DEBUG(expr)
#endif
