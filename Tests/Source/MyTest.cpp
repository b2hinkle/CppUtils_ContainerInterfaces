// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_ContainerInterfaces/StaticArrayInterface.h>

int main(int argc, char** argv)
{
    {
        bool isSuccess = true;
        
        const int rawArr[] = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetCapacity(rawArr);
        constexpr int size = CppUtils::ArrayGetSizePolicy<decltype(rawArr)>::Do(rawArr);
        if (size != capacity) // Constant size arrays have same size and capacity.
        {
            isSuccess = false;
        }

        if (CppUtils::ArrayIsEmptyPolicy<decltype(rawArr)>::Do(rawArr))
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement1 = CppUtils::ArrayGetElementPolicy<decltype(rawArr)>::Do(rawArr, 0);
        if (gottenRawArrElement1 != 0)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement2 = CppUtils::ArrayGetElementPolicy<decltype(rawArr)>::Do(rawArr, 1);
        if (gottenRawArrElement2 != 1)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement3 = CppUtils::ArrayGetElementPolicy<decltype(rawArr)>::Do(rawArr, 2);
        if (gottenRawArrElement3 != 2)
        {
            isSuccess = false;
        }
    }

    {
        bool isSuccess = true;

        constexpr std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetCapacity(stdArr);
        constexpr int front = CppUtils::ArrayGetFrontPolicy<decltype(stdArr)>::Do(stdArr);
        constexpr int back = CppUtils::ArrayGetBackPolicy<decltype(stdArr)>::Do(stdArr);
        const int& gottenStdArrElement = CppUtils::ArrayGetElementPolicy<decltype(stdArr)>::Do(stdArr, 1);

        if (CppUtils::ArrayIsEmptyPolicy<decltype(stdArr)>::Do(stdArr))
        {
            isSuccess = false;
        }

        constexpr std::array<int, 0> stdArrZeroSize;
        if (!CppUtils::ArrayIsEmptyPolicy<decltype(stdArrZeroSize)>::Do(stdArrZeroSize))
        {
            isSuccess = false;
        }
    }

    {
        static const std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr int capacity = CppUtils::GetCapacity(stdArr);
        constexpr int rawArr[] = { 0, 1, 2 };
        constexpr int gottenStdArrElement = CppUtils::ArrayGetElementPolicy<decltype(rawArr)>::Do(rawArr, 1);

    }
}