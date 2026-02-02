// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>

/*
* All container operations which different container types can specialize to provide specific implementations.
* T is the fully untouched type provided by the caller.
* SpecializationKey is an automatically handled argument which facilitates the specialization selection. We specialize
* based on a normalized T (check SpecializationCompatibleT for normalization process) container type to avoid multiple specializations for a single container operation.
* 
* NOTE: I dislike how we use default template argument for selecting partial specializations, but I've not found an
*       alternative yet which still takes advantage of template specialization. We could possibly create a
*       specialization selection helper struct which could hide the parameter, but that seems more complex than needed.
*/
namespace CppUtils
{
    /*
    * Creates compatability with the container op specializations.
    * This way, all forms of a container type resolve to the same container operation.
    */
    template <class T>
    using SpecializationCompatibleT = std::remove_cvref_t<T>;

    /*
    * Returns the number of elements that the container has currently allocated space for.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetCapacity;
    
    /*
    * Returns the number of elements in the container.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetSize;
    
    /*
    * Returns whether the provided index is within the bounds of the container's size.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_IsValidIndex;
    
    /*
    * Returns whether the container has any elements.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_IsEmpty;
    
    /*
    * Returns the first element in the container.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetFront;
    
    /*
    * Returns the last element in the container.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetBack;
    
    /*
    * Returns the element at index via direct access. No bounds checking.
    */
    template <class T, class SpecializationKey = SpecializationCompatibleT<T>>
    struct ContainerOp_GetElement;

}