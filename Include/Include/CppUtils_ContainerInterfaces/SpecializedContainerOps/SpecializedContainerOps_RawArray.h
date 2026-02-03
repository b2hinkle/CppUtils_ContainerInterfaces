// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

/*
* Some raw array details to keep in mind:
*   - It is not possible for raw arrays to exist with no size/capacity.
*/
namespace CppUtils
{
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetCapacity<T, ElementType[Capacity]>
    {
        consteval explicit ContainerOp_GetCapacity(const ElementType (&)[Capacity])
        {
        }

        consteval std::size_t Do() const { return Capacity; }
    };

    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetSize<T, ElementType[Capacity]>
    {
        consteval explicit ContainerOp_GetSize(const ElementType (&)[Capacity])
        {
        }

        consteval std::size_t Do() const { return Capacity; }
    };
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_IsValidIndex<T, ElementType[Capacity]>
    {
        consteval explicit ContainerOp_IsValidIndex(const ElementType (&)[Capacity])
        {
        }

        consteval bool Do(const std::size_t index) const
        {
            return index >= 0
                && index < Capacity;
        }
    };
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_IsEmpty<T, ElementType[Capacity]>
    {
        consteval explicit ContainerOp_IsEmpty(const ElementType (&)[Capacity])
        {

        }

        consteval bool Do() const
        {
            return false;
        }
    };
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetFront<T, ElementType[Capacity]>
    {
        constexpr explicit ContainerOp_GetFront(const ElementType (&arr)[Capacity])
            : m_Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetFront(ElementType (&arr)[Capacity])
            : m_Arr(arr)
        {
        }

        constexpr const ElementType& Do()
            requires (IsConstAfterRemovingRef<T>())
        {
            
            return m_Arr[0];
        }

        constexpr ElementType& Do()
            requires (!IsConstAfterRemovingRef<T>())
        {
            return m_Arr[0];
        }
        
private:

        T m_Arr {};
    };
    
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetBack<T, ElementType[Capacity]>
    {
        constexpr explicit ContainerOp_GetBack(const ElementType (&arr)[Capacity])
            : m_Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetBack(ElementType (&arr)[Capacity])
            : m_Arr(arr)
        {
        }

        constexpr const ElementType& Do()
            requires (IsConstAfterRemovingRef<T>())
        {
            return m_Arr[Capacity - 1];
        }

        constexpr ElementType& Do()
            requires (!IsConstAfterRemovingRef<T>())
        {
            return m_Arr[Capacity - 1];
        }
        
private:

        T m_Arr {};
    };
    
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetElement<T, ElementType[Capacity]>
    {
        constexpr explicit ContainerOp_GetElement(const ElementType (&arr)[Capacity])
            : m_Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetElement(ElementType (&arr)[Capacity])
            : m_Arr(arr)
        {
        }
        
        constexpr const ElementType& Do(const std::size_t index) const
            requires (IsConstAfterRemovingRef<T>())
        {
            return m_Arr[index];
        }

        constexpr ElementType& Do(const std::size_t index) const
            requires (!IsConstAfterRemovingRef<T>())
        {
            return m_Arr[index];
        }
        
private:

        T m_Arr {};
    };
}
