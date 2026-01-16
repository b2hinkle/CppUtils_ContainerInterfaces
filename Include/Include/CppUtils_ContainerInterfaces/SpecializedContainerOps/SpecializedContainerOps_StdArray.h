// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <CppUtils_Misc/TypeTraits.h>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

namespace CppUtils
{    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetCapacity<T, std::array<ElementType, Capacity>>
    {
        consteval explicit ContainerOp_GetCapacity(const std::array<ElementType, Capacity>&)
        {
        }

        consteval std::size_t Do() { return Capacity; }
    };





    template <class T, std::size_t Capacity>
    struct ContainerOp_GetSize<std::array<T, Capacity>>
    {
        static consteval std::size_t Do(const std::array<T, Capacity>&)
        {
            return Capacity;
        }
    };
    

    
    
    
    
    
    
    template <class T, std::size_t Capacity>
    struct ContainerOp_IsValidIndex<std::array<T, Capacity>>
    {
        static consteval bool Do(const std::array<T, Capacity>&, const std::size_t index)
        {
            return index >= 0
                && index < Capacity;
        }
    };
    
    
    

    
    
    
    
    

    template <class T, std::size_t Capacity>
    struct ContainerOp_IsEmpty<std::array<T, Capacity>>
    {
        static consteval bool Do(const std::array<T, Capacity>&)
        {
            return Capacity == 0;
        }
    };
    
    
    

    


    

    template <class T, std::size_t Capacity>
    struct ContainerOp_GetFront<std::array<T, Capacity>>
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
    struct ContainerOp_GetBack<std::array<T, Capacity>>
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
    
    
    

    
    
    
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetElement<T, std::array<ElementType, Capacity>>
    {
        constexpr explicit ContainerOp_GetElement(const std::array<ElementType, Capacity>& arr)
            : Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetElement(std::array<ElementType, Capacity>& arr)
            : Arr(arr)
        {
        }

        constexpr const ElementType& Do(const std::size_t index) const
            requires (IsConstAfterRemovingRef<T>())
        {
            return Arr[index];
        }

        constexpr ElementType& Do(const std::size_t index) const
            requires (!IsConstAfterRemovingRef<T>())
        {
            return Arr[index];
        }
        
private:

        T Arr {};
    };    
}
