#include <iostream>
#define N 100
#define MAX 1000000
using namespace std;

void Swap(int& num1, int& num2)
{
    int tmp = num1;
    num1 = num2;
    num2 = tmp;
}

int Partition(int* arr, int start, int end)
{
    int& pivot = arr[start];
    int i = start;
    for(int j=start+1; j<=end; j++)
    {
        if(arr[j] < pivot)
        {
            i++;
            Swap(arr[i], arr[j]);
        }
    }
    Swap(pivot, arr[i]);
    return i;
}

void QuickSort(int* arr, int start, int end)
{
    if(start < end)
    {
        int pivot = Partition(arr, start, end);
        QuickSort(arr, start, pivot-1);
        QuickSort(arr, pivot+1, end);
    }
}

int main(void)
{
    int arr[N];
    for(int i=0; i<N; i++)
        cin >> arr[i];
    
    QuickSort(arr, 0, N-1);

    for(int i=0; i<N; i++)
        cout << arr[i] << "\n";
    return 0;
}