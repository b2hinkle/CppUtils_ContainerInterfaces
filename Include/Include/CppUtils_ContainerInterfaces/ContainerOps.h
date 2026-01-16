// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <utility>
#include <CppUtils_ContainerInterfaces/ContainerOpInterfaces.h>

/*
*
*/
namespace CppUtils::ContainerOps
{
    /*
    * Gets the capacity.
    */
    template <class ContainerType>
    using GetCapacity = ContainerOpInterface_GetCapacity<ContainerType>;

    /*
    * 
    */
    template <class ContainerType>
    using GetSize = ContainerOpInterface_GetSize<ContainerType>;

    /*
    * 
    */
    template <class ContainerType>
    using IsValidIndex = ContainerOpInterface_IsValidIndex<ContainerType>;

    /*
    * 
    */
    template <class ContainerType>
    using IsEmpty = ContainerOpInterface_IsEmpty<ContainerType>;

    /*
    * 
    */
    template <class ContainerType>
    using GetFront = ContainerOpInterface_GetFront<ContainerType>;

    /*
    * 
    */
    template <class ContainerType>
    using GetBack = ContainerOpInterface_GetBack<ContainerType>;

    /*
    * 
    */
    template <class ContainerType>
    using GetElement = ContainerOpInterface_GetElement<ContainerType>;
}
