#include <iostream>
using namespace std;

int list[201];

int solve(int _num1, int _num2, int _max)
{
    int left, right;

    if(_num1 < _num2)
    {
        left = (_num1+1)/2;
        right = (_num2+1)/2;
    }
    else
    {
        left = (_num2+1)/2;
        right = (_num1+1)/2;
    }

    for(int i=left; i<=right; i++)
    {
        list[i]++;
        if(_max < list[i])
            _max = list[i];
    }

    return _max;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("9_input.txt", "r", stdin);
	cin >> T;

    int numStudent;
    int max, num1, num2;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        cout << "#" << test_case << " ";
        
        max = 0;
        for(int i=0; i<201; i++)
            list[i] = 0;

        cin >> numStudent;

		for(int i=0; i<numStudent; i++)
        {
            cin >> num1 >> num2;
            max = solve(num1, num2, max);
        }
        
        cout << max << "\n";
	}

	return 0;
}