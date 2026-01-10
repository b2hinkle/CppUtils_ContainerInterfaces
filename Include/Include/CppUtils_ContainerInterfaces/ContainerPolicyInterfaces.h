// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerPolicyUtils.h>
#include <CppUtils_Misc/FunctionTraits.h>

namespace CppUtils
{
    /*
    * Base class for container policy interfaces. Responsible for the shared needs of all container policy interfaces to keep code consolidated.
    */
    template <template<class> class TContainerPolicy, class T>
    struct ContainerPolicyInterface_Base
    {
        // Removes cv and ref qualifiers for compatability with the container policy specializations.
        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to this interface.
        using Doer = TContainerPolicy<NeuteredT>;
    };

    template <class Doer>
    using DoFunctionTraitsForDoer = FunctionPointerTraits<decltype(&Doer::Do)>;
}

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
        : ContainerPolicy_GetCapacity<std::remove_cvref_t<T>>
    {
        using Base = ContainerPolicy_GetCapacity<std::remove_cvref_t<T>>;
        using Base::Base;
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <typename T, std::size_t Capacity>
    ContainerPolicyInterface_GetCapacity(const std::array<T, Capacity>&)
        -> ContainerPolicyInterface_GetCapacity<std::array<T, Capacity>>;

    template <typename T, std::size_t Capacity>
    ContainerPolicyInterface_GetCapacity(const T (&)[Capacity])
        -> ContainerPolicyInterface_GetCapacity<T[Capacity]>;

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetSize
        : ContainerPolicyInterface_Base<ContainerPolicy_GetSize, T>
    {
        using TBase = ContainerPolicyInterface_Base<ContainerPolicy_GetSize, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    /*
    * TODO: I've started on some static assertions for this interface. We need to both finish this one, and make enforcements for the rest of the policies.
    */
    template <class T>
    struct ContainerPolicyInterface_IsValidIndex
        : ContainerPolicyInterface_Base<ContainerPolicy_IsValidIndex, T>
    {
        using TBase = ContainerPolicyInterface_Base<ContainerPolicy_IsValidIndex, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        static_assert
        (
            requires { typename DoFunctionTraitsForDoer<Doer>; },
            "Container policy must have a Do callable."
        );
        using DoFunctionTraits = DoFunctionTraitsForDoer<Doer>;

        static_assert
        (
            std::tuple_size_v<typename DoFunctionTraits::ArgsTuple> == 2,
            "Do callable must have 2 parameters."
        );

        static_assert
        (
            std::is_same_v<typename DoFunctionTraits::ClassType, void>,
            "Do callable must be static."
        );

        using TFirstParam  = std::tuple_element_t<0, typename DoFunctionTraits::ArgsTuple>;
        using TSecondParam = std::tuple_element_t<1, typename DoFunctionTraits::ArgsTuple>;
        
        //static_assert(sizeof(T) && std::is_invocable_v<decltype(Doer::Do), const NeuteredT&, IndexType>, "Policy specialization must have a callable Do function with correct parameters.");
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_IsEmpty
        : ContainerPolicyInterface_Base<ContainerPolicy_IsEmpty, T>
    {
        using TBase = ContainerPolicyInterface_Base<ContainerPolicy_IsEmpty, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetFront
        : ContainerPolicyInterface_Base<ContainerPolicy_GetFront, T>
    {
        using TBase = ContainerPolicyInterface_Base<ContainerPolicy_GetFront, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetBack
        : ContainerPolicyInterface_Base<ContainerPolicy_GetBack, T>
    {
        using TBase = ContainerPolicyInterface_Base<ContainerPolicy_GetBack, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerPolicyInterface_GetElement
        : ContainerPolicyInterface_Base<ContainerPolicy_GetElement, T>
    {
        using TBase = ContainerPolicyInterface_Base<ContainerPolicy_GetElement, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };
}
