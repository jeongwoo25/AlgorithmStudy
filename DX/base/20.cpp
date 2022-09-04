#include <iostream>
#define MAXN 310
#define QUEUE_SIZE 4000
using namespace std;

typedef struct Point{
    int r;
    int c;
}point;

int N, res;
int map[MAXN][MAXN];
int check[MAXN][MAXN];

int front, rear, size;
point queue[QUEUE_SIZE];

bool is0(int r, int c)
{
    if(!(map[r-1][c-1] | map[r-1][c] | map[r-1][c+1] |
        map[r][c-1] | map[r][c] | map[r][c+1] |
        map[r+1][c-1] | map[r+1][c] | map[r+1][c+1]))
        return true;
    else return false;
}

void BFS()
{
    while(size > 0)
    {
        front = (front + 1) % QUEUE_SIZE;
        point pop = queue[front];
        --size;

        if(!check[pop.r][pop.c])
        {
            check[pop.r][pop.c] = 1;

            if(is0(pop.r, pop.c))
            {
                point tmp;
                for(int i=-1; i<=1; ++i)
                {
                    for(int j=-1; j<=1; ++j)
                    {
                         tmp.r = pop.r + i;
                         tmp.c = pop.c + j;
                         
                         rear = (rear + 1) % QUEUE_SIZE;
                         queue[rear] = tmp;
                         size++;
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("20_input.txt", "r", stdin);
	cin >> T;
    
    char c;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        res = 0;
        cin >> N;

        for(int i=1; i<=N; ++i)
        {
            for(int j=1; j<=N; ++j)
            {
                cin >> c;
                if(c == '*')
                {
                    map[i][j] = 1;
                    check[i][j] = 1;
                }
                else if(c == '.')
                {
                    map[i][j] = 0;
                    check[i][j] = 0;
                }
            }
        }

        for(int i=0; i<=N+1; ++i)
        {
            map[0][i] = 0;      check[0][i] = 1;
            map[N+1][i] = 0;    check[N+1][i] = 1;
            map[i][0] = 0;      check[i][0] = 1;
            map[i][N+1] = 0;    check[i][N+1] = 1;
        }

        for(int i=1; i<=N; ++i)
        {
            for(int j=1; j<=N; ++j)
            {
                if(is0(i, j) && !check[i][j])
                {
                    ++res;

                    point p;
                    p.r = i;
                    p.c = j;

                    front = -1;
                    rear = -1;
                    size = 0;

                    rear = (rear+1) % QUEUE_SIZE;
                    queue[rear] = p;
                    ++size;

                    BFS();
                }
            }
        }

        for(int i=1; i<=N; ++i)
            for(int j=1; j<=N; ++j)
                if(!check[i][j])
                    ++res;
        
        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}