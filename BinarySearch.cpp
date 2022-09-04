#include <iostream>
using namespace std;

int binarySearch(int* arr, int start, int end, int target)
{
    while(start <= end)
    {
        int mid = (start + end) / 2;

        if(arr[mid] == target)
            return mid;
        else if(arr[mid] > target)
            end = mid - 1;
        else start = mid + 1;
    }

    return -1;
}

int main(void)
{
    int arr[4] = {0, 1, 2, 3};

    int ans = binarySearch(arr, 0, 3, 2);
    cout << ans << endl;
    return 0;
}