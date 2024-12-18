/**************************************************************************
 * Singleton v1.0.2
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
 * @file singleton.h
 * @brief A thread-safe interface for singleton pattern implementation.
 *
 * @author @MasterLaplace
 * @version 1.0.2
 * @date 2024-11-06
 **************************************************************************/

// clang-format off
#ifndef SINGLETON_H_
#define SINGLETON_H_

#ifndef SINGLETON_STANDALONE
#include "singleton_config.h"

#else
#if defined(__cplusplus) && __cplusplus >= 201103L
    #define lpl_nullptr nullptr
#elif !defined(NULL)
    #define lpl_nullptr ((void*)0)
#else
    #define lpl_nullptr NULL
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(SINGLETON_COMPILER_MINGW) || defined(SINGLETON_COMPILER_CYGWIN)
#define SINGLETON_SYSTEM_WINDOWS
#endif

#endif /* !SINGLETON_STANDALONE */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef SINGLETON_NO_THREAD_SAFETY
#define SINGLETON_THREAD_SAFE(_) _

#ifdef SINGLETON_SYSTEM_WINDOWS
#include <windows.h>
#else
#include <pthread.h>
#endif
#else
#define SINGLETON_THREAD_SAFE(_)
#endif /* !SINGLETON_NO_THREAD_SAFETY */

/**
 * @struct singleton_t
 * @brief A structure representing a singleton pattern.
 *
 * This structure is used to implement the singleton design pattern, ensuring that only one instance
 * of a particular type exists throughout the program.
 *
 * @var singleton_t::data
 * A pointer to the data held by the singleton instance.
 *
 * @var singleton_t::create
 * A function pointer to a function that creates the singleton instance. The function takes a
 * variable argument list (va_list) and returns a pointer to the created instance.
 *
 * @var singleton_t::destroy
 * A function pointer to a function that destroys the singleton instance. The function takes a
 * pointer to the instance to be destroyed.
 */
typedef struct {
    void *data;
    void *(*create)(va_list args);
    void (*destroy)(void *);
} singleton_t;

/**
 * @brief Creates an instance of the singleton.
 *
 * This function initializes the singleton instance using the provided create
 * and destroy functions.
 *
 * @param create A function pointer to the creation function for the singleton instance.
 * @param destroy A function pointer to the destruction function for the singleton instance.
 * @param ... Additional arguments to be passed to the creation function.
 */
extern inline void instance_create(void *(*create)(va_list args), void (*destroy)(void *), ...);

/**
 * @brief Retrieves the singleton instance.
 *
 * This function returns a pointer to the singleton instance.
 *
 * @return A pointer to the singleton instance.
 */
extern inline singleton_t *instance_get();

/**
 * @brief Unlocks the singleton instance.
 *
 * This function unlocks the singleton instance, allowing it to be modified or
 * destroyed.
 */
extern inline void instance_unlock();

/**
 * @brief Destroys the singleton instance.
 *
 * This function destroys the singleton instance, freeing any allocated resources.
 */
extern inline void instance_destroy();

#endif /* !SINGLETON_H_ */

////////////////////////////////////////////////////////////////////////////////
/*                               IMPLEMENTATION                               */
////////////////////////////////////////////////////////////////////////////////
#ifdef SINGLETON_H_IMPLEMENTATION
#ifndef SINGLETON_C_ONCE
    #define SINGLETON_C_ONCE

static singleton_t *instance = lpl_nullptr;

#ifndef SINGLETON_NO_THREAD_SAFETY
#   ifdef SINGLETON_SYSTEM_WINDOWS
static HANDLE mutex = NULL;
#   else
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#   endif
#endif /* !SINGLETON_NO_THREAD_SAFETY */

inline void instance_create(void *(*create)(va_list args), void (*destroy)(void *), ...)
{
    assert(!instance && "singleton_t instance is already created! Use instance_reset() to reset it.");

#ifdef SINGLETON_SYSTEM_WINDOWS && !SINGLETON_NO_THREAD_SAFETY
    if (mutex == NULL)
        mutex = CreateMutex(NULL, FALSE, NULL);
#endif
    SINGLETON_THREAD_SAFE(pthread_mutex_lock(&mutex));

    instance = malloc(sizeof(singleton_t));
    instance->create = create;
    instance->destroy = destroy;

    va_list args;
    va_start(args, destroy);
    instance->data = instance->create(args);
    va_end(args);

    if (!instance->data)
    {
        free(instance);
        instance = lpl_nullptr;
    }

    SINGLETON_THREAD_SAFE(pthread_mutex_unlock(&mutex));
}

inline singleton_t *instance_get()
{
    assert(instance && "singleton_t instance is not created yet!");

    SINGLETON_THREAD_SAFE(pthread_mutex_lock(&mutex));

    return instance;
}

inline void instance_unlock()
{
    assert(instance && "singleton_t instance is not created yet!");

    SINGLETON_THREAD_SAFE(pthread_mutex_unlock(&mutex));
}

inline void instance_destroy()
{
    assert(instance && "singleton_t instance is not created yet!");

    SINGLETON_THREAD_SAFE(pthread_mutex_lock(&mutex));

    instance->destroy(instance->data);
    free(instance);
    instance = lpl_nullptr;

    SINGLETON_THREAD_SAFE(pthread_mutex_unlock(&mutex));
}

#endif /* !SINGLETON_C_ONCE */
#endif /* SINGLETON_H_IMPLEMENTATION */
// clang-format on
