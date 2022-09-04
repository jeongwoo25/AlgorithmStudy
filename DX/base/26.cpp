#include <iostream>
#define MAXN 101
using namespace std;

int N;
int node2, node1, node0;
char nodeList[MAXN];

void traverse(int cur)
{
	if(cur <= N)
	{
		traverse(2*cur);
		cout << nodeList[cur];
		traverse(2*cur+1);
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("26_input.txt", "r", stdin);

	char c;
	int idx;
    
	for(test_case = 1; test_case <= 10; ++test_case)
	{
		cin >> N;

		node2 = (N-1)/2;

		if(N & 1) node1 = 0;
		else node1 = 1;

		node0 = N - node2 - node1;

		for(int i=0; i<node2; ++i)
		{
			cin >> idx >> c;
			nodeList[idx] = c;
			cin >> idx >> idx;
		}
		for(int i=0; i<node1; ++i)
		{
			cin >> idx >> c;
			nodeList[idx] = c;
			cin >> idx;
		}
		for(int i=0; i<node0; ++i)
		{
			cin >> idx >> c;
			nodeList[idx] = c;
		}

		cout << "#" << test_case << " ";
		traverse(1);
		cout << "\n";
	}

	return 0;
}