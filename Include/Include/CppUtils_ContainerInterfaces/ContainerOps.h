// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <utility>
#include <CppUtils_ContainerInterfaces/ContainerPolicyInterfaces.h>

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
    using GetCapacity = ContainerPolicyInterface_GetCapacity<ContainerType>;

    template <class ContainerType>
    using GetSize = ContainerPolicyInterface_GetSize<ContainerType>::Doer;

   
    template <class T>
    consteval decltype(auto) IsValidIndex(T&& container, typename ContainerPolicyInterface_IsValidIndex<T>::TSecondParam index)
    {
        return ContainerPolicyInterface_IsValidIndex<T>::Doer::Do(std::forward<T>(container), index);
    }


    template <class T>
    consteval decltype(auto) IsEmpty(T&& container)
    {
        return ContainerPolicyInterface_IsEmpty<T>::Doer::Do(std::forward<T>(container));
    }


    template <class T>
    consteval decltype(auto) GetFront(T&& container)
    {
        return ContainerPolicyInterface_GetFront<T>::Doer::Do(std::forward<T>(container));
    }


    template <class T>
    consteval decltype(auto) GetBack(T&& container)
    {
        return ContainerPolicyInterface_GetBack<T>::Doer::Do(std::forward<T>(container));
    }

    /*
    * 
    */
    template <class ContainerType>
    using GetElement = ContainerPolicyInterface_GetElement<ContainerType>;
}
