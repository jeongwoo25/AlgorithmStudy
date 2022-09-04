#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
    
    freopen("1_input.txt", "r", stdin);
	cin >> T;

    int check = 0b1111111111;
    int base;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout  << "#" << test_case << " ";
        cin >> base;
        
        int Nbase = 0, digit;
        int res = 0b0000000000;
        
        for(int i=1; ; i++)
        {
            Nbase = base * i;
            
            while(Nbase > 0)
            {
                digit = Nbase % 10;
                Nbase /= 10;

                res = res | (1 << digit);
            }

            if((res & check) == check)
            {
                cout << base*i << "\n";
                break;
            }
        }
	}

	return 0;
}