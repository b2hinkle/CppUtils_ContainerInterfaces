// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerOpUtils.h>
#include <CppUtils_Misc/FunctionTraits.h>

namespace CppUtils
{
    /*
    * Base level interface for container ops. Container op interfaces must derive from this base for base level enforcements, as well as the container op itself.
    */
    template <template<class> class ContainerOp_Generic, class T>
    struct ContainerOpInterfaceBase
        : ContainerOp_Generic<T>
    {
        using Op = ContainerOp_Generic<T>;
    protected: // Protected ctrs to keep this type abstract. Only non-base interfaces can be instantiated.
        using Op::Op;

        static_assert(std::is_lvalue_reference_v<T>, "Interfaces require that the container type is an lvalue reference." );

        // NOTE: As of now, this is all we can do for static enforcements on the operation specializations' constructor. We don't get as much power as with function traits since constructors aren't
        //       addressable and don't have a type. We will enforce what we can here. Cpp 26 could potentially help with this due to compile time reflection.
        static_assert(std::is_constructible_v<Op, T>,       "Constructor of operation specialization must accept the container type in order to allow for the class template argument deduction.");
        static_assert(!std::is_default_constructible_v<Op>, "Constructor of operation specialization can't take in nothing, otherwise we get no class template argument deduction.");

        static consteval decltype(auto) GetDoFuncTraitsObj()
        {
            static_assert
            (
                requires { typename FunctionPtrTraits<&Op::Do>; },
                "Operation specialization must contain a `Do` function."
            );

            return FunctionPtrTraits<&Op::Do>{};
        }
        using DoFuncTraits = decltype(GetDoFuncTraitsObj());
    };
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
        : ContainerOpInterfaceBase<ContainerOp_GetCapacity, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetCapacity, T>;
        using InterfaceBase::InterfaceBase;

        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        static_assert
        (
            std::is_integral_v<typename DoFuncTraits::ReturnType>,
            "GetCapacity op's `Do` function must return an integral type."
        );

        static_assert
        (
            DoFuncTraits::GetArgsCount() == 0,
            "GetCapacity op's `Do` function must take no parameters."
        );
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetCapacity(T&)
        -> ContainerOpInterface_GetCapacity<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetCapacity(T (&)[Capacity])
        -> ContainerOpInterface_GetCapacity<T (&)[Capacity]>;

    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetSize
        : ContainerOpInterfaceBase<ContainerOp_GetSize, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetSize, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        static_assert
        (
            std::is_integral_v<typename DoFuncTraits::ReturnType>,
            "GetSize op's `Do` function must return an integral type."
        );

        static_assert
        (
            DoFuncTraits::GetArgsCount() == 0,
            "GetSize op's `Do` function must take no parameters."
        );
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetSize(T&)
        -> ContainerOpInterface_GetSize<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetSize(T (&)[Capacity])
        -> ContainerOpInterface_GetSize<T (&)[Capacity]>;

    /*
    * TODO: I've started on some static assertions for this interface. We need to both finish this one, and make enforcements for the rest of the ops.
    */
    template <class T>
    struct ContainerOpInterface_IsValidIndex
        : ContainerOpInterfaceBase<ContainerOp_IsValidIndex, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_IsValidIndex, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        static_assert
        (
            std::is_same_v<bool, typename DoFuncTraits::ReturnType>,
            "IsValidIndex op's `Do` function must return a boolean."
        );

        static_assert
        (
            DoFuncTraits::GetArgsCount() == 1,
            "IsValidIndex op's `Do` function must take exactly one parameter."
        );
        using FirstParam = std::tuple_element_t<0, typename DoFuncTraits::ArgsTuple>;

        static_assert
        (
            std::is_integral_v<FirstParam>,
            "IsValidIndex op's `Do` function must take in an integral parameter for the index."
        );
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_IsValidIndex(T&)
        -> ContainerOpInterface_IsValidIndex<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_IsValidIndex(T (&)[Capacity])
        -> ContainerOpInterface_IsValidIndex<T (&)[Capacity]>;
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_IsEmpty
        : ContainerOpInterfaceBase<ContainerOp_IsEmpty, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_IsEmpty, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        static_assert
        (
            std::is_same_v<bool, typename DoFuncTraits::ReturnType>,
            "IsEmpty op's `Do` function must return a boolean."
        );

        static_assert
        (
            DoFuncTraits::GetArgsCount() == 0,
            "IsEmpty op's `Do` function must take no parameters."
        );
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_IsEmpty(T&)
        -> ContainerOpInterface_IsEmpty<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_IsEmpty(T (&)[Capacity])
        -> ContainerOpInterface_IsEmpty<T (&)[Capacity]>;
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetFront
        : ContainerOpInterfaceBase<ContainerOp_GetFront, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetFront, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

#if 0
        static_assert
        (
            requires(Op op)
            {
                { op.Do() } -> std::same_as<typename T::value_type>; // TODO: Require correct return type.
            },
            "Op must have `Do` function with no parameters and element return type."
        );
#endif
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetFront(T&)
        -> ContainerOpInterface_GetFront<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetFront(T (&)[Capacity])
        -> ContainerOpInterface_GetFront<T (&)[Capacity]>;

    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetBack
        : ContainerOpInterfaceBase<ContainerOp_GetBack, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetBack, T>;
        using InterfaceBase::InterfaceBase;

        using Op = ContainerOp_GetBack<T>;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetBack(T&)
        -> ContainerOpInterface_GetBack<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetBack(T (&)[Capacity])
        -> ContainerOpInterface_GetBack<T (&)[Capacity]>;
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetElement
        : ContainerOpInterfaceBase<ContainerOp_GetElement, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetElement, T>;
        using InterfaceBase::InterfaceBase;

        using Op = ContainerOp_GetElement<T>;

        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.
    };

    // Deduction guide for more convenient user api.
    template <class T>
    ContainerOpInterface_GetElement(T&)
        -> ContainerOpInterface_GetElement<T&>;
        
    // Specific deduction guide to prevent decay of raw arrays types into ptrs. Specialization requires array type so we deduce it as such.
    template <class T, std::size_t Capacity>
    ContainerOpInterface_GetElement(T (&)[Capacity])
        -> ContainerOpInterface_GetElement<T (&)[Capacity]>;
}
