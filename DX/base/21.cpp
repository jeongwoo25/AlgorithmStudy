#include <iostream>
#include <vector>
#define MAXN 100010
using namespace std;

struct Node{
    int num;
};

int N;
int nodeNum;
Node nodeList[MAXN];

int seqCnt;
Node seq[MAXN];
int parentNum[MAXN][25];
int depth[MAXN];

vector<int> childList[MAXN];
int childCnt[MAXN];

Node queue[MAXN];
int front, rear;
long long res;

void BFS()
{
    front = -1; rear = -1; seqCnt = 1;

    rear = rear + 1;
    queue[rear] = nodeList[1];
    
    while(front != rear)
    {
        front = front + 1;
        Node pop = queue[front];
        
        seq[seqCnt++] = pop;

        for(int i=0; i<childCnt[pop.num]; ++i)
        {
            rear = rear + 1;
            queue[rear] = nodeList[childList[pop.num].at(i)];
        }
    }
}

void lca(int x, int y)
{
    if(depth[x] < depth[y])
    {
        int tmp = x;
        x = y;
        y = tmp;
    }

    int diff = depth[x] - depth[y];

    for(int i=0; diff!=0; ++i)
    {
        if(diff & 1)
        {
            x = parentNum[x][i];
            res += (1 << i);
        }
            
        diff = diff >> 1;
    }

    if(x != y)
    {
        for(int i=20; i>=0; --i)
        {
            if(parentNum[x][i] != -1 && parentNum[x][i] != parentNum[y][i])
            {
                x = parentNum[x][i];
                y = parentNum[y][i];
                res += (1 << (i+1));
            }
        }

        res += 2;
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("21_input.txt", "r", stdin);
	cin >> T;
    
    int parent;
    Node* ptr;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;

        nodeNum = 1;
        res = 0;

        nodeList[nodeNum].num = nodeNum;
        depth[nodeNum] = 1;
        parentNum[nodeNum][0] = -1;

        ++nodeNum;

        for(int i=0; i<N-1; ++i)
        {
            cin >> parent;

            nodeList[nodeNum].num = nodeNum;
            depth[nodeNum] = depth[parent] + 1;
            parentNum[nodeNum][0] = parent;

            ptr = &nodeList[parent];
            
            childList[parent].push_back(nodeNum);
            ++childCnt[parent];

            ++nodeNum;
        }
        
        BFS();

        for(int j=1; j<21; ++j)
            for(int i=1; i<=N; ++i)
                parentNum[i][j] = parentNum[parentNum[i][j-1]][j-1];

        for(int i=1; i<N; ++i)
            lca(seq[i].num, seq[i+1].num);

        cout << "#" << test_case << " " << res << "\n";

        for(int i=1; i<N+5; ++i)
            childCnt[i] = 0;

        for(int i=1; i<N+5; ++i)
            childList[i].clear();
	}

	return 0;
}