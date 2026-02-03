// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <utility>
#include <CppUtils_ContainerInterfaces/ContainerOpInterfaces.h>

/*
 * Container ops provide a uniform, type-erased interface for performing common
 * container operations without requiring knowledge of the container’s concrete type.
 *
 * Each operation is expressed as a lightweight interface wrapper that resolves,
 * at compile time, to the appropriate container-specific implementation via
 * specialization. This allows generic code to interact with a wide variety of
 * container types while retaining static type safety and zero runtime overhead.
 *
 * Containers opt into support by providing specializations for the corresponding
 * ContainerOp_* templates.
 */
namespace CppUtils::ContainerOps
{
    template <class ContainerType>
    using GetCapacity = ContainerOpInterface_GetCapacity<ContainerType>;

    template <class ContainerType>
    using GetSize = ContainerOpInterface_GetSize<ContainerType>;

    template <class ContainerType>
    using IsValidIndex = ContainerOpInterface_IsValidIndex<ContainerType>;

    template <class ContainerType>
    using IsEmpty = ContainerOpInterface_IsEmpty<ContainerType>;

    template <class ContainerType>
    using GetFront = ContainerOpInterface_GetFront<ContainerType>;

    template <class ContainerType>
    using GetBack = ContainerOpInterface_GetBack<ContainerType>;

    template <class ContainerType>
    using GetElement = ContainerOpInterface_GetElement<ContainerType>;
}
