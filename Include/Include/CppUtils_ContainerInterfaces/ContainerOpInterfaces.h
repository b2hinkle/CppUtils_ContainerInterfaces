// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>
#include <CppUtils/Misc/FunctionTraits.h>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils/Misc/ContainerElementType.h>
#include <CppUtils/Misc/Static_Execute.h>
#include <CppUtils/Misc/TypeProbes.h>
#include <CppUtils/Misc/Tag_IsPrimaryTemplate.h>
#include <CppUtils_ContainerInterfaces/ContainerOpInterfaceDeductionGuides.h>

/*
* Due to the nature of having many container interfaces, there are very common static assertions which we need in many different interfaces.
* We avoid the duplicate code by creating consteval function wrappers which we static execute (via `CPPUTILS_STATIC_EXECUTE` utility).
*
* [techdebt] Generalizing these static asserts for reuse between different ops sadly makes error messaging less clear, since we can't provide the op name in the message.
*            This is a tradeoff we have to make for now to avoid code duplication. In the future with non-string-literal static_assert messages (C++23), this can be improved, and
*            compile time reflection (C++26) can help even more.
*/
namespace CppUtils::ContainerOps::Detail
{
    template <class TOp, class T>
    consteval void AssertDoFunc_IsCtrContainerTypeParamConst()
    {
        static_assert
        (
            std::is_constructible_v<TOp, TypeProbe_ConstRef<std::remove_cvref_t<T>>>,
            "Container type for operation's ctr must be const."
        );
    }

    template <class TDoFuncTraits>
    consteval void AssertDoFunc_IsIntegralReturn()
    {
        static_assert
        (
            std::is_integral_v<typename TDoFuncTraits::ReturnType>,
            "Operation's `Do` function must return an integral type."
        );
    }

    template <class TDoFuncTraits>
    consteval void AssertDoFunc_IsBoolReturn()
    {
        static_assert
        (
            std::is_same_v<bool, typename TDoFuncTraits::ReturnType>,
            "Operation's `Do` function must return a boolean."
        );
    }

    /*
    * Enforce proper returning of container element.
    */
    template <class TContainer, class TDoFuncTraits>
    consteval void AssertDoFunc_IsContainerElementReturn()
    {
        using ElementType = ContainerElementType_t<std::remove_reference_t<TContainer>>;

        // Enforce value type correctness between the container element type and the return type.
        {
            static_assert
            (
                std::is_same_v
                <
                    std::remove_cvref_t<typename TDoFuncTraits::ReturnType>,
                    std::remove_cvref_t<ElementType>
                >,
                "Operation's `Do` function return value type must be the same as the container element's value type."
            );
        }

        // Enforce returning a reference to the container element. Caller may still grab a copy from this reference if needed.
        static_assert
        (
            std::is_lvalue_reference_v<typename TDoFuncTraits::ReturnType>,
            "Operation's `Do` function return type must be an lvalue reference."
        );

        // Enforce const correctness between the container and container element type with the return type.
        {
            static_assert
            (
                IsConstAfterRemovingRef<typename TDoFuncTraits::ReturnType>() == IsConstAfterRemovingRef<TContainer>(),
                "Operation's `Do` function return type must be same constness as the container type."
            );
    
            static_assert
            (
                !IsConstAfterRemovingRef<ElementType>() ||
                IsConstAfterRemovingRef<typename TDoFuncTraits::ReturnType>(),
                R"(Operation's `Do` function return type must obey the constness of the element type. This assert simply evaluates to, "if the element type is const, the return type must also be const".)"
            );
        }
    }

    template <class TDoFuncTraits>
    consteval void AssertDoFunc_HasNoParams()
    {
        static_assert
        (
            TDoFuncTraits::GetArgsCount() == 0,
            "Operation's `Do` function must have no parameters."
        );
    }

    template <class TDoFuncTraits>
    consteval void AssertDoFunc_HasExactlyOneParam()
    {
        static_assert
        (
            TDoFuncTraits::GetArgsCount() == 1,
            "Operation's `Do` function must have exactly one parameter."
        );
    }

    template <class TDoFuncTraits>
    consteval void AssertDoFunc_HasIntegralFirstParam()
    {
        using FirstParam = std::tuple_element_t<0, typename TDoFuncTraits::ArgsTuple>;
        static_assert
        (
            std::is_integral_v<FirstParam>,
            "Operation's `Do` function must have integral type as its first parameter."
        );
    }
}

namespace CppUtils::ContainerOps::Detail
{
    /*
    * Base level interface for container ops. Container op interfaces must derive from this base for base level enforcements, as well as the container op itself.
    */
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
        * We enforce an lvalue reference to the container type as the ctr. This is for multiple reasons. It enforces the consistency of our convenient user api (nice class template argument deduction).
        *    It also enforces zero copies of container data, and sets us up for the standard compiler optimization ____, which elides the ptr copy for the reference member.
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
* Static interfaces for container operations which callers go through for generically calling on a container's operation implementation.
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
