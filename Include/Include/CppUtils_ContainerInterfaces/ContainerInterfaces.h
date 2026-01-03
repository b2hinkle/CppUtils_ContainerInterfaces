// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <utility>
#include <CppUtils_ContainerInterfaces/PolicyPrimaryTemplates.h>

/*
* Static interfaces for container operations which callers go through for generically calling on a container's operation implementation.
* TODO: Make a non-consteval version to account for dynamically sized arrays.
* TODO: Potentally also make a pass by value overload, especially helpful for static arrays.
*/
namespace CppUtils
{
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetCapacity
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>; // TODO: Use mixin approach for inheriting this using to avoid dup code.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_GetCapacity<NeuteredT>;
    };

    /*
    * Gets the capacity.
    */
    template <class T>
    consteval decltype(auto) GetContainerCapacity(T&& container)
    {
        return ContainerPolicyInterface_GetCapacity<T>::Doer::Do(std::forward<T>(container));
    }







    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetSize
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_GetSize<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) GetContainerSize(T&& container)
    {
        return ContainerPolicyInterface_GetSize<T>::Doer::Do(std::forward<T>(container));
    }








    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsValidIndex
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_IsValidIndex<NeuteredT>;
    };
    
    // TODO: GENERIC TYPE FOR INDEX!
    template <class T>
    consteval decltype(auto) IsValidIndexForContainer(T&& container, int index)
    {
        return ContainerPolicyInterface_IsValidIndex<T>::Doer::Do(std::forward<T>(container), index);
    }











    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsEmpty
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_IsEmpty<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) IsContainerEmpty(T&& container)
    {
        return ContainerPolicyInterface_IsEmpty<T>::Doer::Do(std::forward<T>(container));
    }







    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetFront
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_GetFront<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) GetContainerFront(T&& container)
    {
        return ContainerPolicyInterface_GetFront<T>::Doer::Do(std::forward<T>(container));
    }







    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetBack
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_GetBack<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) GetContainerBack(T&& container)
    {
        return ContainerPolicyInterface_GetBack<T>::Doer::Do(std::forward<T>(container));
    }








    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetElement
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyInterface_GetElement<NeuteredT>;
    };
    
    // TODO: GENERIC TYPE FOR INDEX!
    template <class T>
    constexpr decltype(auto) GetContainerElement(T&& container, int index)
    {
        return ContainerPolicyInterface_GetElement<T>::Doer::Do(std::forward<T>(container), index);
    }
}