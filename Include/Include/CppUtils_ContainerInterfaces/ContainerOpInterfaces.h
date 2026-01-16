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

    // TODO: I believe GCC will complain about ptr type to consteval member func. Look into potential workaround.
    template <class Op>
    using DoFunctionTraitsForOp = FunctionTraits<decltype(&Op::Do)>;
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
    struct ContainerOpInterface_GetCapacity
        : ContainerOp_GetCapacity<T, std::remove_cvref_t<T>>
    {
        using Op = ContainerOp_GetCapacity<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.
        

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
        : ContainerOp_GetSize<T, std::remove_cvref_t<T>>
    {
        using Op = ContainerOp_GetSize<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.
        

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetSize(T&)
        -> ContainerOpInterface_GetSize<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetSize(const T (&)[Capacity])
        -> ContainerOpInterface_GetSize<const T (&)[Capacity]>;

    /*
    * TODO: I've started on some static assertions for this interface. We need to both finish this one, and make enforcements for the rest of the ops.
    */
    template <class T>
    struct ContainerOpInterface_IsValidIndex
        : ContainerOp_IsValidIndex<T, std::remove_cvref_t<T>>
    {
        using Op = ContainerOp_IsValidIndex<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.

        static_assert
        (
            requires(Op& IsValidIndexOp)
            {
                { IsValidIndexOp.Do(1) } -> std::same_as<bool>;
            },
            "Container op must have Do function with an index parameter and bool return type."
        );
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_IsValidIndex(T&)
        -> ContainerOpInterface_IsValidIndex<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_IsValidIndex(const T (&)[Capacity])
        -> ContainerOpInterface_IsValidIndex<const T (&)[Capacity]>;
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_IsEmpty
        : ContainerOp_IsEmpty<T, std::remove_cvref_t<T>>
    {
        using Op = ContainerOp_IsEmpty<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_IsEmpty(T&)
        -> ContainerOpInterface_IsEmpty<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_IsEmpty(const T (&)[Capacity])
        -> ContainerOpInterface_IsEmpty<const T (&)[Capacity]>;
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetFront
        : ContainerOp_GetFront<T, std::remove_cvref_t<T>>
    {
        using Op = ContainerOp_GetFront<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetFront(T&)
        -> ContainerOpInterface_GetFront<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetFront(const T (&)[Capacity])
        -> ContainerOpInterface_GetFront<const T (&)[Capacity]>;

    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetFront(T (&)[Capacity])
        -> ContainerOpInterface_GetFront<T (&)[Capacity]>;

    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetBack
        : ContainerOp_GetBack<T, std::remove_cvref_t<T>>
    {
        using Op = ContainerOp_GetBack<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetBack(T&)
        -> ContainerOpInterface_GetBack<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetBack(const T (&)[Capacity])
        -> ContainerOpInterface_GetBack<const T (&)[Capacity]>;

    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetBack(T (&)[Capacity])
        -> ContainerOpInterface_GetBack<T (&)[Capacity]>;
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetElement
        : ContainerOp_GetElement<T, std::remove_cvref_t<T>>
    {        
        using Op = ContainerOp_GetElement<T, std::remove_cvref_t<T>>;
        using Op::Op; // Inherit ctr(s) from our implementer.

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
