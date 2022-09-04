#include <iostream>
#include <cstring>
#include <cmath>
#define MAXN 1010
#define MAXD 1500000
using namespace std;

struct Node{
    int x;
    int y;
};

int N, visitCnt, mNum;
long long res;
double _res, E, minDist;

Node island[MAXN];
int visitList[MAXN];
bool visit[MAXN];
double dist[MAXN][MAXN];

void solve()
{
    visitList[++visitCnt] = 1;
    visit[1] = true;

    while(visitCnt < N)
    {
        minDist = MAXD;

        for(int i=1; i<=visitCnt; ++i)
        {
            for(int j=1; j<=N; ++j)
            {
                if(!visit[j] && minDist > dist[visitList[i]][j])
                {
                    minDist = dist[visitList[i]][j];
                    mNum = j;
                }
            }
        }

        visitList[++visitCnt] = mNum;
        visit[mNum] = true;
        _res += pow(minDist, 2);
    }

}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("22_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;

        _res = 0;
        visitCnt = 0;
        memset(visit, false, sizeof(visit));

        for(int i=1; i<=N; ++i)
            cin >> island[i].x;
        
        for(int i=1; i<=N; ++i)
            cin >> island[i].y;

        cin >> E;

        double d;

        for(int i=1; i<=N; ++i)
        {
            for(int j=i; j<=N; ++j)
            {
                if(i == j) dist[i][j] = 0;
                else
                {
                    d = sqrt(pow(island[i].x-island[j].x, 2) + pow(island[i].y-island[j].y, 2));
                    dist[i][j] = d; dist[j][i] = d;
                }
            }
        }

        solve();

        _res *= E;
        res = floor(_res + 0.5);
        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}