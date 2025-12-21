// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>

namespace CppUtils
{
    // Raw array.
    template <class T, std::size_t Capacity>
    consteval std::size_t ArrayGetCapacity(const T (&)[Capacity])
    {
        return Capacity;
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    consteval std::size_t ArrayGetCapacity(const std::array<T, Capacity>&)
    {
        return Capacity;
    }
    
    
    
    
    
    // Raw array.
    template <class T, std::size_t Capacity>
    consteval std::size_t ArrayGetSize(const T (&)[Capacity])
    {
        return Capacity;
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    consteval std::size_t ArrayGetSize(const std::array<T, Capacity>&)
    {
        return Capacity;
    }
    
    
    
    
    // Raw array.
    template <class T, std::size_t Capacity>
    consteval bool ArrayIsValidIndex(const T (&)[Capacity], const std::size_t index)
    {
        return index >= 0
            && index < Capacity;
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    consteval bool ArrayIsValidIndex(const std::array<T, Capacity>&, const std::size_t index)
    {
        return index >= 0
            && index < Capacity;
    }

    
    
    
    // Raw array.
    template <class T, std::size_t Capacity>
    consteval std::size_t ArrayIsEmpty(const T (&)[Capacity])
    {
        // NOTE: It is not possible for raw arrays to exist with no size/capacity.
        return false;
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    consteval std::size_t ArrayIsEmpty(const std::array<T, Capacity>&)
    {
        return Capacity == 0;
    }
    
    
    
    // Raw array.
    template <class T, std::size_t Capacity>
    constexpr T& ArrayGetFront(const T (&arr)[Capacity])
    {
        static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
        return arr[0];
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    constexpr std::size_t ArrayGetFront(const std::array<T, Capacity>& arr)
    {
        static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
        return arr.front();
    }
    
    
    
    // Raw array.
    template <class T, std::size_t Capacity>
    constexpr T& ArrayGetBack(const T (&arr)[Capacity])
    {
        static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
        return arr[Capacity - 1];
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    constexpr std::size_t ArrayGetBack(const std::array<T, Capacity>& arr)
    {
        static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
        return arr.back();
    }
    
    
    
    
    
    // Raw array.
    template <class T, std::size_t Capacity>
    constexpr T& ArrayGetElement(T (&arr)[Capacity], const std::size_t index)
    {
        return arr[index];
    }
    template <class T, std::size_t Capacity>
    constexpr const T& ArrayGetElement(const T (&arr)[Capacity], const std::size_t index)
    {
        return arr[index];
    }
    
    // std::array.
    template <class T, std::size_t Capacity>
    constexpr T& ArrayGetElement(std::array<T, Capacity>& arr, const std::size_t index)
    {
        return arr[index];
    }
    template <class T, std::size_t Capacity>
    constexpr const T& ArrayGetElement(const std::array<T, Capacity>& arr, const std::size_t index)
    {
        return arr[index];
    }
    
}