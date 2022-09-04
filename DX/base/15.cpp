#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("15_input.txt", "r", stdin);
	cin >> T;
    
    int n, p;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << " ";
        cin >> n >> p;
        
		bool visited[1000001] = {false};

		int tmp;
		for(int i=0; i<n; i++)
		{
			cin >> tmp;
			visited[tmp] = true;
		}

		int start=1, end=1, cnt=0, max=p+1;

		while(end <= 1000000)
		{
			if(visited[end])
			{
				cnt++;
				end++;
				max = (max < cnt ? cnt : max);
			}
			else
			{
				if(p == 0)
				{
					if(!visited[start]) p++;
					cnt--;
					start++;
				}
				else
				{
					p--;
					cnt++;
					end++;
					max = (max < cnt ? cnt : max);
				}
			}
		}

		cout << max << "\n";
	}

	return 0;
}