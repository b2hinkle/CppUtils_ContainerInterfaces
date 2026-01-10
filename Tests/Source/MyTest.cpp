// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_ContainerInterfaces/ContainerOps.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerPolicies/SpecializedContainerPolicies_RawArray.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerPolicies/SpecializedContainerPolicies_StdArray.h>

int main(int argc, char** argv)
{
    {
        bool isSuccess = true;
        
        const int rawArr[] = { 0, 1, 2 };
        constexpr int capacity = CppUtils::ContainerOps::GetCapacity<decltype(rawArr)>::Do(rawArr);
        constexpr int size = CppUtils::ContainerOps::GetSize<decltype(rawArr)>::Do(rawArr);
        if (size != capacity) // Constant size arrays have same size and capacity.
        {
            isSuccess = false;
        }

        const bool isValidIndex = CppUtils::ContainerOps::IsValidIndex(rawArr, 1);

        if (CppUtils::ContainerOps::IsEmpty(rawArr))
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement1 = CppUtils::ContainerOps::GetElement(rawArr, 0);
        if (gottenRawArrElement1 != 0)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement2 = CppUtils::ContainerOps::GetElement(rawArr, 1);
        if (gottenRawArrElement2 != 1)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement3 = CppUtils::ContainerOps::GetElement(rawArr, 2);
        if (gottenRawArrElement3 != 2)
        {
            isSuccess = false;
        }
    }

    {
        bool isSuccess = true;

        constexpr std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::ContainerOps::GetCapacity<decltype(stdArr)>::Do(stdArr);
        constexpr int front = CppUtils::ContainerOps::GetFront(stdArr);
        constexpr int back = CppUtils::ContainerOps::GetBack(stdArr);
        const int& gottenStdArrElement = CppUtils::ContainerOps::GetElement(stdArr, 1);

        const bool isValidIndex = CppUtils::ContainerOps::IsValidIndex(stdArr, 1);

        if (CppUtils::ContainerOps::IsEmpty(stdArr))
        {
            isSuccess = false;
        }

        constexpr std::array<int, 0> stdArrZeroSize;
        if (!CppUtils::ContainerOps::IsEmpty(stdArrZeroSize))
        {
            isSuccess = false;
        }
    }

    {
        static const std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::ContainerOps::GetCapacity<decltype(stdArr)>::Do(stdArr);
        constexpr int rawArr[] = { 0, 1, 2 };
        constexpr int gottenStdArrElement = CppUtils::ContainerOps::GetElement(rawArr, 1);

    }
}
