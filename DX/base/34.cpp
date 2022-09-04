#include <iostream>
#define MAXN 200100
#define MOD 20171109
#define MAXHEAP 1
#define MINHEAP 2
using namespace std;

struct Heap{
    int heapSize;
    int heap[MAXN];

    void heapPush(int value, int type)
    {
        heap[heapSize] = value;

        int current = heapSize;

        if(type == MAXHEAP)
        {
            while(current > 1 && heap[current >> 1] < heap[current])
            {
                int tmp = heap[current];
                heap[current] = heap[current >> 1];
                heap[current >> 1] = tmp;
                current = current >> 1;
            }
        }
        else if(type == MINHEAP)
        {
            while(current > 1 && heap[current >> 1] > heap[current])
            {
                int tmp = heap[current];
                heap[current] = heap[current >> 1];
                heap[current >> 1] = tmp;
                current = current >> 1;
            }
        }

        ++heapSize;
    }
    int heapPop(int type)
    {
        int pop = heap[1];
        heap[1] = heap[--heapSize];

        int current = 1;
        if(type == MAXHEAP)
        {
            while((current << 1) < heapSize)
            {
                int child;

                if((current << 1) + 1 == heapSize)
                    child = current << 1;
                else child = heap[current << 1] > heap[(current << 1) + 1] ? current << 1 : (current << 1) + 1;

                if(heap[current] > heap[child])
                    break;

                int tmp = heap[current];
                heap[current] = heap[child];
                heap[child] = tmp;

                current = child;
            }
        }
        else if(type == MINHEAP)
        {
            while((current << 1) < heapSize)
            {
                int child;

                if((current << 1) + 1 == heapSize)
                    child = current << 1;
                else child = heap[current << 1] < heap[(current << 1) + 1] ? current << 1 : (current << 1) + 1;

                if(heap[current] < heap[child])
                    break;

                int tmp = heap[current];
                heap[current] = heap[child];
                heap[child] = tmp;

                current = child;
            }
        }

        return pop;
    }
};

Heap maxHeap;
Heap minHeap;
int mid, res, N, n1, n2;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("34_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        res = 0;
        maxHeap.heapSize = 1;
        minHeap.heapSize = 1;

        cin >> N >> mid;
        
        for(int i=0; i<N; ++i)
        {
            cin >> n1 >> n2;

            mid > n1 ? maxHeap.heapPush(n1, MAXHEAP) : minHeap.heapPush(n1, MINHEAP);
            mid > n2 ? maxHeap.heapPush(n2, MAXHEAP) : minHeap.heapPush(n2, MINHEAP);
            
            if(maxHeap.heapSize > minHeap.heapSize)
            {
                minHeap.heapPush(mid, MINHEAP);
                mid = maxHeap.heapPop(MAXHEAP);
            }
            else if(maxHeap.heapSize < minHeap.heapSize)
            {
                maxHeap.heapPush(mid, MAXHEAP);
                mid = minHeap.heapPop(MINHEAP);
            }
            
            res = (res + mid) % MOD;
        }
        
        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}