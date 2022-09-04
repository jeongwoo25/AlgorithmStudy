#include <iostream>
using namespace std;

int numList[8];
int priceList[8];

void solve(int _price, int idx)
{
    if(_price == 0 || idx > 7)
        return;

    while(_price - priceList[idx] >= 0)
    {
        _price -= priceList[idx];
        numList[idx]++;
    }
    
    solve(_price, idx+1);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("8_input.txt", "r", stdin);
	cin >> T;
    
    priceList[0] = 50000; priceList[1] = 10000; priceList[2] = 5000; priceList[3] = 1000;
    priceList[4] = 500;   priceList[5] = 100;   priceList[6] = 50;   priceList[7] = 10;

    int price;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << "\n";
		cin >> price;
        
        for(int i=0; i<8; i++)
            numList[i] = 0;

        solve(price, 0);

        for(int i=0; i<8; i++)
            cout << numList[i] << " ";
        cout << "\n";
	}

	return 0;
}