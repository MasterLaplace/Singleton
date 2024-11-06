/**************************************************************************
 * Singleton v0.0.0
 *
 * Singleton is a C/CPP library for creating portable singleton objects.
 * It is designed to be easy to use and easy to integrate into your project
 * using a single header file (stb style).
 *
 * This file is part of the Singleton project that is under Anti-NN License.
 * https://github.com/MasterLaplace/Anti-NN_LICENSE
 * Copyright © 2024 by @MasterLaplace, All rights reserved.
 *
 * Singleton is a free software: you can redistribute it and/or modify
 * it under the terms of the Anti-NN License as published by MasterLaplace.
 * See the Anti-NN License for more details.
 *
 * @file config.h
 * @brief Compile-Time Configuration Parameters for Singleton.
 *
 * @author @MasterLaplace
 * @version 0.0.0
 * @date 2024-11-06
 **************************************************************************/

// clang-format off
#ifndef CONFIG_H_
    #define CONFIG_H_

#ifdef __cplusplus
    #include <utility>
    #include <type_traits>

    #include <cstddef>
    #include <cstdint>
#else
    #include <stddef.h>
    #include <stdint.h>
#endif

#ifndef DISTRIBUTION_H_
    #define DISTRIBUTION_H_

////////////////////////////////////////////////////////////
// Identify the Compiler
////////////////////////////////////////////////////////////
#if defined(_MSC_VER) || defined(_MSVC_LANG)
    #define SINGLETON_COMPILER_MSVC
    #define SINGLETON_COMPILER_STRING "MSVC"
#elif defined(__GNUC__) || defined(__GNUG__)
    #define SINGLETON_COMPILER_GCC
    #define SINGLETON_COMPILER_STRING "GCC"
#elif defined(__clang__) || defined(__llvm__)
    #define SINGLETON_COMPILER_CLANG
    #define SINGLETON_COMPILER_STRING "Clang"
#elif defined(__MINGW32__) || defined(__MINGW64__)
    #define SINGLETON_COMPILER_MINGW
    #define SINGLETON_COMPILER_STRING "MinGW"
#elif defined(__CYGWIN__)
    #define SINGLETON_COMPILER_CYGWIN
    #define SINGLETON_COMPILER_STRING "Cygwin"
#else
    #error [Config@Distribution]: This compiler is not supported by SINGLETON library.
#endif


////////////////////////////////////////////////////////////
// Identify the Operating System
////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(__WIN32__) || defined(SINGLETON_COMPILER_MINGW) || defined(SINGLETON_COMPILER_CYGWIN)

    #define SINGLETON_SYSTEM_WINDOWS
    #define SINGLETON_SYSTEM_STRING "Windows"

// Android is based on the Linux SINGLETON, so it has to appear before Linux
#elif defined(__ANDROID__)

    #define SINGLETON_SYSTEM_ANDROID
    #define SINGLETON_SYSTEM_STRING "Android"

#elif defined(linux) || defined(__linux)

    #define SINGLETON_SYSTEM_LINUX
    #define SINGLETON_SYSTEM_STRING "Linux"

#elif defined(__unix) || defined(__unix__)

    #define SINGLETON_SYSTEM_UNIX
    #define SINGLETON_SYSTEM_STRING "Unix"

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    #define SINGLETON_SYSTEM_MACOS
    #define SINGLETON_SYSTEM_STRING "MacOS"

#elif defined(__FreeBSD__) || defined(__FreeBSD_SINGLETON__)

    #define SINGLETON_SYSTEM_FREEBSD
    #define SINGLETON_SYSTEM_STRING "FreeBSD"

#elif defined(LAPLACE_KERNEL_PANIC)

    #define SINGLETON_SYSTEM_KERNEL
    #define SINGLETON_SYSTEM_STRING "Laplace Kernel"

#else
    #error [Config@Distribution]: This operating system is not supported by SINGLETON library.
#endif

