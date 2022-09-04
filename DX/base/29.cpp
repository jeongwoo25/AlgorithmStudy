#include <iostream>
#define MAXN 10001
using namespace std;

struct Node{
    int idx;
    int numChild;
    int subTree;
    Node* leftChild;
    Node* rightChild;
};

int V, E, node1, node2, p, c;
Node nodeList[MAXN];
int depth[MAXN];
int parent[MAXN][15];

void setDepth(Node* cur)
{
    depth[cur->idx] = depth[parent[cur->idx][0]] + 1;

    if(cur->numChild)
    {
        setDepth(cur->leftChild);

        if(cur->numChild == 2)
            setDepth(cur->rightChild);
    }
}
int lca(int x, int y)
{
    if(depth[y] > depth[x])
    {
        int tmp = x;
        x = y;
        y = tmp;
    }

    int diff = depth[x] - depth[y];

    for(int i=0; diff != 0; ++i)
    {
        if(diff % 2 == 1)
            x = parent[x][i];
        diff /= 2;
    }

    if(x == y)  return x;

    if(x != y)
    {
        for(int i=14; i>=0; --i)
        { 
            if(parent[x][i] != parent[y][i])
            {
                x = parent[x][i];
                y = parent[y][i];
            }
        }
    }

    return parent[x][0];
}

int traverse(Node* cur)
{
    int numChild = cur->numChild;

    if(!numChild)
        return 1;

    int left = traverse(cur->leftChild);
    int right = 0;
    
    if(numChild== 2) right = traverse(cur->rightChild);

    return left + right + 1;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("29_input.txt", "r", stdin);
	cin >> T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        for(int i=1; i<MAXN; ++i)
        {
            nodeList[i].numChild = 0;
            nodeList[i].idx = i;
        }
        
        cin >> V >> E >> node1 >> node2;

        for(int i=0; i<E; ++i)
        {
            cin >> p >> c;

            if(nodeList[p].numChild == 0) nodeList[p].leftChild = &nodeList[c];
            else nodeList[p].rightChild = &nodeList[c];

            ++nodeList[p].numChild;

            parent[c][0] = p;
        }

        parent[1][0] = 0;
        depth[0] = 0;

        setDepth(&nodeList[1]);

        for(int j=1; j<=14; ++j)
            for(int i=1; i<=V; ++i)
                parent[i][j] = parent[parent[i][j-1]][j-1];

        int ancient = lca(node1, node2);
        int res = traverse(&nodeList[ancient]);

        cout << "#" << test_case << " " << ancient << " " << res << "\n";
	}

	return 0;
}