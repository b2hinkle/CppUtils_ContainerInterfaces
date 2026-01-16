// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

/*
* All possible implementable container operations.
*/
namespace CppUtils
{

    template <class T>
    struct ContainerOp_GetCapacity;
    
    template <class T>
    struct ContainerOp_GetSize;
    
    template <class T>
    struct ContainerOp_IsValidIndex;
    
    template <class T>
    struct ContainerOp_IsEmpty;
    
    template <class T>
    struct ContainerOp_GetFront;
    
    template <class T>
    struct ContainerOp_GetBack;
    
    // TODO: I believe we want this to be a better name, possibly use the term subscript. Reason is because we might have an At op that does bounds checking.
    template <class T, class NeuteredT>
    struct ContainerOp_GetElement;

}