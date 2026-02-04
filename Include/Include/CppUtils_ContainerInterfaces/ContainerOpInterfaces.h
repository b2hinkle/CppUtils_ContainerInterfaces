// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>
#include <CppUtils/Misc/Static_Execute.h>
#include <CppUtils/Misc/Tag_IsPrimaryTemplate.h>
#include <CppUtils_ContainerInterfaces/ContainerOpInterfaceDeductionGuides.h>
#include <CppUtils_ContainerInterfaces/ContainerOpInterfaceStaticAsserts.h>

/*
* Base level interface for container ops. Container op interfaces must derive from this
* base for base level enforcements, as well as the container op itself.
*/
namespace CppUtils::ContainerOps::Detail
{
    template <template<class> class ContainerOp_Generic, class T>
        requires (!std::is_base_of_v<Tag_IsPrimaryTemplate, ContainerOp_Generic<T>>)
    struct ContainerOpInterfaceBase
        : ContainerOp_Generic<T>
    {
        using Op = ContainerOp_Generic<T>;
    protected: // Protected ctrs to keep this type abstract. Only non-base interfaces can be instantiated.
        using Op::Op;

        static_assert(std::is_lvalue_reference_v<T>, "Interfaces require that the container type is an lvalue reference." );

        /*
        * We require all operation specializations to be constructible from a
        * container type lvalue reference.
        * 
        * Rationale:
        *  3) Provides the operation implementation with full access to the container
        *     object (including cv-qualification and aliasing semantics).
        *  1) Enforces a consistent and predictable user API.
        *  2) Enables CTAD via deduction guides, resulting in a cleaner user-facing API.
        *  4) Access to the container at no runtime cost: Storing a pointer (the lvalue reference)
        *     has no observable side effects and may be freely optimized away by the compiler under
        *     the standard as-if rule.
        */
        static_assert(std::is_constructible_v<Op, TypeProbe_LValueRef<std::remove_cvref_t<T>>>,       "Ctr of operation specialization must take 1 parameter, which accepts lvalue reference to the container type.");
        static_assert(!std::is_default_constructible_v<Op>, "Operation specialization can't have default ctr. We enforce a consistant user api which only accepts lvalue ref to user's container type.");

        static_assert(!std::is_convertible_v<T, Op>, "Constructor must be explicit. We have this constraint to eliminate potental implicit conversion complexity that may be unexpected.");


        static consteval decltype(auto) GetDoFuncTraitsTypeAsObj()
        {
            static_assert
            (
                requires { typename FunctionPtrTraits<&Op::Do>; },
                "Operation specialization must contain a `Do` function."
            );

            return FunctionPtrTraits<&Op::Do>{};
        }
        using DoFuncTraits = decltype(GetDoFuncTraitsTypeAsObj());
    };
}

/*
* Static interfaces for container operations which callers go through for generically
* calling on a container's operation implementation.
*/
namespace CppUtils::ContainerOps::Detail
{
    template <class T>
    struct ContainerOpInterface_GetCapacity
        : ContainerOpInterfaceBase<ContainerOp_GetCapacity, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetCapacity, T>;
        using InterfaceBase::InterfaceBase;

        using Op = InterfaceBase::Op;
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsCtrContainerTypeParamConst<Op, T>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsIntegralReturn<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetCapacity, const)

    template <class T>
    struct ContainerOpInterface_GetSize
        : ContainerOpInterfaceBase<ContainerOp_GetSize, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetSize, T>;
        using InterfaceBase::InterfaceBase;
        
        using Op = InterfaceBase::Op;
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsCtrContainerTypeParamConst<Op, T>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsIntegralReturn<DoFuncTraits>())
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetSize, const)

    template <class T>
    struct ContainerOpInterface_IsValidIndex
        : ContainerOpInterfaceBase<ContainerOp_IsValidIndex, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_IsValidIndex, T>;
        using InterfaceBase::InterfaceBase;
        
        using Op = InterfaceBase::Op;
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsCtrContainerTypeParamConst<Op, T>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsBoolReturn<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasIntegralFirstParam<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasExactlyOneParam<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_IsValidIndex, const)
    
    template <class T>
    struct ContainerOpInterface_IsEmpty
        : ContainerOpInterfaceBase<ContainerOp_IsEmpty, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_IsEmpty, T>;
        using InterfaceBase::InterfaceBase;
        
        using Op = InterfaceBase::Op;
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsCtrContainerTypeParamConst<Op, T>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsBoolReturn<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_IsEmpty, const)
    
    template <class T>
    struct ContainerOpInterface_GetFront
        : ContainerOpInterfaceBase<ContainerOp_GetFront, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetFront, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsContainerElementReturn<T, DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetFront, )

    template <class T>
    struct ContainerOpInterface_GetBack
        : ContainerOpInterfaceBase<ContainerOp_GetBack, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetBack, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsContainerElementReturn<T, DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetBack, )
    
    template <class T>
    struct ContainerOpInterface_GetElement
        : ContainerOpInterfaceBase<ContainerOp_GetElement, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetElement, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsContainerElementReturn<T, DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasIntegralFirstParam<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasExactlyOneParam<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetElement, )
}
