// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <array>
#include <vector>
#include <cassert>
#include <CppUtils_ContainerInterfaces/ContainerOps.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerOps/SpecializedContainerOps_RawArray.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerOps/SpecializedContainerOps_StdArray.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerOps/SpecializedContainerOps_StdVector.h>

template <class ContainerType>
bool DoesPassOperationChecks(const ContainerType& container)
{
    assert(CppUtils::ContainerOps::GetSize{container}.Do() == 3); // These tests assume a container with 3 elements.

    {
        if (CppUtils::ContainerOps::GetCapacity{container}.Do() != 3) // [todo] Consider creating a common api for reserve so that we can guarentee this always passes. Non-dynamic arrays could potentially be a noop.
        {
            return false;
        }

        if (CppUtils::ContainerOps::IsEmpty(container).Do())
        {
            return false;
        }
        
        // Test valid bounds.
        if (CppUtils::ContainerOps::IsValidIndex{container}.Do(3) || !CppUtils::ContainerOps::IsValidIndex{container}.Do(1))
        {
            return false;
        }
    }

    // Test mutable access.....
    {   
        ContainerType& container_mutable = const_cast<ContainerType&>(container);

        CppUtils::ContainerOps::GetFront(container_mutable).Do() = 0;
        CppUtils::ContainerOps::GetElement(container_mutable).Do(1) = 1;
        CppUtils::ContainerOps::GetBack(container_mutable).Do() = 2;
    }

    // Test const access
    {
        if (CppUtils::ContainerOps::GetFront(container).Do() != 0)
        {
            return false;
        }

        if (CppUtils::ContainerOps::GetElement(container).Do(1) != 1)
        {
            return false;
        }

        if (CppUtils::ContainerOps::GetBack(container).Do() != 2)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    // Test all operations on all supported container types.
    int rawArr[]                { -1, -1, -1 };
    std::array<int, 3> stdArray { -1, -1, -1 };
    std::vector<int> stdVector  { -1, -1, -1 };

    if (!DoesPassOperationChecks(rawArr))
    {
        return -1;
    }

    if (!DoesPassOperationChecks(stdArray))
    {
        return -1;
    }

    if (!DoesPassOperationChecks(stdVector))
    {
        return -1;
    }

    return 0;
}
