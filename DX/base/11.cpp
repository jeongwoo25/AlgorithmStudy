#include <iostream>
#include <cstring>
using namespace std;

char str1[1001];
char str2[1001];
int arr[1001][1001];

int solve(int _len1, int _len2)
{
	for(int i=0; i<=_len1; i++)
		arr[0][i] = 0;
	for(int i=0; i<=_len2; i++)
		arr[i][0] = 0;

	for(int i=1; i<=_len2; i++)
	{
		for(int j=1; j<=_len1; j++)
		{
			if(str2[i-1] == str1[j-1])
				arr[i][j] = arr[i-1][j-1] + 1;
			else
			{
				if(arr[i][j-1] > arr[i-1][j])
					arr[i][j] = arr[i][j-1];
				else arr[i][j] = arr[i-1][j];
			}
		}
	}
		
	return arr[_len2][_len1];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("11_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";
		cin >> str1 >> str2;

		int len1 = strlen(str1);
		int len2 = strlen(str2);
		
		int res = solve(len1, len2);
		cout << res << "\n";
	}

	return 0;
}