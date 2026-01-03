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
    struct ArrayGetCapacityPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>; // TODO: Use mixin approach for inheriting this using to avoid dup code.

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetCapacityPolicy_Impl<NeuteredT>;
    };

    /*
    * Gets the capacity.
    */
    template <class T>
    consteval decltype(auto) GetCapacity(T&& container)
    {
        return ArrayGetCapacityPolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }







    /*
    *
    */
    template <class T>
    struct ArrayGetSizePolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetSizePolicy_Impl<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) GetSize(T&& container)
    {
        return ArrayGetSizePolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }








    /*
    *
    */
    template <class T>
    struct ArrayIsValidIndexPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayIsValidIndexPolicy_Impl<NeuteredT>;
    };
    
    // TODO: GENERIC TYPE FOR INDEX!
    template <class T>
    consteval decltype(auto) IsValidIndex(T&& container, int index)
    {
        return ArrayIsValidIndexPolicy_Interface<T>::Doer::Do(std::forward<T>(container), index);
    }











    /*
    *
    */
    template <class T>
    struct ArrayIsEmptyPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayIsEmptyPolicy_Impl<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) ArrayIsEmpty(T&& container)
    {
        return ArrayIsEmptyPolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }







    /*
    *
    */
    template <class T>
    struct ArrayGetFrontPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetFrontPolicy_Impl<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) ArrayGetFront(T&& container)
    {
        return ArrayGetFrontPolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }







    /*
    *
    */
    template <class T>
    struct ArrayGetBackPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetBackPolicy_Impl<NeuteredT>;
    };
    
    template <class T>
    consteval decltype(auto) ArrayGetBack(T&& container)
    {
        return ArrayGetBackPolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }








    /*
    *
    */
    template <class T>
    struct ArrayGetElementPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetElementPolicy_Impl<NeuteredT>;
    };
    
    // TODO: GENERIC TYPE FOR INDEX!
    template <class T>
    constexpr decltype(auto) ArrayGetElement(T&& container, int index)
    {
        return ArrayGetElementPolicy_Interface<T>::Doer::Do(std::forward<T>(container), index);
    }
}