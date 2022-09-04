#include <iostream>
using namespace std;

int N, K, T;
long long total, sum;
int arr[100010];

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K >> T;

    for(int i=0; i<N; ++i) {
        cin >> arr[i];
        total += arr[i];
    }

    bool ans = false;

    if(total == 0) ans = true;
    else if(total % K == 0) {
        mergeSort(arr, 0, N-1);
        
        long long numBucket = total / K;
        for(int i=0; i<numBucket; ++i)
            sum += arr[N-1-i];

        if(total - sum <= T) ans = true;
    }

    if(ans) cout << "YES";
    else cout << "NO";

    return 0;
}