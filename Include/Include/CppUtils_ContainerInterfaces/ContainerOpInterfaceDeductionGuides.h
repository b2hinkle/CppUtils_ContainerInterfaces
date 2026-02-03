// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

/*
 * Boilerplate CTAD deduction guides for container operation interfaces.
 *
 * These guides enable a clean user-facing API where passing a container
 * instance is sufficient to deduce the interface type:
 *
 *     ContainerOpInterface{container}
 *
 * instead of the more verbose:
 *
 *     ContainerOpInterface<decltype(container)>{container}
 *
 * Most container ops only observe the container. For these cases, we want
 * deduction to add `const` to avoid discarded-qualifier errors when the
 * container ref is stored.
 *
 * A separate deduction guide is provided for raw arrays to prevent array
 * decay into pointers during deduction. Several container operations
 * require the full array type (including its extent), so the array form
 * is preserved explicitly.
 */
#define CPPUTILS_DECLARE_OP_INTERFACE_DEDUCTION_GUIDES(ContainerOpInterface, ExtraQualifiers) \
    template <class T>                                                                        \
    ContainerOpInterface(T&)                                                                  \
        -> ContainerOpInterface<ExtraQualifiers T&>;                                          \
                                                                                              \
                                                                                              \
    template <class T, std::size_t Capacity>                                                  \
    ContainerOpInterface(T (&)[Capacity])                                                     \
        -> ContainerOpInterface<ExtraQualifiers T (&)[Capacity]>;
