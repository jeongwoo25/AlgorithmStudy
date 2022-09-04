#include <iostream>
#define MAXN 105
#define INF 99999
using namespace std;

struct pos{
    int row;
    int col;
    int dist;
};

char c;
int N;
int map[MAXN][MAXN];
int minDist[MAXN][MAXN];

int heapSize;
pos heap[MAXN * MAXN];
pos start;

void init()
{
    for(int i=1; i<=N; ++i)
    {
        for(int j=1; j<=N; ++j)
        {
            cin >> c;
            map[i][j] = c - '0';
            minDist[i][j] = INF;
        }
    }

    heapSize = 1;

    start.row = start.col = 1; start.dist = 0;
    heap[heapSize++] = start;
}

void heapPush(pos k)
{
    heap[heapSize] = k;

    int current = heapSize;
    while(current > 1 && heap[current >> 1].dist > heap[current].dist)
    {
        pos tmp = heap[current];
        heap[current] = heap[current >> 1];
        heap[current >> 1] = tmp;

        current  = current >> 1;
    }

    ++heapSize;
}

pos heapPop()
{
    pos pop = heap[1];
    heap[1] = heap[--heapSize];

    int current = 1;
    while((current << 1) < heapSize)
    {
        int child;

        if((current << 1) + 1 == heapSize)
            child = current << 1;
        else child = heap[current << 1].dist < heap[(current << 1) + 1].dist ? current << 1 : (current << 1) + 1;

        if(heap[child].dist > heap[current].dist)
            break;

        pos tmp = heap[child];
        heap[child] = heap[current];
        heap[current] = tmp;

        current = child; 
    }

    return pop;
}

void solve()
{
    while(heapSize > 1)
    {
        pos pop = heapPop();

        if(pop.dist >= minDist[pop.row][pop.col])
            continue;

        minDist[pop.row][pop.col] = pop.dist;

        pos up = pop, down = pop, left = pop, right = pop;
        --up.row, ++down.row; --left.col; ++right.col;

        if(up.row >= 0)
        {
            up.dist = pop.dist + map[up.row][up.col];
            heapPush(up);
        }

        if(down.row <= N)
        {
            down.dist = pop.dist + map[down.row][down.col];
            heapPush(down);
        }

        if(left.col >= 0)
        {
            left.dist = pop.dist + map[left.row][left.col];
            heapPush(left);
        }

        if(right.col <= N)
        {
            right.dist = pop.dist + map[right.row][right.col];
            heapPush(right);
        }
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("33_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;

        init();

        solve();

        cout << "#" << test_case << " " << minDist[N][N] << "\n";
	}

	return 0;
}