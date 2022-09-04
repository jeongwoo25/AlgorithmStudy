#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("3_input.txt", "r", stdin);
	cin >> T;
    
	char str[10001];
	int list[16];
	list[0b0000] = 0;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";

		cin >> str;
		int len = strlen(str);

		int j = 0, k = str[0] - 'A';
		for(int i=0; i<(1 << 4); i++)
		{
			if( ((i & (1 << j)) != 0) && ((i & (1 << k)) != 0) )
				list[i] = 1;
			else list[i] = 0;
		}
		
		int input;

		for(int i=1; i<len; i++)
		{
			int thisList[16];
			for(int i=0; i<16; i++)
				thisList[i] = 0;
			
			input = str[i] - 'A';

			for(int i=0; i<(1 << 4); i++)
			{
				if(list[i] != 0)
				{
					if(i & (1 << input))
					{
						for(int j=0; j<(1 << 4); j++)
							if(j & (1 << input))
								thisList[j] = (thisList[j] + list[i]) % 1000000007;
					}
					else
					{
						for(int j=0; j<(1 << 4); j++)
							if( ((j & (1 << input)) != 0) && ((j & i) != 0))
								thisList[j] = (thisList[j] + list[i]) % 1000000007;
					}
				}
			}

			for(int i=0; i<16; i++)
				list[i] = thisList[i];
		}

		int res = 0;
		for(int i=0; i<16; i++)
			res = (res + list[i]) % 1000000007;
		cout << res << "\n";
	}

	return 0;
}