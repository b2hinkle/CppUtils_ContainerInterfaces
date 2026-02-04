// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils/Misc/TypeTraits.h>
#include <CppUtils/Misc/FunctionTraits.h>
#include <CppUtils/Misc/TypeProbes.h>
#include <CppUtils/Misc/ContainerElementType.h>

/*
* Due to the nature of having many container operation interfaces, there are very common static assertions which we need in many different interfaces.
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
