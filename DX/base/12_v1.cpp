#include <iostream>
using namespace std;

int value[101];
int volume[101];
int memo[101][1001];

int solve(int idx, int n, int resVol)
{
    if(idx == n+1 || resVol == 0)
        return 0;

    if(memo[idx][resVol] != -1)
        return memo[idx][resVol];

    int ret = 0, tmp;

    if(volume[idx] <= resVol)
    {
        tmp = value[idx] + solve(idx+1, n, resVol-volume[idx]);
        if(tmp > ret)
            ret = tmp;
    }

    tmp = solve(idx+1, n, resVol);
    if(tmp > ret) ret = tmp;

    memo[idx][resVol] = ret;
    return memo[idx][resVol];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("12_input.txt", "r", stdin);
	cin >> T;
    
    int n, maxVol;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << " ";
        cin >> n >> maxVol;

        for(int i=1; i<=n; i++)
            for(int j=1; j<=maxVol; j++)
                memo[i][j] = -1;

        for(int i=1; i<=n; i++)
            cin >> volume[i] >> value[i];

        int res = solve(1, n, maxVol);
        cout << res << "\n";
	}

	return 0;
}