// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerOpUtils.h>
#include <CppUtils/Misc/FunctionTraits.h>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils/Misc/ContainerElementType.h>
#include <CppUtils/Misc/Static_Execute.h>

/*
* Boilerplate deduction guides for container op interfaces. These allow for simple user api via CTAD, where the passed in container is enough
* to resolve the class template argument.
* E.g. ContainerOpInterface(container) instead of ContainerOpInterface<decltype(container)>(container)
*/
#define CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface)                                                                             \
    template <class T>                                                                                                                                   \
    ContainerOpInterface(T&)                                                                                                                             \
        -> ContainerOpInterface<T&>;                                                                                                                     \
                                                                                                                                                         \
    /* Specific deduction guide to preserve raw arrays types before they decay into ptrs. Specialization requires array type so we deduce it as such. */ \
    template <class T, std::size_t Capacity>                                                                                                             \
    ContainerOpInterface(T (&)[Capacity])                                                                                                                \
        -> ContainerOpInterface<T (&)[Capacity]>;


/*
* Due to the nature of having many container interfaces, there are very common static assertions which we need in many different interfaces.
* We avoid the duplicate code by creating consteval function wrappers which we static execute (via `CPPUTILS_STATIC_EXECUTE` utility).
*
* [techdebt] Generalizing these static asserts for reuse between different ops sadly makes error messaging less clear, since we can't provide the op name in the message.
*            This is a tradeoff we have to make for now to avoid code duplication. In the future with non-string-literal static_assert messages (C++23), this can be improved, and
*            compile time reflection (C++26) can help even more.
*/
namespace CppUtils
{
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
    consteval void AssertDoFunc_IsFirstParamIntegral()
    {
        using FirstParam = std::tuple_element_t<0, typename TDoFuncTraits::ArgsTuple>;
        static_assert
        (
            std::is_integral_v<FirstParam>,
            "Operation's `Do` function must have integral type as its first parameter."
        );
    }
}
    
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

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsIntegralReturn<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetCapacity)

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

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsIntegralReturn<DoFuncTraits>())
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetSize)

    /*
    * 
    */
    template <class T>
    struct ContainerOpInterface_IsValidIndex
        : ContainerOpInterfaceBase<ContainerOp_IsValidIndex, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_IsValidIndex, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsBoolReturn<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsFirstParamIntegral<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasExactlyOneParam<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_IsValidIndex)
    
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

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsBoolReturn<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_IsEmpty)
    
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

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsContainerElementReturn<T, DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasNoParams<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetFront)

    /*
    *
    */
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

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetBack)
    
    /*
    *
    */
    template <class T>
    struct ContainerOpInterface_GetElement
        : ContainerOpInterfaceBase<ContainerOp_GetElement, T>
    {
        using InterfaceBase = ContainerOpInterfaceBase<ContainerOp_GetElement, T>;
        using InterfaceBase::InterfaceBase;
        
        using DoFuncTraits = InterfaceBase::DoFuncTraits;

        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsContainerElementReturn<T, DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_IsFirstParamIntegral<DoFuncTraits>());
        CPPUTILS_STATIC_EXECUTE(AssertDoFunc_HasExactlyOneParam<DoFuncTraits>());
    };

    CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface_GetElement)
}
