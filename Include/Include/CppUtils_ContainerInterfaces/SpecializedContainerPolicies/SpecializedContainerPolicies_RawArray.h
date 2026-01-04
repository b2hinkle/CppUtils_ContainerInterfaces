// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <CppUtils_ContainerInterfaces/ContainerPolicies_PrimaryTemplate.h>

namespace CppUtils
{
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetCapacity<T[Capacity]>
    {
        static consteval std::size_t Do(const T (&)[Capacity])
        {
            return Capacity;
        }
        
        static consteval std::size_t Do(T (&)[Capacity])
        {
            return Capacity;
        }
    };





    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetSize<T[Capacity]>
    {
        static consteval std::size_t Do(const T (&)[Capacity])
        {
            return Capacity;
        }
    };
    

    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_IsValidIndex<T[Capacity]>
    {
        static consteval bool Do(const T (&)[Capacity], const std::size_t index)
        {
            return index >= 0
                && index < Capacity;
        }
    };
    
    
    

    
    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_IsEmpty<T[Capacity]>
    {
        static consteval bool Do(const T (&)[Capacity])
        {
            // NOTE: It is not possible for raw arrays to exist with no size/capacity.
            return false;
        }
    };
    
    
    

    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetFront<T[Capacity]>
    {
        static constexpr const T& Do(const T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[0];
        }
        
        static constexpr T& Do(T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[0];
        }
    };
    
    
    

    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetBack<T[Capacity]>
    {
        static constexpr const T& Do(const T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[Capacity - 1];
        }
        
        static constexpr T& Do(T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[Capacity - 1];
        }
    };
    
    
    

    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetElement<T[Capacity]>
    {
        static constexpr const T& Do(const T (&arr)[Capacity], const std::size_t index)
        {
            return arr[index];
        }

        static constexpr T& Do(T (&arr)[Capacity], const std::size_t index)
        {
            return arr[index];
        }
    };   
}