#define MAXN 100

int childList[MAXN][5];
int childCnt[MAXN];
//int Graph[MAXN][MAXN];
int stack[MAXN], top;

void dfs_init(int N, int path[100][2])
{
	for(int i=0; i<MAXN; ++i)
	{
		childCnt[i] = 0;
		//for(int j=0; j<MAXN; ++j)
			//Graph[i][j] = 0;
	}

	for(int i=0; i<N; ++i)
	{
		//Graph[path[i][0]][path[i][1]] = 1;
		childList[path[i][0]][childCnt[path[i][0]]++] = path[i][1];
	}

}

int dfs(int n)
{
	bool visit[MAXN] = {false};
	int top = -1;
	int res = -1;

	stack[++top] = n;

	while(top != -1)
	{
		int cur = stack[top--];

		if(!visit[cur])
		{
			visit[cur] = true;

			if(cur > n)
			{
				res = cur;
				break;
			}

			for(int next=childCnt[cur]-1; next>=0; next--)
				//if(!visit[childList[cur][next]] && Graph[cur][childList[cur][next]])
				if(!visit[childList[cur][next]])
					stack[++top] = childList[cur][next];
		}

	}

	return res;
}