// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

/*
* All possible implementable container operations.
*/
namespace CppUtils
{

    template <class T>
    struct ArrayGetCapacityPolicy_Impl;
    
    template <class T>
    struct ArrayGetSizePolicy_Impl;
    
    template <class T>
    struct ArrayIsValidIndexPolicy_Impl;
    
    template <class T>
    struct ArrayIsEmptyPolicy_Impl;
    
    template <class T>
    struct ArrayGetFrontPolicy_Impl;
    
    template <class T>
    struct ArrayGetBackPolicy_Impl;
    
    template <class T>
    struct ArrayGetElementPolicy_Impl;

}