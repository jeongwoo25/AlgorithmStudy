#include <iostream>
#define MAXN 100010
using namespace std;

int N;
long long cnt;
int arr[MAXN];
int buf[MAXN];

void merge(int start, int mid, int end)
{
    int i=start, j=mid+1, k=0;

    while(i<=mid && j<=end)
    {
        if(arr[i] < arr[j])
            buf[k++] = arr[i++];
        if(arr[i] > arr[j])
        {
            buf[k++] = arr[j++];
            cnt += mid - i + 1;
        }
    }

    while(i <= mid) buf[k++] = arr[i++];
    while(j <= end) buf[k++] = arr[j++];

    for(int i=start, k=0; i<=end; i++, k++)
        arr[i] = buf[k];
}

void mergeSort(int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(start, mid);
        mergeSort(mid+1, end);
        merge(start, mid, end);
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("18_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cnt = 0;

        cin >> N;
		
        for(int i=0; i<N; ++i)
            cin >> arr[i];

        mergeSort(0, N-1);

        cout << "#" << test_case << " " << cnt << "\n";
	}

	return 0;
}