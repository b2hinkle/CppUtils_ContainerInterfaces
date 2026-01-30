// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

namespace CppUtils
{    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetCapacity<T, std::array<ElementType, Capacity>>
    {
        consteval explicit ContainerOp_GetCapacity(const std::array<ElementType, Capacity>&)
        {
        }

        consteval std::size_t Do() const { return Capacity; }
    };





    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetSize<T, std::array<ElementType, Capacity>>
    {
        consteval explicit ContainerOp_GetSize(const std::array<ElementType, Capacity>&)
        {
        }

        consteval std::size_t Do() const { return Capacity; }
    };
    

    
    
    
    
    
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_IsValidIndex<T, std::array<ElementType, Capacity>>
    {
        consteval explicit ContainerOp_IsValidIndex(const std::array<ElementType, Capacity>&)
        {
        }

        consteval bool Do(const std::size_t index) const
        {
            return index >= 0
                && index < Capacity;
        }
    };
    
    
    

    
    
    
    
    

    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_IsEmpty<T, std::array<ElementType, Capacity>>
    {
        consteval explicit ContainerOp_IsEmpty(const std::array<ElementType, Capacity>&)
        {
        }

        consteval bool Do() const
        {
            return Capacity == 0;
        }
    };
    
    
    

    


    

    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetFront<T, std::array<ElementType, Capacity>>
    {
        constexpr explicit ContainerOp_GetFront(const std::array<ElementType, Capacity>& arr)
            : Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetFront(std::array<ElementType, Capacity>& arr)
            : Arr(arr)
        {
        }

        constexpr const ElementType& Do()
            requires (IsConstAfterRemovingRef<T>())
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return Arr.front();
        }

        constexpr ElementType& Do()
            requires (!IsConstAfterRemovingRef<T>())
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return Arr.front();
        }
        
private:

        T Arr {};
    };
    
    
    

    
    
    
    
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetBack<T, std::array<ElementType, Capacity>>
    {
        constexpr explicit ContainerOp_GetBack(const std::array<ElementType, Capacity>& arr)
            : Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetBack(std::array<ElementType, Capacity>& arr)
            : Arr(arr)
        {
        }

        constexpr const ElementType& Do()
            requires (IsConstAfterRemovingRef<T>())
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return Arr.back();
        }

        constexpr ElementType& Do()
            requires (!IsConstAfterRemovingRef<T>())
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return Arr.back();
        }
        
private:

        T Arr {};
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
