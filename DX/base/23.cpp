#include <iostream>
#include <cstring>
#define MAXV 50010
#define MAXE 200010
using namespace std;

typedef struct Edge{
    int s;
    int e;
    int cost;
}edge;

int V, E, res, edgeCnt, heapSize;
edge e;
int parent[MAXV];
edge edgeList[MAXE];
edge heap[MAXE];

void heapPush(edge e)
{
    heap[heapSize] = e;

    int current = heapSize;
    while(current > 1 && heap[current].cost < heap[current >> 1].cost)
    {
        edge tmp = heap[current];
        heap[current] = heap[current >> 1];
        heap[current >> 1] = tmp;

        current = current >> 1;
    }

    ++heapSize;
}
edge heapPop()
{
    edge pop = heap[1];
    heap[1] = heap[--heapSize];

    int current = 1;
    while((current << 1) < heapSize)
    {
        int child;

        if((current << 1) + 1 == heapSize)
            child = current << 1;
        else child = heap[current << 1].cost < heap[(current << 1) + 1].cost ? current << 1 : (current << 1) + 1;

        if(heap[current].cost < heap[child].cost)
            break;

        edge tmp = heap[current];
        heap[current] = heap[child];
        heap[child] = tmp;

        current = child;
    }

    return pop;
}

int getParent(int x)
{
    if(parent[x] == x) return x;
    else return parent[x] = getParent(parent[x]);
}
bool isUnited(int x, int y)
{
    x = getParent(x);
    y = getParent(y);
    if(x == y) return true;
    else return false;
}
void unite(int x, int y)
{
    x = getParent(x);
    y = getParent(y);
    if(x < y) parent[y] = x;
    else parent[x] = y;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("23_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> V >> E;
		
        edgeCnt = 1;
        heapSize = 1;
        res = 0;

        for(int i=1; i<=V; ++i)
            parent[i] = i;
        
        for(int i=0; i<E; ++i)
        {
            cin >> edgeList[edgeCnt].s >> edgeList[edgeCnt].e >> edgeList[edgeCnt].cost;
            heapPush(edgeList[edgeCnt]);
            edgeCnt++;
        }

        for(int i=0; i<E; ++i)
        {
            e = heapPop();
            
            if(!isUnited(e.s, e.e))
            {
                res += e.cost;
                unite(e.s, e.e);
            }
        }

        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}