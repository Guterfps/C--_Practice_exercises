
#include <iostream>

long long FindNumInInfArr(int *arr, int num);
long long BinarySearch(int *arr, long long start, long long end, int num);


int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 
                19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    
    std::cout << "Find number in inf array: ";
    (0 == FindNumInInfArr(arr, 1)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (29 == FindNumInInfArr(arr, 30)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (-1 == FindNumInInfArr(arr, 0)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (24 == FindNumInInfArr(arr, 25)) ? 
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    int arr2[] = { 3, 5, 7, 9, 10, 90, 100, 130, 140, 160, 170};
    std::cout << "Find number in inf array: ";
    (-1 == FindNumInInfArr(arr2, 25)) ?
    std::cout << "SUCCESS ✅, " : std::cout << "FAIL ❌, ";
    (4 == FindNumInInfArr(arr2, 10)) ?
    std::cout << "SUCCESS ✅\n" : std::cout << "FAIL ❌\n";

    return 0;
}

long long FindNumInInfArr(int *arr, int num)
{
    long long start = 0;
    long long end = 1;

    while (num > arr[end])
    {
        std::size_t temp = end + 1;
        end += (end - start + 1) * 2;
        start = temp;
    }

    return BinarySearch(arr, start, end, num);
}

long long BinarySearch(int *arr, long long start, long long end, int num)
{
    while (start <= end)
    {
        std::size_t mid = start + (end - start) / 2;
        if (num > arr[mid])
        {
            start = mid + 1;
        }
        else if (num < arr[mid])
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}