// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_ContainerInterfaces/ContainerInterfaces.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerPolicies/SpecializedContainerPolicies_RawArray.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerPolicies/SpecializedContainerPolicies_StdArray.h>

int main(int argc, char** argv)
{
    {
        bool isSuccess = true;
        
        const int rawArr[] = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetContainerCapacity(rawArr);
        constexpr int size = CppUtils::GetContainerSize(rawArr);
        if (size != capacity) // Constant size arrays have same size and capacity.
        {
            isSuccess = false;
        }

        const bool isValidIndex = CppUtils::IsValidIndexForContainer(rawArr, 1);

        if (CppUtils::IsContainerEmpty(rawArr))
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement1 = CppUtils::GetContainerElement(rawArr, 0);
        if (gottenRawArrElement1 != 0)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement2 = CppUtils::GetContainerElement(rawArr, 1);
        if (gottenRawArrElement2 != 1)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement3 = CppUtils::GetContainerElement(rawArr, 2);
        if (gottenRawArrElement3 != 2)
        {
            isSuccess = false;
        }
    }

    {
        bool isSuccess = true;

        constexpr std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetContainerCapacity(stdArr);
        constexpr int front = CppUtils::GetContainerFront(stdArr);
        constexpr int back = CppUtils::GetContainerBack(stdArr);
        const int& gottenStdArrElement = CppUtils::GetContainerElement(stdArr, 1);

        if (CppUtils::IsContainerEmpty(stdArr))
        {
            isSuccess = false;
        }

        constexpr std::array<int, 0> stdArrZeroSize;
        if (!CppUtils::IsContainerEmpty(stdArrZeroSize))
        {
            isSuccess = false;
        }
    }

    {
        static const std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetContainerCapacity(stdArr);
        constexpr int rawArr[] = { 0, 1, 2 };
        constexpr int gottenStdArrElement = CppUtils::GetContainerElement(rawArr, 1);

    }
}