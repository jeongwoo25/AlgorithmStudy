#include <iostream>
#define MAXN 11
using namespace std;

struct Node{
	int left;
	int cnt;
};

int N, K, heapSize, res;
int A[MAXN];
Node heap[100001];

void heapPush(int _left, int _cnt)
{
	heap[heapSize].left = _left;
	heap[heapSize].cnt = _cnt;

	int current = heapSize;
	while(current > 1)
	{
		if(heap[current].cnt > heap[current >> 1].cnt)
			break;
		else if(heap[current].cnt == heap[current >> 1].cnt)
			if(heap[current].left > heap[current >> 1].left)
				break;

		Node tmp = heap[current];
		heap[current] = heap[current >> 1];
		heap[current >> 1] = tmp;

		current = current >> 1;
	}

	++heapSize;
}

Node heapPop()
{
	Node pop = heap[1];
	heap[1] = heap[--heapSize];

	int current = 1;
	while((current << 1) < heapSize)
	{
		int child;

		if((current << 1) + 1 == heapSize)
			child = current << 1;
		else
		{
			if(heap[current << 1].cnt == heap[(current << 1) + 1].cnt)
				child = heap[current << 1].left < heap[(current << 1) + 1].left ? current << 1 : (current << 1) + 1;
			else child = heap[current << 1].cnt < heap[(current << 1) + 1].cnt ? current << 1 : (current << 1) + 1;
		}

		if(heap[current].cnt < heap[child].cnt)
			break;
		else if(heap[current].cnt == heap[child].cnt)
			if(heap[current].left < heap[child].left)
				break;

		Node tmp = heap[current];
		heap[current] = heap[child];
		heap[child] = tmp;

		current = child;
	}

	return pop;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("35_input.txt", "r", stdin);
	cin >> T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		heapSize = 1;

		cin >> N;

		for(int i=1; i<=N; ++i)
			cin >> A[i];

		cin >> K;
		
		heapPush(K, 0);

		while(heapSize > 1)
		{
			Node pop = heapPop();

			if(pop.left == 0)
			{
				res = pop.cnt;
				break;
			}
			
			bool isPush = false;
			for(int i=1; i<=N; ++i)
			{
				if(pop.left >= A[i])
				{
					heapPush(pop.left / A[i], pop.cnt + (pop.left % A[i]));
					isPush = true;
				}
			}

			if(!isPush) heapPush(0, pop.cnt + pop.left);
		}

		cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}