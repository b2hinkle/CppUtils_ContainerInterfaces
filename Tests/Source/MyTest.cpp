// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_ContainerInterfaces/ContainerInterfaces.h>
#include <CppUtils_ContainerInterfaces/ContainerImplementations/RawArrayImplementation.h>
#include <CppUtils_ContainerInterfaces/ContainerImplementations/StdArrayImplementation.h>

int main(int argc, char** argv)
{
    {
        bool isSuccess = true;
        
        const int rawArr[] = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetCapacity(rawArr);
        constexpr int size = CppUtils::GetSize(rawArr);
        if (size != capacity) // Constant size arrays have same size and capacity.
        {
            isSuccess = false;
        }

        const bool isValidIndex = CppUtils::IsValidIndex(rawArr, 1);

        if (CppUtils::ArrayIsEmpty(rawArr))
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement1 = CppUtils::ArrayGetElement(rawArr, 0);
        if (gottenRawArrElement1 != 0)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement2 = CppUtils::ArrayGetElement(rawArr, 1);
        if (gottenRawArrElement2 != 1)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement3 = CppUtils::ArrayGetElement(rawArr, 2);
        if (gottenRawArrElement3 != 2)
        {
            isSuccess = false;
        }
    }

    {
        bool isSuccess = true;

        constexpr std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetCapacity(stdArr);
        constexpr int front = CppUtils::ArrayGetFront(stdArr);
        constexpr int back = CppUtils::ArrayGetBack(stdArr);
        const int& gottenStdArrElement = CppUtils::ArrayGetElement(stdArr, 1);

        if (CppUtils::ArrayIsEmpty(stdArr))
        {
            isSuccess = false;
        }

        constexpr std::array<int, 0> stdArrZeroSize;
        if (!CppUtils::ArrayIsEmpty(stdArrZeroSize))
        {
            isSuccess = false;
        }
    }

    {
        static const std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetCapacity(stdArr);
        constexpr int rawArr[] = { 0, 1, 2 };
        constexpr int gottenStdArrElement = CppUtils::ArrayGetElement(rawArr, 1);

    }
}