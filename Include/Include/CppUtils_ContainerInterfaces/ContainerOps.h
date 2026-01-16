// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <utility>
#include <CppUtils_ContainerInterfaces/ContainerOpInterfaces.h>

/*
* TODO: Make a non-consteval version to account for dynamically sized arrays.
* TODO: Potentally also make a pass by value overload, especially helpful for static arrays.
*/
namespace CppUtils::ContainerOps
{
    /*
    * Gets the capacity.
    */
    template <class ContainerType>
    using GetCapacity = ContainerOpInterface_GetCapacity<ContainerType>;

    template <class ContainerType>
    using GetSize = ContainerOpInterface_GetSize<ContainerType>::Doer;

   
    template <class T>
    consteval decltype(auto) IsValidIndex(T&& container, typename ContainerOpInterface_IsValidIndex<T>::TSecondParam index)
    {
        return ContainerOpInterface_IsValidIndex<T>::Doer::Do(std::forward<T>(container), index);
    }


    template <class T>
    consteval decltype(auto) IsEmpty(T&& container)
    {
        return ContainerOpInterface_IsEmpty<T>::Doer::Do(std::forward<T>(container));
    }


    template <class T>
    consteval decltype(auto) GetFront(T&& container)
    {
        return ContainerOpInterface_GetFront<T>::Doer::Do(std::forward<T>(container));
    }


    template <class T>
    consteval decltype(auto) GetBack(T&& container)
    {
        return ContainerOpInterface_GetBack<T>::Doer::Do(std::forward<T>(container));
    }

    /*
    * 
    */
    template <class ContainerType>
    using GetElement = ContainerOpInterface_GetElement<ContainerType>;
}
