// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

#define STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");

namespace CppUtils::ContainerOps::Detail
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
            : m_Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetFront(std::array<ElementType, Capacity>& arr)
            : m_Arr(arr)
        {
        }

        constexpr const ElementType& Do() const
            requires (IsConstAfterRemovingRef<T>())
        {
            STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR;
            return m_Arr.front();
        }

        constexpr ElementType& Do() const
            requires (!IsConstAfterRemovingRef<T>())
        {
            STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR;
            return m_Arr.front();
        }
        
private:

        T m_Arr {};
    };
        
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetBack<T, std::array<ElementType, Capacity>>
    {
        constexpr explicit ContainerOp_GetBack(const std::array<ElementType, Capacity>& arr)
            : m_Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetBack(std::array<ElementType, Capacity>& arr)
            : m_Arr(arr)
        {
        }
        
        constexpr const ElementType& Do() const
            requires (IsConstAfterRemovingRef<T>())
        {
            STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR;
            return m_Arr.back();
        }

        constexpr ElementType& Do() const
            requires (!IsConstAfterRemovingRef<T>())
        {
            STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR;
            return m_Arr.back();
        }
        
private:

        T m_Arr {};
    };
        
    template <class T, class ElementType, std::size_t Capacity>
    struct ContainerOp_GetElement<T, std::array<ElementType, Capacity>>
    {
        constexpr explicit ContainerOp_GetElement(const std::array<ElementType, Capacity>& arr)
            : m_Arr(arr)
        {
        }

        constexpr explicit ContainerOp_GetElement(std::array<ElementType, Capacity>& arr)
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

#if !defined(STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR)
#    error "STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR macro expected to be defined."
#endif
#undef STATIC_ASSERT_GETFRONT_OR_GETBACK_UNDEFINED_BEHAVIOR