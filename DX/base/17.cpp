#include <iostream>
#define MAXN 200010
using namespace std;

int N, K;
int wearList[MAXN];
int block[MAXN];

bool isPossible(int target)
{
	int index = -1;

	for(int i=0; i<K; i++)
    {
		for(int j=0; j<block[i]; j++)
        {
			++index;

			if(index == N)
                return false;

			if(wearList[index] > target)
            {
				--i;
				break;
			}
		}
	}
    
	return true;
}

int solve()
{
	int start = 0, end = 200000;

	while(start < end)
    {
		int mid = (start + end) / 2;
        
		if (isPossible(mid))
            end = mid;
		else start = mid + 1;
	}

	return end;
}

int main(int argc, char** argv)
{
    int test_case;
	int T;
    freopen("17_input.txt", "r", stdin);
	cin >> T;

	for(test_case = 1; test_case <= T; ++test_case)
    {
		cin >> N >> K;
		for(int i=0; i<N; ++i)
            cin >> wearList[i];

		for(int i=0; i<K; ++i)
            cin >> block[i];

		int ret = solve();
		cout << "#" << test_case << " " << ret << '\n';
	}
	return 0;
}