#ifdef __cplusplus
    #define SINGLETON_EXTERN_C extern "C"

    #if __cplusplus >= 202203L
        #define SINGLETON_CPP23(_) _
        #define SINGLETON_CPP20(_) _
        #define SINGLETON_CPP17(_) _
        #define SINGLETON_CPP14(_) _
        #define SINGLETON_CPP11(_) _
        #define SINGLETON_CPP99(_) _
    #elif __cplusplus >= 202002L
        #define SINGLETON_CPP23(_)
        #define SINGLETON_CPP20(_) _
        #define SINGLETON_CPP17(_) _
        #define SINGLETON_CPP14(_) _
        #define SINGLETON_CPP11(_) _
        #define SINGLETON_CPP99(_) _
    #elif __cplusplus >= 201703L
        #define SINGLETON_CPP23(_)
        #define SINGLETON_CPP20(_)
        #define SINGLETON_CPP17(_) _
        #define SINGLETON_CPP14(_) _
        #define SINGLETON_CPP11(_) _
        #define SINGLETON_CPP99(_) _
    #elif __cplusplus >= 201402L
        #define SINGLETON_CPP23(_)
        #define SINGLETON_CPP20(_)
        #define SINGLETON_CPP17(_)
        #define SINGLETON_CPP14(_) _
        #define SINGLETON_CPP11(_) _
        #define SINGLETON_CPP99(_) _
    #elif __cplusplus >= 201103L
        #define SINGLETON_CPP23(_)
        #define SINGLETON_CPP20(_)
        #define SINGLETON_CPP17(_)
        #define SINGLETON_CPP14(_)
        #define SINGLETON_CPP11(_) _
        #define SINGLETON_CPP99(_) _
    #elif __cplusplus >= 199711L
        #define SINGLETON_CPP23(_)
        #define SINGLETON_CPP20(_)
        #define SINGLETON_CPP17(_)
        #define SINGLETON_CPP14(_)
        #define SINGLETON_CPP11(_)
        #define SINGLETON_CPP99(_) _
    #else
        #define SINGLETON_CPP23(_)
        #define SINGLETON_CPP20(_)
        #define SINGLETON_CPP17(_)
        #define SINGLETON_CPP14(_)
        #define SINGLETON_CPP11(_)
        #define SINGLETON_CPP99(_)
    #endif

    ////////////////////////////////////////////////////////////
    // Define a macro to handle cpp features compatibility
    ////////////////////////////////////////////////////////////
    /** Usage:
     * @example
     * void func() SINGLETON_CPP14([[deprecated]]);
     *
     * @example
     * void func() SINGLETON_CPP([[deprecated]], 14);
    \**********************************************************/
    #define SINGLETON_CPP(_, version) SINGLETON_CPP##version(_)

#else
    #define SINGLETON_EXTERN_C extern

    #define SINGLETON_CPP23(_)
    #define SINGLETON_CPP20(_)
    #define SINGLETON_CPP17(_)
    #define SINGLETON_CPP14(_)
    #define SINGLETON_CPP11(_)
    #define SINGLETON_CPP99(_)
    #define SINGLETON_CPP(_, version)
#endif

////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if defined(SINGLETON_SYSTEM_WINDOWS)

    // Windows compilers need specific (and different) keywords for export and import
    #define SINGLETON_API_EXPORT extern "C" __declspec(dllexport)
    #define SINGLETON_API_IMPORT SINGLETON_EXTERN_C __declspec(dllimport)

    // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
    #ifdef _MSC_VER

        #pragma warning(disable : 4251)

    #endif

#else // Linux, FreeBSD, Mac OS X

    #if __GNUC__ >= 4

        // GCC 4 has special keywords for showing/hidding symbols,
        // the same keyword is used for both importing and exporting
        #define SINGLETON_API_EXPORT extern "C" __attribute__ ((__visibility__ ("default")))
        #define SINGLETON_API_IMPORT SINGLETON_EXTERN_C __attribute__ ((__visibility__ ("default")))

    #else

        // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
        #define SINGLETON_API_EXPORT extern "C"
        #define SINGLETON_API_IMPORT SINGLETON_EXTERN_C

    #endif

#endif


#ifdef SINGLETON_SYSTEM_WINDOWS

    // Windows compilers use a different name for the main function
    #define SINGLETON_GUI_MAIN(hInstance, hPrevInstance, lpCmdLine, nCmdShow) WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    #define SINGLETON_MAIN(ac, av, env) main(int ac, char *av[], char *env[])

#elif defined(SINGLETON_SYSTEM_ANDROID)

    // Android doesn't need a main function
    #define SINGLETON_GUI_MAIN(app) android_main(struct android_app* app)
    #define SINGLETON_MAIN

#elif defined(SINGLETON_SYSTEM_MACOS)

    // On MacOS X, we use a Unix main function
    #define SINGLETON_MAIN(ac, av, env, apple) main(int ac, char *av[], char *env[], char *apple[])

