// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <type_traits>
#include <CppUtils_ContainerInterfaces/ContainerOps_PrimaryTemplate.h>

/*
* Accessing a container op specialization. This removes cv and ref qualifiers in the process for compatability with the specializations.
* For this reason we go through here for the specialization types rather then directly.
*/
namespace CppUtils::ContainerOpUtils
{
    template <class T>
    struct GetSpecializationForContainerOp;

    template <template <class> class TOp, class TContainer>
    struct GetSpecializationForContainerOp<TOp<TContainer>>
    {
        using type = TOp<std::remove_cvref_t<TContainer>>;
    };

    template <class T>
    using GetSpecializationForContainerOp_t = typename GetSpecializationForContainerOp<T>::type;
}
