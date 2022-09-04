#define QUEUE_SIZE 100

struct xy
{
    int x;
    int y;
};

int myMap[12][12];
xy queue[QUEUE_SIZE];

void fillList(xy tmp, int& cnt, xy list[])
{
    xy up = tmp; --up.y;
    xy down = tmp; ++down.y;
    xy left = tmp; --left.x;
    xy right = tmp; ++right.x;

    if(myMap[up.y][up.x] == 0) list[cnt++] = up;
    if(myMap[down.y][down.x] == 0) list[cnt++] = down;
    if(myMap[left.y][left.x] == 0) list[cnt++] = left;
    if(myMap[right.y][right.x] == 0) list[cnt++] = right;
}

void bfs_init(int map_size, int map[10][10])
{
    for(int i=1; i<11; ++i)
        for(int j=1; j<11; ++j)
            myMap[i][j] = map[i-1][j-1];
    
    for(int i=0; i<12; ++i)
    {
        myMap[i][0] = 1;
        myMap[i][11] = 1;
        myMap[0][i] = 1;
        myMap[11][i] = 1;
    }
}

int bfs(int x1, int y1, int x2, int y2)
{
    int dist[11][11] = {0, };
    bool visit[11][11] = {false, };
    int front = -1, rear = -1, size = 0;

    xy start, end;
    start.x = x1; end.x = x2;
    start.y = y1; end.y = y2;

    queue[++rear] = start;
    visit[start.x][start.y] = true;
    ++size;

    while(size > 0)
    {
        front = (front + 1) % QUEUE_SIZE;
        xy cur = queue[front];
        --size;

        int cnt = 0;
        xy list[4];
        fillList(cur, cnt, list);
        
        for(int next=0; next<cnt; ++next)
        {
            if(!visit[list[next].x][list[next].y])
            {
                rear = (rear + 1) % QUEUE_SIZE;
                queue[rear] = list[next];
                visit[list[next].x][list[next].y] = true;
                dist[list[next].x][list[next].y] = dist[cur.x][cur.y] + 1;
                ++size;
            }
        }
    }

    if(dist[end.x][end.y] == 0) return -1;
    else return dist[end.x][end.y];
}