#else

    // Other platforms should use the standard main function
    #define SINGLETON_MAIN(ac, av, env) main(int ac, char *av[], char *env[])
#endif

////////////////////////////////////////////////////////////
// Define portable NULL pointer using C++11 nullptr keyword
////////////////////////////////////////////////////////////
#ifdef __cplusplus
#elif !defined(NULL)
    #define nullptr ((void*)0)
#else
    #define nullptr NULL
#endif

////////////////////////////////////////////////////////////
// Define boolean type and values
////////////////////////////////////////////////////////////
#if defined(__cplusplus)
#elif !defined(__bool_true_false_are_defined)
    #define bool _Bool
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined 1
#endif

////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if (defined(_DEBUG) || defined(DEBUG)) && !defined(NDEBUG)

    #define SINGLETON_DEBUG
    #define SINGLETON_DEBUG_STRING "Debug"

#else
    #define SINGLETON_DEBUG_STRING "Release"
#endif


#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
    ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif

////////////////////////////////////////////////////////////
// Define a portable way to declare a function as deprecated
////////////////////////////////////////////////////////////
/** Usage:
 * @example "for functions"
 *   SINGLETON_DEPRECATED void func();
 * @example "for structs"
 *   struct SINGLETON_DEPRECATED MyStruct { ... };
 * @example "for enums"
 *   enum SINGLETON_DEPRECATED MyEnum { ... };
 *   enum MyEnum {
 *        MyEnum1 = 0,
 *        MyEnum2 SINGLETON_DEPRECATED,
 *        MyEnum3
 *   };
 * @example "for classes"
 *   class SINGLETON_DEPRECATED MyClass { ... };
\**********************************************************/
#ifdef SINGLETON_DISABLE_DEPRECATION

    #define SINGLETON_DEPRECATED
    #define SINGLETON_DEPRECATED_MSG(message)
    #define SINGLETON_DEPRECATED_VMSG(version, message)

