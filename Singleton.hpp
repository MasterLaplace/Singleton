/**************************************************************************
 * Singleton v1.0.1
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
 * @file Singleton.hpp
 * @brief A thread-safe Singleton template class.
 *
 * @author @MasterLaplace
 * @version 1.0.1
 * @date 2024-11-06
 **************************************************************************/

// clang-format off
#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include "config.h"

#include <iostream>
#include <cassert>

#ifndef SINGLETON_NO_THREAD_SAFETY
#define SINGLETON_THREAD_SAFE(_) _

#include <mutex>
#else
#define SINGLETON_THREAD_SAFE(_)
#endif /* !SINGLETON_NO_THREAD_SAFETY */

/**
 * @brief A thread-safe Singleton template class.
 *
 * This class provides a thread-safe implementation of the Singleton design pattern.
 * You can inherit from this class to create a Singleton object.
 * It ensures that only one instance of the class is created and provides global
 * access to that instance.
 *
 * @note This class is thread-safe by default. You can desable thread-safety
 *      by defining SINGLETON_NO_THREAD_SAFETY before including this header.
 *
 * @tparam T The type of the Singleton class.
 */
template <typename T>
class Singleton {
    public:
        /**
         * @brief Create an instance of the Singleton class.
         *
         * This method creates an instance of the Singleton class with the
         * provided arguments. If an instance already exists, it will assert.
         *
         * @tparam Args The types of the arguments to pass to the constructor.
         * @param args The arguments to pass to the constructor.
         */
        template <typename... Args>
        static inline void CreateInstance(Args &&...args);

        /**
         * @brief Reset the Singleton instance with new arguments.
         *
         * This method deletes the current instance and creates a new one with
         * the provided arguments. If no instance exists, it will assert.
         *
         * @tparam Args The types of the arguments to pass to the constructor.
         * @param args The arguments to pass to the constructor.
         */
        template <typename... Args>
        static inline void ResetInstance(Args &&...args);

        /**
         * @brief Get the Singleton instance.
         *
         * This method returns a reference to the Singleton instance.
         * If no instance exists, it will assert.
         *
         * @note This method locks the instance mutex. Make sure to call
         *       UnlockInstance after use. If SINGLETON_NO_THREAD_SAFETY is
         *       defined, this method will not lock the instance mutex.
         *
         * @return T& A reference to the Singleton instance.
         */
        static inline T &GetInstance();

        /**
         * @brief Unlock the Singleton instance.
         *
         * This method unlocks the instance mutex after use.
         * If SINGLETON_NO_THREAD_SAFETY is defined, this method does nothing.
         *
         * @note Make sure to call this method after calling GetInstance.
         */
        static inline void UnlockInstance();

        /**
         * @brief Destroy the Singleton instance.
         *
         * This method deletes the Singleton instance and sets the instance
         * pointer to nullptr. If no instance exists, it will assert.
         */
        static inline void DestroyInstance();

        /**
         * @brief Deleted copy constructor.
         *
         * This prevents copying of the Singleton instance.
         *
         * @param copy The instance to copy.
         */
        Singleton(const T &copy) = delete;

        /**
         * @brief Deleted copy assignment operator.
         *
         * This prevents assignment of the Singleton instance.
         *
         * @param copy The instance to assign.
         * @return T& A reference to the assigned instance.
         */
        T &operator=(const T &copy) = delete;

    protected:
        /**
         * @brief Protected default constructor.
         *
         * This ensures that the Singleton class can only be instantiated through
         * the CreateInstance method.
         */
        Singleton() = default;

        /**
         * @brief Protected virtual destructor.
         *
         * This ensures that the Singleton class can be properly destroyed.
         */
        virtual ~Singleton() = default;

    private:
        /**
         * @brief Pointer to the Singleton instance.
         */
        static SINGLETON_CPP17(inline) T *_instance SINGLETON_CPP17(= nullptr);

#ifndef SINGLETON_NO_THREAD_SAFETY
        /**
         * @brief Mutex for thread-safe access to the Singleton instance.
         */
        static SINGLETON_CPP17(inline) std::mutex _mutex;
#endif /* !SINGLETON_NO_THREAD_SAFETY */
};

#endif /* !SINGLETON_HPP_ */

////////////////////////////////////////////////////////////////////////////////
/*                               IMPLEMENTATION                               */
////////////////////////////////////////////////////////////////////////////////
#ifdef SINGLETON_IMPLEMENTATION
#ifndef SINGLETON_CPP_ONCE
    #define SINGLETON_CPP_ONCE

#if __cplusplus < 201703L

template <typename T>
T *Singleton<T>::_instance;

#ifndef SINGLETON_NO_THREAD_SAFETY
template <typename T>
std::mutex Singleton<T>::_mutex;
#endif /* !SINGLETON_NO_THREAD_SAFETY */

#endif /* __cplusplus < 201703L */

template <typename T>
template <typename... Args>
inline void Singleton<T>::CreateInstance(Args &&...args)
{
    assert(!_instance && "Singleton instance is already created! Use ResetInstance() to reset it.");

    SINGLETON_THREAD_SAFE(std::lock_guard<std::mutex> lock(_mutex));

    _instance = new T(std::forward<Args>(args)...);
}

template <typename T>
template <typename... Args>
inline void Singleton<T>::ResetInstance(Args &&...args)
{
    assert(_instance && "Singleton instance is not created yet!");

    SINGLETON_THREAD_SAFE(std::lock_guard<std::mutex> lock(_mutex));

    delete _instance;
    _instance = new T(std::forward<Args>(args)...);
}

template <typename T>
inline T &Singleton<T>::GetInstance()
{
    assert(_instance && "Singleton instance is not created yet!");

    SINGLETON_THREAD_SAFE(_mutex.lock());

    return *_instance;
}

template <typename T>
inline void Singleton<T>::UnlockInstance()
{
    assert(_instance && "Singleton instance is not created yet!");

    SINGLETON_THREAD_SAFE(_mutex.unlock());
}

template <typename T>
inline void Singleton<T>::DestroyInstance()
{
    assert(_instance && "Singleton instance is not created yet!");

    SINGLETON_THREAD_SAFE(std::lock_guard<std::mutex> lock(_mutex));

    delete _instance;
    _instance = nullptr;
}

#endif /* !SINGLETON_CPP_ONCE */
#endif /* !SINGLETON_IMPLEMENTATION */
// clang-format on
