#include<iostream>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
    
	freopen("2_input.txt", "r", stdin);
	cin >> T;

	int Nbit, M;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cout << "#" << test_case << " ";
        cin >> Nbit >> M;

        int k = (1 << Nbit) - 1;

        if( (M & k) == k ) cout << "ON\n";
        else cout << "OFF\n";
	}

	return 0;
}