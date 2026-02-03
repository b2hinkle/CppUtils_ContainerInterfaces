// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CppUtils_ContainerInterfaces/ContainerOps.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerOps/SpecializedContainerOps_RawArray.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerOps/SpecializedContainerOps_StdArray.h>
#include <CppUtils_ContainerInterfaces/SpecializedContainerOps/SpecializedContainerOps_StdVector.h>

#include <vector>

// TODO: Right now this is somewhat of a sandbox. Make proper individual tests.
int main(int argc, char** argv)
{
    {
        std::vector<int> vec { 5, 6, 7, 8 };
        const std::size_t capacity = CppUtils::ContainerOps::GetCapacity{vec}.Do();
        const std::size_t size = CppUtils::ContainerOps::GetSize{vec}.Do();
        const bool isValidIndex = CppUtils::ContainerOps::IsValidIndex{vec}.Do(0);
        const bool isEmpty = CppUtils::ContainerOps::IsEmpty{vec}.Do();
        int& frontEl  = CppUtils::ContainerOps::GetFront{vec}.Do();
        int& BackEl   = CppUtils::ContainerOps::GetBack{vec}.Do();
        int& secondEl = CppUtils::ContainerOps::GetElement{vec}.Do(1);
    }
    
    {
        bool isSuccess = true;

        const int rawArr[] = { 0, 1, 2 };
        
        constexpr std::size_t capacity = CppUtils::ContainerOps::GetCapacity(rawArr).Do();
        constexpr std::size_t size = CppUtils::ContainerOps::GetSize(rawArr).Do();
        if (size != capacity) // Constant size arrays have same size and capacity.
        {
            isSuccess = false;
        }

        const bool isValidIndex = CppUtils::ContainerOps::IsValidIndex(rawArr).Do(1);

        if (CppUtils::ContainerOps::IsEmpty(rawArr).Do())
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement1 = CppUtils::ContainerOps::GetElement(rawArr).Do(0);
        if (gottenRawArrElement1 != 0)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement2 = CppUtils::ContainerOps::GetElement(rawArr).Do(1);
        if (gottenRawArrElement2 != 1)
        {
            isSuccess = false;
        }

        const int& gottenRawArrElement3 = CppUtils::ContainerOps::GetElement(rawArr).Do(2);
        if (gottenRawArrElement3 != 2)
        {
            isSuccess = false;
        }
    }

    {
        bool isSuccess = true;

        constexpr std::array<int, 3> stdArr = { 0, 1, 2 };

        const std::size_t capacity = CppUtils::ContainerOps::GetCapacity(stdArr).Do();
        constexpr int front = CppUtils::ContainerOps::GetFront(stdArr).Do();
        constexpr int back = CppUtils::ContainerOps::GetBack(stdArr).Do();
        const int& gottenStdArrElement = CppUtils::ContainerOps::GetElement(stdArr).Do(1);

        
        const std::array<int, 3> constArr = { 0, 1, 2 };
        const int& constEl = CppUtils::ContainerOps::GetElement(constArr).Do(1);

        const bool isValidIndex = CppUtils::ContainerOps::IsValidIndex(stdArr).Do(1);

        if (CppUtils::ContainerOps::IsEmpty(stdArr).Do())
        {
            isSuccess = false;
        }

        constexpr std::array<int, 0> stdArrZeroSize;
        if (!CppUtils::ContainerOps::IsEmpty(stdArrZeroSize).Do())
        {
            isSuccess = false;
        }
    }

    {
        static const std::array<int, 3> stdArr = { 0, 1, 2 };
        constexpr std::size_t capacity = CppUtils::ContainerOps::GetCapacity(stdArr).Do();

        int rawArr[] = { 0, 1, 2 };
        const int& gottenStdArrElement = CppUtils::ContainerOps::GetElement(rawArr).Do(1);

    }
}
