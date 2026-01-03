// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <array>
#include <type_traits>

namespace CppUtils
{
#if 0
    template <class T>
    struct IsStaticArrayApi
    {
        enum { value = false }
    };

    template <class T, std::size_t Capacity>
    struct IsStaticArrayApi<T[Capacity]>
    {
        enum { value = true }
    };
#endif

#if 0
    template <class T>
    struct StaticArrayInterface
    {
        static_assert<sizeof(T) && false, "No">;
    }
#endif

    template <class T>
    struct ArrayGetCapacityPolicy_Impl;

    /*
    *
    */
    template <class T>
    struct ArrayGetCapacityPolicy_Interface
    {
        //static_assert(sizeof(T) && std::); // TODO: I want to make enforcements on the doer. It's the whole purpose of this interface type.

        using NeuteredT = std::remove_cvref_t<T>; // TODO: Possibly use mixin approach for inheriting this using to avoid dup code.

        // Our implementer which conforms to our enforcements.
        using Doer = ArrayGetCapacityPolicy_Impl<NeuteredT>;
    };

    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayGetCapacityPolicy_Impl<T[Capacity]>
    {
        static consteval std::size_t Do(const T (&)[Capacity])
        {
            return Capacity;
        }
        
        static consteval std::size_t Do(T (&)[Capacity])
        {
            return Capacity;
        }
    };

    // std::array.    
    template <class T, std::size_t Capacity>
    struct ArrayGetCapacityPolicy_Impl<std::array<T, Capacity>>
    {
        static consteval std::size_t Do(const std::array<T, Capacity>&)
        {
            return Capacity;
        }
        
        static consteval std::size_t Do(std::array<T, Capacity>&)
        {
            return Capacity;
        }
    };

    /*
    * Gets the capacity.
    * TODO: Make a non-consteval version to account for dynamically sized arrays.
    * TODO: Potentally also make a pass by value overload, especially helpful for static arrays.
    */
    template <class T>
    consteval decltype(auto) GetCapacity(T&& container)
    {
        return ArrayGetCapacityPolicy_Interface<T>::Doer::Do(std::forward<T>(container));
    }





    
    
    
    
    template <class T>
    struct ArrayGetSizePolicy_Impl;
    
    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayGetSizePolicy_Impl<T[Capacity]>
    {
        static consteval std::size_t Do(const T (&)[Capacity])
        {
            return Capacity;
        }
    };
    
    // std::array.
    template <class T, std::size_t Capacity>
    struct ArrayGetSizePolicy_Impl<std::array<T, Capacity>>
    {
        static consteval std::size_t Do(const std::array<T, Capacity>&)
        {
            return Capacity;
        }
    };

    template <class T>
    using ArrayGetSizePolicy = ArrayGetSizePolicy_Impl<std::remove_cvref_t<T>>;
    
    template <class T>
    consteval decltype(auto) GetSize(T&& container)
    {
        return ArrayGetSizePolicy<T>::Do(std::forward<T>(container));
    }
    

    
    
    
    
    template <class T>
    struct ArrayIsValidIndexPolicy_Impl;
    
    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayIsValidIndexPolicy_Impl<T[Capacity]>
    {
        static consteval bool Do(const T (&)[Capacity], const std::size_t index)
        {
            return index >= 0
                && index < Capacity;
        }
    };
    
    // std::array.
    template <class T, std::size_t Capacity>
    struct ArrayIsValidIndexPolicy_Impl<std::array<T, Capacity>>
    {
        static consteval bool Do(const std::array<T, Capacity>&, const std::size_t index)
        {
            return index >= 0
                && index < Capacity;
        }
    };

    template <class T>
    using ArrayIsValidIndexPolicy = ArrayIsValidIndexPolicy_Impl<std::remove_cvref_t<T>>;
    
    
    

    
    
    
    
    template <class T>
    struct ArrayIsEmptyPolicy_Impl;
    
    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayIsEmptyPolicy_Impl<T[Capacity]>
    {
        static consteval bool Do(const T (&)[Capacity])
        {
            // NOTE: It is not possible for raw arrays to exist with no size/capacity.
            return false;
        }
    };
    
    // std::array.
    template <class T, std::size_t Capacity>
    struct ArrayIsEmptyPolicy_Impl<std::array<T, Capacity>>
    {
        static consteval bool Do(const std::array<T, Capacity>&)
        {
            return Capacity == 0;
        }
    };

    template <class T>
    using ArrayIsEmptyPolicy = ArrayIsEmptyPolicy_Impl<std::remove_cvref_t<T>>;
    
    
    

    
    
    
    
    template <class T>
    struct ArrayGetFrontPolicy_Impl;
    
    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayGetFrontPolicy_Impl<T[Capacity]>
    {
        static constexpr const T& Do(const T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[0];
        }
        
        static constexpr T& Do(T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[0];
        }
    };
    
    // std::array.
    template <class T, std::size_t Capacity>
    struct ArrayGetFrontPolicy_Impl<std::array<T, Capacity>>
    {
        static constexpr const T& Do(const std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.front();
        }
        
        static constexpr T& Do(std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.front();
        }
    };

    template <class T>
    using ArrayGetFrontPolicy = ArrayGetFrontPolicy_Impl<std::remove_cvref_t<T>>;
    
    
    

    
    
    
    
    template <class T>
    struct ArrayGetBackPolicy_Impl;
    
    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayGetBackPolicy_Impl<T[Capacity]>
    {
        static constexpr const T& Do(const T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[Capacity - 1];
        }
        
        static constexpr T& Do(T (&arr)[Capacity])
        {
            static_assert(Capacity > 0, "Assert will never hit, as it is not possible for raw arrays to exist with no size/capacity.");
            return arr[Capacity - 1];
        }
    };
    
    // std::array.
    template <class T, std::size_t Capacity>
    struct ArrayGetBackPolicy_Impl<std::array<T, Capacity>>
    {
        static constexpr const T& Do(const std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.back();
        }
        
        static constexpr T& Do(std::array<T, Capacity>& arr)
        {
            static_assert(Capacity > 0, "Calling front or back on zero-sized std::array would be undefined.");
            return arr.back();
        }
    };

    template <class T>
    using ArrayGetBackPolicy = ArrayGetBackPolicy_Impl<std::remove_cvref_t<T>>;
    
    
    

    
    
    
    
    template <class T>
    struct ArrayGetElementPolicy_Impl;
    
    // Raw array.
    template <class T, std::size_t Capacity>
    struct ArrayGetElementPolicy_Impl<T[Capacity]>
    {
        static constexpr const T& Do(const T (&arr)[Capacity], const std::size_t index)
        {
            return arr[index];
        }

        static constexpr T& Do(T (&arr)[Capacity], const std::size_t index)
        {
            return arr[index];
        }
    };
    
    // std::array.
    template <class T, std::size_t Capacity>
    struct ArrayGetElementPolicy_Impl<std::array<T, Capacity>>
    {
        static constexpr const T& Do(const std::array<T, Capacity>& arr, const std::size_t index)
        {
            return arr[index];
        }

        static constexpr T& Do(std::array<T, Capacity>& arr, const std::size_t index)
        {
            return arr[index];
        }
    };

    template <class T>
    using ArrayGetElementPolicy = ArrayGetElementPolicy_Impl<std::remove_cvref_t<T>>;
    
}