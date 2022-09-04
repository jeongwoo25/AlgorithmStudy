#include <iostream>
#define N 10
#define MAX 1000001
using namespace std;

void Merge(int* arr, int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int* left = new int[n1 + 1];
    int* right = new int[n2 + 1];
    
    for(int i=0; i<n1; i++) left[i] = arr[start + i];
    for(int i=0; i<n2; i++) right[i] = arr[mid + 1 + i];
    left[n1] = right[n2] = MAX;

    int i=0, j=0;
    for(int k=start; k<=end; k++)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
    }

    delete[] left;
    delete[] right;
}

void MergeSort(int* arr, int start, int end)    // linkedlist 구현시 가장 효율적
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(arr, start, mid);
        MergeSort(arr, mid + 1, end);
        Merge(arr, start, mid ,end);
    }
}

int main(void)
{
    int arr[N];
    for(int i=0; i<N; i++)
        cin >> arr[i];
    
    MergeSort(arr, 0, N-1);
    for(int i=0; i<N; i++)
        cout << arr[i] << "\n";
    return 0;
}