// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerPolicies_PrimaryTemplate.h>

/*
* Accessing a container policy specialization. This removes cv and ref qualifiers in the process for compatability with the specializations.
* For this reason we go through here for the specialization types rather then directly.
*/
namespace CppUtils::ContainerPolicyUtils
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
