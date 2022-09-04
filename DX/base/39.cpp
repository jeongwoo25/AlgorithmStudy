#include <iostream>
#define MAX 2010
#define HASH_SIZE (1 << 30)
#define MOD (HASH_SIZE - 1)
using namespace std;

char c;
int H, W, N, M;
int shiftr = 2;
int shiftc = 4;
int powr, powc;

long long myPic[MAX][MAX];
long long teachPic[MAX][MAX];

long long myHash;
long long rowHash[MAX][MAX];
long long teachHash[MAX][MAX];

int pow(int shift, int n)
{
    long long res = 1;

    for(int i=0; i<n; ++i)
        res = (((res << shift) + res) & MOD);

    return res;
}

int getHash(long long* str, int len, int shift)
{
	int hash = 0;

	for(int i=0; i<len; ++i)
		hash = (hash << shift) + hash + *str++;

	return hash & MOD;
}

int getColHash(long long str[][MAX], int len, int shift, int col)
{
	int hash = 0;

	for(int i=0; i<len; ++i)
		hash = (hash << shift) + hash + str[i][col];

	return hash & MOD;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int test_case;
	int T;
	freopen("39_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> H >> W >> N >> M;

		for(int i=0; i<H; ++i)
		{
			for(int j=0; j<W; ++j)
			{
				cin >> c;
				if(c == 'o') myPic[i][j] = 1;
				else myPic[i][j] = 0;
			}
		}
		
		for(int i=0; i<N; ++i)
		{
			for(int j=0; j<M; ++j)
			{
				cin >> c;
				if(c == 'o') teachPic[i][j] = 1;
				else teachPic[i][j] = 0;
			}
		}

		for(int i=0; i<H; ++i)
			rowHash[i][0] = getHash(myPic[i], W, shiftr);

		myHash = getColHash(rowHash, H, shiftc, 0);
		
		powr = pow(shiftr, W-1);
		powc = pow(shiftc, H-1);

		for(int i=0; i<N; ++i)
		{
			rowHash[i][0] = getHash(teachPic[i], W, shiftr);

			for(int j=1; j<=M-W; ++j)
			{
				rowHash[i][j] = rowHash[i][j-1];
				rowHash[i][j] -= powr * teachPic[i][j-1];
				rowHash[i][j] = ((rowHash[i][j] << shiftr) + rowHash[i][j] + teachPic[i][j+W-1]) & MOD;
			}
		}

		for(int i=0; i<=M-W; ++i)
		{
			teachHash[0][i] = getColHash(rowHash, H, shiftc, i);

			for(int j=1; j<=N-H; ++j)
			{
				teachHash[j][i] = teachHash[j-1][i];
				teachHash[j][i] -= powc * rowHash[j-1][i];
				teachHash[j][i] = ((teachHash[j][i] << shiftc) + teachHash[j][i] + rowHash[j+H-1][i]) & MOD;
			}
		}

		int cnt = 0;

		for(int i=0; i<=N-H; ++i)
			for(int j=0; j<=M-W; ++j)
				if(myHash == teachHash[i][j]) ++cnt;

		cout << "#" << test_case << " " << cnt << "\n";
	}
    
	return 0;
}