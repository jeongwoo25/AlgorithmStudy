#include <iostream>
#define MAX_N 13
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4
#define NO_WAY 5
#define INF 9999
using namespace std;

typedef struct Point
{
    int r;
    int c;
}point;

int print;

int N;
int minLen[MAX_N+1];

int coreAllCnt;
int coreCnt;
int coreConnect;
int maxConnect;

int map[MAX_N][MAX_N];
point coreList[MAX_N];

int visitCnt[MAX_N];
point visitList[MAX_N][MAX_N];

int isPossible(point coreCur, int coreNum, int dir)
{
    if(dir == NO_WAY)
        return 0;
    else
    {
        point visit = coreCur;
        visit.r = coreCur.r;
        visit.c = coreCur.c;

        if(dir == UP)
        {
            while(visit.r > 0)
            {
                --visit.r;

                if(map[visit.r][visit.c]) return 0;
                else
                {
                    map[visit.r][visit.c] = 1;
                    visitList[coreNum][visitCnt[coreNum]++] = visit;
                }
            }

            return coreCur.r;
        }
        else if(dir == LEFT)
        {
            while(visit.c > 0)
            {
                --visit.c;

                if(map[visit.r][visit.c]) return 0;
                else
                {
                    map[visit.r][visit.c] = 1;
                    visitList[coreNum][visitCnt[coreNum]++] = visit;
                }
            }

            return coreCur.c;
        }
        else if(dir == DOWN)
        {
            while(visit.r < N-1)
            {
                ++visit.r;

                if(map[visit.r][visit.c]) return 0;
                else
                {
                    map[visit.r][visit.c] = 1;
                    visitList[coreNum][visitCnt[coreNum]++] = visit;
                }
            }

            return N-1-coreCur.r;
        }
        else if(dir == RIGHT)
        {
            while(visit.c < N-1)
            {
                ++visit.c;

                if(map[visit.r][visit.c]) return 0;
                else
                {
                    map[visit.r][visit.c] = 1;
                    visitList[coreNum][visitCnt[coreNum]++] = visit;
                }
            }

            return N-1-coreCur.c;
        }
    }
}
void removeVisit(int coreNum)
{
    for(int i=0; i<visitCnt[coreNum]; ++i)
    {
        point remove = visitList[coreNum][i];
        map[remove.r][remove.c] = 0;
    }

    visitCnt[coreNum] = 0;
}

int solve(int curr, int preLen)
{
    if(curr < coreCnt)
    {
        point coreCur = coreList[curr];

        for(int dir = UP; dir <= NO_WAY; ++dir)
        {
            int isP = isPossible(coreCur, curr, dir);

            if(isP)
            {
                ++coreConnect;
                maxConnect = (maxConnect < coreConnect) ? coreConnect : maxConnect;

                int len = preLen + isP;
                if(minLen[coreConnect] > len)
                    minLen[coreConnect] = len;

                solve(curr + 1, len);
                removeVisit(curr);
                --coreConnect;
            }
            else removeVisit(curr);
            
            if(dir == NO_WAY)
                solve(curr + 1, preLen);
        }
    }

    return minLen[maxConnect];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("19_input.txt", "r", stdin);
	cin >> T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        print = test_case;
        coreAllCnt = 0;
        coreCnt = 0;
        for(int i=0; i<MAX_N; ++i)
        {
            visitCnt[i] = 0;
            minLen[i] = INF;
        }

        cin >> N;

        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                cin >> map[i][j];
                if(map[i][j] == 1)
                {
                    ++coreAllCnt;

                    if( !(i==0 || j==0 || i==N-1 || j==N-1) )
                    {
                        coreList[coreCnt].r = i;
                        coreList[coreCnt].c = j;
                        ++coreCnt;
                    }
                }
            }
        }

        coreConnect = coreAllCnt - coreCnt;
        maxConnect = coreConnect;

        for(int i=0; i<=coreConnect; ++i)
            minLen[i] = 0;
        
        int res = solve(0, minLen[maxConnect]);

        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}