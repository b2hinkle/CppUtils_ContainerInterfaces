// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CppUtils_ContainerInterfaces/ContainerPolicyUtils.h>

/*
* Static interfaces for container operations which callers go through for generically calling on a container's operation implementation.
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
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_GetCapacity<T>>;
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetSize
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_GetSize<T>>;
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsValidIndex
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_IsValidIndex<T>>;
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsEmpty
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_IsEmpty<T>>;
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetFront
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_GetFront<T>>;
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetBack
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_GetBack<T>>;
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetElement
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        // Our implementer which conforms to our enforcements.
        using Doer = ContainerPolicyUtils::GetSpecializationForContainerPolicy_t<ContainerPolicy_GetElement<T>>;
    };
}