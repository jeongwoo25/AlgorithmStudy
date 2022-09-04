#include <iostream>
#define N 10
using namespace std;

void quickSort(int* arr, int start, int end)
{
    if(start < end)
    {
        int pivot = arr[start];

        int i=start+1, j=end;
        while(i<=j)
        {
            while(arr[i] <= pivot) i++;
            while(arr[j] > pivot) j--;

            if(i<=j)
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }

        int tmp = pivot;
        arr[start] = arr[j];
        arr[j] = tmp;

        quickSort(arr, start, j-1);
        quickSort(arr, j+1, end);
    }

}

int main(void)
{
    int arr[N];
    for(int i=0; i<N; i++)
        cin >> arr[i];
    
    quickSort(arr, 0, N-1);

    for(int i=0; i<N; i++)
        cout << arr[i] << "\n";
    return 0;
}