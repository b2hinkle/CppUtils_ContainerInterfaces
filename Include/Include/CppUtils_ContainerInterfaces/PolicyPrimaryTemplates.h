// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

/*
* All possible implementable container operations.
*/
namespace CppUtils
{

    template <class T>
    struct ContainerPolicy_GetCapacity;
    
    template <class T>
    struct ContainerPolicy_GetSize;
    
    template <class T>
    struct ContainerPolicy_IsValidIndex;
    
    template <class T>
    struct ContainerPolicy_IsEmpty;
    
    template <class T>
    struct ContainerPolicy_GetFront;
    
    template <class T>
    struct ContainerPolicy_GetBack;
    
    template <class T>
    struct ContainerPolicy_GetElement;

}