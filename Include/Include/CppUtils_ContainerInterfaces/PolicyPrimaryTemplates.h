// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

/*
* All possible implementable container operations.
*/
namespace CppUtils
{

    template <class T>
    struct ContainerPolicyInterface_GetCapacity;
    
    template <class T>
    struct ContainerPolicyInterface_GetSize;
    
    template <class T>
    struct ContainerPolicyInterface_IsValidIndex;
    
    template <class T>
    struct ContainerPolicyInterface_IsEmpty;
    
    template <class T>
    struct ContainerPolicyInterface_GetFront;
    
    template <class T>
    struct ContainerPolicyInterface_GetBack;
    
    template <class T>
    struct ContainerPolicyInterface_GetElement;

}