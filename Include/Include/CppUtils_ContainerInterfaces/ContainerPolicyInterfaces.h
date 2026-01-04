// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <utility>
#include <CppUtils_ContainerInterfaces/ContainerPolicies_PrimaryTemplate.h>

/*
* Accessing a container policy specialization. This removes cv and ref qualifiers in the process for compatability with the specializations.
* For this reason we go through here for the specialization types rather then directly.
*/
namespace CppUtils
{
    template <class T>
    struct GetSpecializationForContainerPolicy;

    template <template <class> class TPolicy, class TContainer>
    struct GetSpecializationForContainerPolicy<TPolicy<TContainer>>
    {
        using type = TPolicy<std::remove_cvref_t<TContainer>>;
    };

    template <class T>
    using GetSpecializationForContainerPolicy_t = typename GetSpecializationForContainerPolicy<T>::type;
}

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
        
        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_GetCapacity<T>>;
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetSize
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_GetSize<T>>;
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsValidIndex
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_IsValidIndex<T>>;
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsEmpty
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_IsEmpty<T>>;
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetFront
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_GetFront<T>>;
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetBack
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_GetBack<T>>;
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetElement
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = GetSpecializationForContainerPolicy_t<ContainerPolicy_GetElement<T>>;
    };
}