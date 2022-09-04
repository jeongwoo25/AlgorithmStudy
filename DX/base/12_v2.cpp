#include <iostream>
using namespace std;

int value[101];
int volume[101];
int memo[101][1001];

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

        for(int i=0; i<=n; i++)
            memo[i][0] = 0;
        for(int i=0; i<=maxVol; i++)
            memo[0][i] = 0;

        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=maxVol; j++)
            {
                if(volume[i] <= j)
                {
                    if(value[i] + memo[i-1][j-volume[i]] > memo[i-1][j])
                        memo[i][j] = value[i] + memo[i-1][j-volume[i]];
                    else
                        memo[i][j] = memo[i-1][j];
                }
                else
                    memo[i][j] = memo[i-1][j];
            }
        }
        
        cout << memo[n][maxVol] << "\n";
	}

	return 0;
}