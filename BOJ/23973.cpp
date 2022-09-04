#include <iostream>
#include <cstring>
#include <cstdlib>
#define MAXN 100010
using namespace std;

struct point{
    int r;
    int c;
};

int N, M, targetCnt, cnt[10];
int** map;
point target[MAXN];

bool find(point p) {
    for(int i=1; i<=9; ++i) {
        for(int j = p.c - i; j <= p.c + i; ++j) {
            if(map[p.r - i][j]) ++cnt[10 - i];
            if(map[p.r + i][j]) ++cnt[10 - i];
        }
        for(int j = p.r - i + 1; j <= p.r + i - 1; ++j) {
            if(map[j][p.c - i]) ++cnt[10 - i];
            if(map[j][p.c + i]) ++cnt[10 - i];
        }
    }

    if(cnt[1] == 1 && cnt[2] == 1 && cnt[3] == 1 && cnt[4] == 1 && cnt[5] == 1 && 
        cnt[6] == 1 && cnt[7] == 1 && cnt[8] == 1 && cnt[9] == 1) return true;
    else return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    map = (int**)malloc((N+18) * sizeof(int*));
    for(int i=0; i<N+18; ++i)
        map[i] = (int*)malloc((M+18) * sizeof(int));

    for(int i=0; i<N+18; ++i)
        memset(map[i], 0, sizeof(int)*(M+18));

    char c;
    for(int i=9; i<N+9; ++i) {
        for(int j=9; j<M+9; ++j) {
            cin >> c;
            map[i][j] = c - '0';

            if(map[i][j] == 1) {
                target[targetCnt].r = i;
                target[targetCnt].c = j;
                ++targetCnt;
            }
        }
    }
    
    bool isFind = false;

    for(int i=0; i<targetCnt; ++i) {
        if(find(target[i])) {
            isFind = true;
            cout << target[i].r - 9 << " " << target[i].c - 9;
            break;
        }
        for(int i=1; i<=9; ++i) cnt[i] = 0;
    }

    if(!isFind) cout << -1;

    return 0;
}