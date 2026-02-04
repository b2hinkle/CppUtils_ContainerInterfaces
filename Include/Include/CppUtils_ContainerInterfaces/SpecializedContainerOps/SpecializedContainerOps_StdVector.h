// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <vector>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

namespace CppUtils::ContainerOps::Detail
{
    template <class T, class ElementType>
    struct ContainerOp_GetCapacity<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_GetCapacity(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr std::size_t Do() const { return m_Vector.capacity(); }

private:

        T m_Vector;
    };

    template <class T, class ElementType>
    struct ContainerOp_GetSize<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_GetSize(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr std::size_t Do() const { return m_Vector.size(); }

private:

        T m_Vector;
    };

    template <class T, class ElementType>
    struct ContainerOp_IsValidIndex<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_IsValidIndex(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr bool Do(const std::size_t index) const
        {
            // Custom implementation, as std::vector has no existing function.
            return index >= 0
                && index < m_Vector.size();
        }

private:

        T m_Vector;
    };

    template <class T, class ElementType>
    struct ContainerOp_IsEmpty<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_IsEmpty(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr bool Do() const
        {
            return m_Vector.empty();
        }

private:

        T m_Vector;
    };

    template <class T, class ElementType>
    struct ContainerOp_GetFront<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_GetFront(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr explicit ContainerOp_GetFront(std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr const ElementType& Do() const
            requires (IsConstAfterRemovingRef<T>())
        {
            return m_Vector.front();
        }

        constexpr ElementType& Do() const
            requires (!IsConstAfterRemovingRef<T>())
        {
            return m_Vector.front();
        }

private:

        T m_Vector;
    };

    template <class T, class ElementType>
    struct ContainerOp_GetBack<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_GetBack(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr explicit ContainerOp_GetBack(std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr const ElementType& Do() const
            requires (IsConstAfterRemovingRef<T>())
        {
            return m_Vector.back();
        }

        constexpr ElementType& Do() const
            requires (!IsConstAfterRemovingRef<T>())
        {
            return m_Vector.back();
        }

private:

        T m_Vector;
    };

    template <class T, class ElementType>
    struct ContainerOp_GetElement<T, std::vector<ElementType, std::allocator<ElementType>>>
    {
        constexpr explicit ContainerOp_GetElement(const std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr explicit ContainerOp_GetElement(std::vector<ElementType, std::allocator<ElementType>>& vector)
            : m_Vector(vector)
        {
        }

        constexpr const ElementType& Do(const std::size_t index) const
            requires (IsConstAfterRemovingRef<T>())
        {
            return m_Vector[index];
        }

        constexpr ElementType& Do(const std::size_t index) const
            requires (!IsConstAfterRemovingRef<T>())
        {
            return m_Vector[index];
        }

private:

        T m_Vector;
    };
}
