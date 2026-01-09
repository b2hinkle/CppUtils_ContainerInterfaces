// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <CppUtils_ContainerInterfaces/ContainerPolicies_PrimaryTemplate.h>

namespace CppUtils
{    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetCapacity<std::array<T, Capacity>>
    {
        static consteval std::size_t Do(const std::array<T, Capacity>&)
        {
            return Capacity;
        }
        
        static consteval std::size_t Do(std::array<T, Capacity>&)
        {
            return Capacity;
        }
    };






    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetSize<std::array<T, Capacity>>
    {
        static consteval std::size_t Do(const std::array<T, Capacity>&)
        {
            return Capacity;
        }
    };
    

    
    
    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_IsValidIndex<std::array<T, Capacity>>
    {
        static consteval bool Do(const std::array<T, Capacity>&, const std::size_t index)
        {
            return index >= 0
                && index < Capacity;
        }
    };
    
    
    

    
    
    
    
    

    template <class T, std::size_t Capacity>
    struct ContainerPolicy_IsEmpty<std::array<T, Capacity>>
    {
        static consteval bool Do(const std::array<T, Capacity>&)
        {
            return Capacity == 0;
        }
    };
    
    
    

    


    

    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetFront<std::array<T, Capacity>>
    {
        static constexpr const T& Do(const std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.front();
        }
        
        static constexpr T& Do(std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.front();
        }
    };
    
    
    

    
    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetBack<std::array<T, Capacity>>
    {
        static constexpr const T& Do(const std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.back();
        }
        
        static constexpr T& Do(std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.back();
        }
    };
    
    
    

    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerPolicy_GetElement<std::array<T, Capacity>>
    {
        static constexpr const T& Do(const std::array<T, Capacity>& arr, const std::size_t index)
        {
            return arr[index];
        }

        static constexpr T& Do(std::array<T, Capacity>& arr, const std::size_t index)
        {
            return arr[index];
        }
    };    
}
