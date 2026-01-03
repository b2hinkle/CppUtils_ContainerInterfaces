// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <utility>
#include <CppUtils_ContainerInterfaces/PolicyPrimaryTemplates.h>

/*
* Static interfaces for container operations which callers go through for generically calling on a container's operation implementation.
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

        using NeuteredT = std::remove_cvref_t<T>; // TODO: Possibly use mixin approach for inheriting this using to avoid dup code.

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetCapacityPolicy_Impl<NeuteredT>;
    };

    /*
    * Gets the capacity.
    * TODO: Make a non-consteval version to account for dynamically sized arrays.
    * TODO: Potentally also make a pass by value overload, especially helpful for static arrays.
    */
    template <class T>
    consteval decltype(auto) GetCapacity(T&& container)
    {
        return ArrayGetCapacityPolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }







    
    template <class T>
    using ArrayGetSizePolicy = ArrayGetSizePolicy_Impl<std::remove_cvref_t<T>>;
    
    template <class T>
    consteval decltype(auto) GetSize(T&& container)
    {
        return ArrayGetSizePolicy<T>::Do(std::forward<T>(container));
    }





    template <class T>
    using ArrayIsValidIndexPolicy = ArrayIsValidIndexPolicy_Impl<std::remove_cvref_t<T>>;



    
    template <class T>
    using ArrayIsEmptyPolicy = ArrayIsEmptyPolicy_Impl<std::remove_cvref_t<T>>;






    template <class T>
    using ArrayGetFrontPolicy = ArrayGetFrontPolicy_Impl<std::remove_cvref_t<T>>;






    template <class T>
    using ArrayGetBackPolicy = ArrayGetBackPolicy_Impl<std::remove_cvref_t<T>>;






    template <class T>
    using ArrayGetElementPolicy = ArrayGetElementPolicy_Impl<std::remove_cvref_t<T>>;
}