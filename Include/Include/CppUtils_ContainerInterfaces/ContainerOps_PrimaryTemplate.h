// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils/Misc/Tag_IsPrimaryTemplate.h>

#define CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOpName) \
    static_assert(sizeof(T) && false, "Provided container type has no implementation for " #ContainerOpName ". Either not supported by the container type, or the specialization simply wasn't implemented yet.");

namespace CppUtils::ContainerOps::Detail
{
    /*
    * Creates compatability with the container op specializations.
    * This way, all forms of a container type resolve to the same container operation.
    */
    template <class T>
    using SpecializationCompatibleT = std::remove_cvref_t<T>;
}

/*
* All container operations which different container types can specialize to provide specific implementations.
* T is the fully untouched type provided by the caller.
* SpecializationKey is an automatically handled argument which facilitates the specialization selection. We specialize
* based on a normalized T (check SpecializationCompatibleT for normalization process) container type to avoid multiple specializations for a single container operation.
*/
namespace CppUtils::ContainerOps::Detail
{
    /*
    * Returns the number of elements that the container has currently allocated space for.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetCapacity : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_GetCapacity);
    };
    
    /*
    * Returns the number of elements in the container.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetSize : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_GetSize);
    };
    
    /*
    * Returns whether the provided index is within the bounds of the container's size.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_IsValidIndex : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_IsValidIndex);
    };
    
    /*
    * Returns whether the container has any elements.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_IsEmpty : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_IsEmpty);
    };
    
    /*
    * Returns the first element in the container.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetFront : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_GetFront);
    };
    
    /*
    * Returns the last element in the container.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetBack : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_GetBack);
    };
    
    /*
    * Returns the element at index via direct access. No bounds checking.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetElement : Tag_IsPrimaryTemplate
    {
        CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT(ContainerOp_GetElement);
    };

}

#if !defined(CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT)
#    error "CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT macro expected to be defined."
#endif
#undef CONTAINER_OP_PRIMARY_TEMPLATE_STATIC_ASSERT
