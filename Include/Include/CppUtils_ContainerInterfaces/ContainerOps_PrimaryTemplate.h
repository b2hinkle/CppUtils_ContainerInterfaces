// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>

/*
* All container operations which different container types can specialize to provide specific implementations.
* T is the fully qualified type provided by the caller.
* UnqualifiedT is an automatically handled argument which facilitates the specialization selection. We specialize
* based on a fully unqualified (no ref or cv) container type to avoid multiple specializations for a single container operation.
* 
* NOTE: I dislike how we use default template argument for selecting partial specializations, but I've not found an
*       alternative yet which still takes advantage of template specialization. We could possibly create a
*       specialization selection helper struct which could hide the parameter, but that seems more complex than needed.
*/
namespace CppUtils
{
    /*
    * Our rule which creates compatability with the container op specializations.
    */
    template <class T>
    using StripQualifiers = std::remove_cvref_t<T>;

    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_GetCapacity;
    
    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_GetSize;
    
    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_IsValidIndex;
    
    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_IsEmpty;
    
    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_GetFront;
    
    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_GetBack;
    
    /*
    * Accesses element at index, no bounds checking (e.g. subscript behavior on an array).
    */
    template <class T, class UnqualifiedT = StripQualifiers<T>>
    struct ContainerOp_GetElement;

}