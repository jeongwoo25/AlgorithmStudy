#include <bits/stdc++.h>
using namespace std;

int have[15001001], rest[15001001], cmax[101][10];
char city[15001001], num[15001001];
int dist[101][101], N, TC;

int hash_make(char s[]) {
    int ret = 0;
    for(register int i=0; s[i] != 0; i++) {
        ret *= 27; ret += (s[i] - 'a' + 1);
    }
    return ret;
}

void init(int _N, int M, int mRoads[][2]) {
    int i, j, k;
    N = _N;
    TC++;
    for(i=1; i<=N; i++) for(j=1; j<=N; j++) dist[i][j] = 100;
    for(i=1; i<=N; i++) dist[i][i] = 0;
    for(i=0; i<M; i++) dist[mRoads[i][0]][mRoads[i][1]] = dist[mRoads[i][1]][mRoads[i][0]] = 1;

    for(k=1; k<=N; k++) {
        for(i=1; i<=N; i++) {
            for(j=1; j<=N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    //memset(have, 0, sizeof(have));
    memset(cmax, 0, sizeof(cmax));
}


void addRestaurant(int mCityID, char mName[]){
    int h = hash_make(mName);
    city[h] = mCityID; rest[h] = 0;
}

void addValue(char mName[], int mScore){
    int h = hash_make(mName);
    rest[h] += mScore;
    int i, j, n, tmp = 0; n = strlen(mName);
    for(i=0; i<n; i++) {
        tmp = 0;
        for(j=i; j<n; j++) { // i~j 까지의 문자열을 have에 갱신해주는 과정
            tmp *= 27; tmp += (mName[j] - 'a' + 1);
            if(num[tmp] != TC) { have[tmp] = rest[h]; num[tmp] = TC; }
            else have[tmp] = max(have[tmp], rest[h]);
        }
    }

    int nowcity = city[h];
    for(i=0; i<3; i++) {
        if(cmax[nowcity][i] == h) {
            cmax[nowcity][i] = 0;
            for(j=i+1; j<3; j++) swap(cmax[nowcity][j], cmax[nowcity][j-1]);
        }
    }
    for(i=0; i<3; i++) {
        if( rest[cmax[nowcity][i]] < rest[h] ) {
            for(j=2; j>=i; j--) swap(cmax[nowcity][j+1], cmax[nowcity][j]);
            cmax[nowcity][i] = h; break;
        }
    }
}


int bestValue(char mStr[])
{
    int h = hash_make(mStr);
    if(num[h] != TC) return 0;
    return have[h];
}

int reCity[100], arr[100];
int regionalValue(int mCityID, int mDist)
{
    int i, j, cnt = 0, ret = 0;
    for(i=1; i<=N; i++) {
        if( dist[mCityID][i] <= mDist ) {
            reCity[cnt] = i; arr[cnt] = 0;
            cnt++;
        }
    }

    for(i=0; i<3; i++) {
        int max1 = 0;
        for(j=0; j<cnt; j++) {
            if( rest[ cmax[ reCity[j] ][ arr[j] ] ] > rest[ cmax[ reCity[max1] ][ arr[max1] ] ] ) {
                max1 = j;
            }
        }
        ret += rest[ cmax[ reCity[max1] ][ arr[max1] ] ];
        arr[max1]++;
    }
    return ret;
}