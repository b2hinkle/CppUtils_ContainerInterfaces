// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <vector>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

namespace CppUtils
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




}
