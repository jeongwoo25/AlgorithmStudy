#include <iostream>
#define N 10
using namespace std;

void merge(int* arr, int start, int mid, int end)
{
    int i=start, j=mid+1, k=0;

    int* buf = new int[end-start+1];

    while(i<=mid && j<=end)
        buf[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    while(i<=mid)
        buf[k++] = arr[i++];
    while(j<=end)
        buf[k++] = arr[j++];

    for(int i=start, k=0; i<=end; i++, k++)
        arr[i] = buf[k];

    delete[] buf;
}

void mergeSort(int* arr, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end)/2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

int main(void)
{
    int arr[N];
    for(int i=0; i<N; i++)
        cin >> arr[i];
    
    mergeSort(arr, 0, N-1);
    for(int i=0; i<N; i++)
        cout << arr[i] << "\n";
    return 0;
}