// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

/*
* All container operations which different container types can specialize to provide specific implementations.
* T is the fully qualified type provided by the caller.
* NeuteredT is fully unqualified (no ref or cv), allowing for a single specialization for each container operation.
*/
namespace CppUtils
{
    template <class T, class NeuteredT>
    struct ContainerOp_GetCapacity;
    
    template <class T, class NeuteredT>
    struct ContainerOp_GetSize;
    
    template <class T, class NeuteredT>
    struct ContainerOp_IsValidIndex;
    
    template <class T, class NeuteredT>
    struct ContainerOp_IsEmpty;
    
    template <class T, class NeuteredT>
    struct ContainerOp_GetFront;
    
    template <class T, class NeuteredT>
    struct ContainerOp_GetBack;
    
    // TODO: I believe we want this to be a better name, possibly use the term subscript. Reason is because we might have an At op that does bounds checking.
    template <class T, class NeuteredT>
    struct ContainerOp_GetElement;

}