#elif defined(__cplusplus) && (__cplusplus >= 201402)

    #define SINGLETON_DEPRECATED [[deprecated]]

    #if (__cplusplus >= 201402) && (__cplusplus < 201703)

        #define SINGLETON_DEPRECATED_MSG(message) [[deprecated(message)]]
        #define SINGLETON_DEPRECATED_VMSG(version, message) \
            [[deprecated("since " # version ". " message)]]

    #else
        #define SINGLETON_DEPRECATED_MSG(message) [[deprecated]]
        #define SINGLETON_DEPRECATED_VMSG(version, message) [[deprecated]]
    #endif

#elif defined(SINGLETON_COMPILER_MSVC) && (_MSC_VER >= 1400)

    #define SINGLETON_DEPRECATED __declspec(deprecated)

    #if (_MSC_VER >= 1900)

        #define SINGLETON_DEPRECATED_MSG(message) __declspec(deprecated(message))
        #define SINGLETON_DEPRECATED_VMSG(version, message) \
            __declspec(deprecated("since " # version ". " message))

    #else
        #define SINGLETON_DEPRECATED_MSG(message) __declspec(deprecated)
        #define SINGLETON_DEPRECATED_VMSG(version, message) __declspec(deprecated)
    #endif

#elif defined(SINGLETON_COMPILER_CLANG) && defined(__has_feature)

    #define SINGLETON_DEPRECATED __attribute__((deprecated))

    #if __has_feature(attribute_deprecated_with_message)

        #define SINGLETON_DEPRECATED_MSG(message) __attribute__((deprecated(message)))
        #define SINGLETON_DEPRECATED_VMSG(version, message) \
            __attribute__((deprecated("since " # version ". " message)))

    #else
        #define SINGLETON_DEPRECATED_MSG(message) __attribute__((deprecated))
        #define SINGLETON_DEPRECATED_VMSG(version, message) __attribute__((deprecated))
    #endif

#elif defined(SINGLETON_COMPILER_GCC) && defined(__GNUC__) && __GNUC_PREREQ(4, 5)

    #define SINGLETON_DEPRECATED __attribute__((deprecated))

    #if defined(SINGLETON_COMPILER_GCC) && defined(__GNUC__) && __GNUC_PREREQ(4, 9)

        #define SINGLETON_DEPRECATED_MSG(message) __attribute__((deprecated(message)))
        #define SINGLETON_DEPRECATED_VMSG(version, message) \
            __attribute__((deprecated("since " # version ". " message)))

    #else
        #define SINGLETON_DEPRECATED_MSG(message) __attribute__((deprecated))
        #define SINGLETON_DEPRECATED_VMSG(version, message) __attribute__((deprecated))
    #endif

#else

    #pragma message("WARNING: SINGLETON_DEPRECATED not supported on this compiler")
    #define SINGLETON_DEPRECATED
    #define SINGLETON_DEPRECATED_MSG(message)
    #define SINGLETON_DEPRECATED_VMSG(version, message)
#endif


////////////////////////////////////////////////////////////
// Define a portable way for packing structures
////////////////////////////////////////////////////////////
/** Usage:
 * @example
 * PACKED(struct MyStruct
 * {
 *     int a;
 *     char b;
 *     ...
 * });
\**********************************************************/
#if defined(__GNUC__) || defined(__GNUG__)
    #define PACKED( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#elif _MSC_VER
    #define PACKED( __Declaration__ ) __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#else
    #define PACKED( __Declaration__ ) __Declaration__
#endif

////////////////////////////////////////////////////////////
// Define other portable macros for various compilers
////////////////////////////////////////////////////////////
#define NEED_COMMA struct _
#define ATTRIBUTE(key) __attribute__((key))
#define UNUSED_ATTRIBUTE ATTRIBUTE(unused)
#define UNUSED(x) (void)(x)

#endif /* !DISTRIBUTION_H_ */


#ifndef VERSION_H_
    #define VERSION_H_

////////////////////////////////////////////////////////////
// Define the SINGLETON version
////////////////////////////////////////////////////////////
#ifdef FLAG_VERSION_MAJOR
    #define SINGLETON_VERSION_MAJOR FLAG_VERSION_MAJOR
#else
    #define SINGLETON_VERSION_MAJOR 0
#endif

#ifdef FLAG_VERSION_MINOR
    #define SINGLETON_VERSION_MINOR FLAG_VERSION_MINOR
#else
    #define SINGLETON_VERSION_MINOR 0
#endif

#ifdef FLAG_VERSION_PATCH
    #define SINGLETON_VERSION_PATCH FLAG_VERSION_PATCH
#else
    #define SINGLETON_VERSION_PATCH 0
#endif

#ifdef FLAG_VERSION_TWEAK
    #define SINGLETON_VERSION_TWEAK FLAG_VERSION_TWEAK
#else
    #define SINGLETON_VERSION_TWEAK 0
#endif

////////////////////////////////////////////////////////////
// Define the SINGLETON version number
////////////////////////////////////////////////////////////
#define SINGLETON_VERSION \
        (SINGLETON_VERSION_MAJOR * 1000000 + \
        SINGLETON_VERSION_MINOR * 10000 + \
        SINGLETON_VERSION_PATCH * 100 + \
        SINGLETON_VERSION_TWEAK)

#define SINGLETON_PREREQ_VERSION(maj, min, pat) (SINGLETON_VERSION >= (maj * 1000000 + min * 10000 + pat * 100))

////////////////////////////////////////////////////////////
// Define the SINGLETON version concatenated
////////////////////////////////////////////////////////////
#define SINGLETON_VERSION_CCT SINGLETON_VERSION_MAJOR##_##SINGLETON_VERSION_MINOR##_##SINGLETON_VERSION_PATCH##_##SINGLETON_VERSION_TWEAK


////////////////////////////////////////////////////////////
// Define the SINGLETON version string
////////////////////////////////////////////////////////////
// Helper macro to convert a macro to a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define SINGLETON_VERSION_STRING \
        TOSTRING(SINGLETON_VERSION_MAJOR) "." \
        TOSTRING(SINGLETON_VERSION_MINOR) "." \
        TOSTRING(SINGLETON_VERSION_PATCH) "." \
        TOSTRING(SINGLETON_VERSION_TWEAK)

#endif /* !VERSION_H_ */


////////////////////////////////////////////////////////////
// Compile-Time Configuration Parameters
////////////////////////////////////////////////////////////
#define SINGLETON_CONFIG_STRING \
        "SINGLETON_VERSION=" SINGLETON_VERSION_STRING "\n" \
        "SINGLETON_SYSTEM=" SINGLETON_SYSTEM_STRING "\n" \
        "SINGLETON_COMPILER=" SINGLETON_COMPILER_STRING "\n" \
        "SINGLETON_DEBUG=" SINGLETON_DEBUG_STRING "\n"

#endif /* !CONFIG_H_ */
// clang-format on
