#include <iostream>
using namespace std;

int resSwapCnt;

int numLen(int _num)
{
	int i;
	for(i=1; ; i++)
	{
		if(_num / 10 == 0)
			break;

		_num /= 10;
	}

	return i;
}

int findMax(int _num, int _len)
{
	int max = 0, tmp;

	for(int i=0; i<_len; i++)
	{
		tmp = _num % 10;

		if(max < tmp)
			max = tmp;

		_num /= 10;
	}

	return max;
}

int solve(int _num, int _swapCnt, int _len)
{
	if(_swapCnt == 0)
		return _num;

	if(_len == 1)
	{
		resSwapCnt = _swapCnt;
		return _num;
	}

	int res = 0;
	int max = findMax(_num, _len);

	int k = 1;
	for(int i=0; i<_len-1; i++)
		k *= 10;
	
	int first = _num / k;

	if(first >= max)
		return first*k + solve(_num%k, _swapCnt, _len-1);

	int mul = 1, tmp;
	for(int i=0; i<_len-1; i++)
	{
		if((_num/mul) % 10 == max)
		{
			tmp = max*k + solve(_num%k - mul*max + mul*first, _swapCnt-1, _len-1);
			if(tmp > res) res = tmp;
		}

		mul *= 10;
	}

	return res;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("10_input.txt", "r", stdin);
	cin >> T;
    
	int num, res, swapCnt, len;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << " ";
		
		resSwapCnt = 0;
        cin >> num >> swapCnt;

		len = numLen(num);
		res = solve(num, swapCnt, len);

		if(resSwapCnt != 0)
		{
			if(resSwapCnt & 1)
			{
				int check[10] = {0};

				for(int i=0; i<len; i++)
				{
					check[num%10]++;
					num /= 10;
				}

				int over2 = 0;
				for(int i=0; i<10; i++)
				{
					if(check[i] >= 2)
					{
						over2 = 1;
						break;
					}
				}

				if(!over2)
				{
					int digit1 = res % 10;
					int digit2 = (res / 10) % 10;

					res = res + (digit1-digit2)*10 -digit1+digit2;
				}
			}
		}

		cout << res << "\n";
	}

	return 0;
}