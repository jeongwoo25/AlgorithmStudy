#include <iostream>
#define MAXN 100001
using namespace std;

int heap[MAXN];
int heapSize;

void heapPush(int key)
{
    heap[heapSize] = key;

    int current = heapSize;
    while(current > 1 && heap[current >> 1] < heap[current])
    {
        int tmp = heap[current];
        heap[current] = heap[current >> 1];
        heap[current >> 1] = tmp;
        current = current >> 1;
    }

    ++heapSize;
}

int heapPop()
{
    if(heapSize == 1)
        return -1;

    int pop = heap[1];
    heap[1] = heap[--heapSize];

    int current = 1;
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

    return pop;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("32_input.txt", "r", stdin);
	cin >> T;
	
    int N;
    int op, key;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        heapSize = 1;

        cin >> N;

        cout << "#" << test_case << " ";

        for(int i=0; i<N; ++i)
        {
            cin >> op;
            
            if(op == 1)
            {
                cin >> key;
                heapPush(key);
            }
            else cout << heapPop() << " ";
        }

        cout << "\n";
	}

	return 0;
}