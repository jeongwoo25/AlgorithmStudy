#include <iostream>
using namespace std;

int arrN[3001];
int arrM[101];

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("13_input.txt", "r", stdin);
	cin >> T;
    
    int N, M;


	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << " ";

        cin >> N;
        for(int i=1; i<=N; i++)
            cin >> arrN[i];
        
        cin >> M;
        for(int i=1; i<=M; i++)
            cin >> arrM[i];

        int*** dp = new int**[N+M+1];
        for(int i=0; i<=N+M; i++)
        {
            dp[i] = new int*[N+1];
            for(int j=0; j<=N; j++)
                dp[i][j] = new int[M+1];
        }

        






        for(int i=0; i<=N+M; i++)
        {
            for(int j=0; j<=N; j++)
                delete[] dp[i][j];
            delete[] dp[i];
        }
        delete[] dp;
	}

	return 0;
}