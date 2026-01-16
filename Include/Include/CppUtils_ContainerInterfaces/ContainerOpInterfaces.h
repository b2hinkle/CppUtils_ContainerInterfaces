// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerOpUtils.h>
#include <CppUtils_Misc/FunctionTraits.h>

namespace CppUtils
{
    /*
    * Base class for container op interfaces. Responsible for the shared needs of all container op interfaces to keep code consolidated.
    * TODO: Enforce that implementation's ctr takes in reference to container type.
    */
    template <template<class> class TContainerOp, class T>
    struct ContainerOpInterface_Base
    {
        // Removes cv and ref qualifiers for compatability with the container op specializations.
        using NeuteredT = std::remove_cvref_t<T>;

        // Our implementer which conforms to this interface.
        using Doer = TContainerOp<NeuteredT>;
    };

    template <class Doer>
    using DoFunctionTraitsForDoer = FunctionTraits<decltype(Doer::Do)>;
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
    struct ContainerOpInterface_GetCapacity :
        ContainerOp_GetCapacity<std::remove_cvref_t<T>>
    {
        using Base = ContainerOp_GetCapacity<std::remove_cvref_t<T>>;
        using Base::Base; // Inherit ctr(s) from our implementer.
        

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetCapacity(T&)
        -> ContainerOpInterface_GetCapacity<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetCapacity(const T (&)[Capacity])
        -> ContainerOpInterface_GetCapacity<const T (&)[Capacity]>;

    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetSize
        : ContainerOpInterface_Base<ContainerOp_GetSize, T>
    {
        using TBase = ContainerOpInterface_Base<ContainerOp_GetSize, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    /*
    * TODO: I've started on some static assertions for this interface. We need to both finish this one, and make enforcements for the rest of the ops.
    */
    template <class T>
    struct ContainerOpInterface_IsValidIndex
        : ContainerOpInterface_Base<ContainerOp_IsValidIndex, T>
    {
        using TBase = ContainerOpInterface_Base<ContainerOp_IsValidIndex, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        static_assert
        (
            requires { typename DoFunctionTraitsForDoer<Doer>; },
            "Container op must have a Do callable."
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
        
        //static_assert(sizeof(T) && std::is_invocable_v<decltype(Doer::Do), const NeuteredT&, IndexType>, "Op specialization must have a callable Do function with correct parameters.");
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_IsEmpty
        : ContainerOpInterface_Base<ContainerOp_IsEmpty, T>
    {
        using TBase = ContainerOpInterface_Base<ContainerOp_IsEmpty, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetFront
        : ContainerOpInterface_Base<ContainerOp_GetFront, T>
    {
        using TBase = ContainerOpInterface_Base<ContainerOp_GetFront, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetBack
        : ContainerOpInterface_Base<ContainerOp_GetBack, T>
    {
        using TBase = ContainerOpInterface_Base<ContainerOp_GetBack, T>;
        using typename TBase::Doer;
        using typename TBase::NeuteredT;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetElement
        : ContainerOp_GetElement<T, std::remove_cvref_t<T>>
    {        
        using Base = ContainerOp_GetElement<T, std::remove_cvref_t<T>>;
        using Base::Base; // Inherit ctr(s) from our implementer.

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetElement(T&)
        -> ContainerOpInterface_GetElement<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetElement(const T (&)[Capacity])
        -> ContainerOpInterface_GetElement<const T (&)[Capacity]>;

    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetElement(T (&)[Capacity])
        -> ContainerOpInterface_GetElement<T (&)[Capacity]>;
}
