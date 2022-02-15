#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <float.h>
#include <map>

// 命名空间宏定义
#define _NAMESPACE_BEGIN                                                                                               \
    namespace Mearth                                                                                                   \
    {
#define _NAMESPACE_END }

_NAMESPACE_BEGIN

#define DISALLOW_CONSTRUCT_COPY_ASSIGN(ClassName)                                                                      \
    ClassName(const ClassName&) = delete;                                                                              \
    ClassName& operator=(const ClassName&) = delete;                                                                   \
    ClassName() = delete;                                                                                              \
    ~ClassName() = delete;
//　多线程存在争抢资源情况,最大输出为1024
#define MAX_LOG_BUF 1024

int Information(const char* format, ...);
int Process(size_t cur, size_t num);
int Warning(const char* format, ...);
int Error(const char* format, ...);

// 命令台输出
#define ENABLE_LOG

#ifdef ENABLE_LOG
#    define MT_INFO(format, ...) Information("%s(%d), " format, __FILE__, __LINE__, ##__VA_ARGS__);
#    define MT_PROCESS(cur, num) Process(cur, num);
#    define MT_WARN(format, ...) Warning("%s(%d), " format, __FILE__, __LINE__, ##__VA_ARGS__);
#    define MT_ERROR(format, ...) Error("%s(%d), " format, __FILE__, __LINE__, ##__VA_ARGS__);
#else
#    define MT_INFO(format, ...)
#    define MT_PROCESS(cur, num)
#    define MT_WARN(format, ...)
#    define MT_ERROR(format, ...)
#endif

#define VALID_PTR_VOID(ptr)                                                                                            \
    do {                                                                                                               \
        if (ptr == NULL) {                                                                                             \
            MT_INFO("this has invalid ptr\n");                                                                         \
            return;                                                                                                    \
        }                                                                                                              \
    } while (0);

#define VALID_PTR_BOOL(ptr)                                                                                            \
    do {                                                                                                               \
        if (ptr == NULL) {                                                                                             \
            MT_INFO("this has invalid ptr\n");                                                                         \
            return false;                                                                                              \
        }                                                                                                              \
    } while (0);

bool doubleEqual(double a, double b);

_NAMESPACE_END
