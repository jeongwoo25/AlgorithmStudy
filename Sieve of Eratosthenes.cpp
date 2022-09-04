#include <iostream>
#include <cmath>
#define MAX 100
using namespace std;

int number = MAX;
int primeNum[MAX+1];

void primeNumberSieve()
{
    primeNum[0] = 0;
    primeNum[1] = 0;

    for(int i=2; i<=MAX; i++)
        primeNum[i] = i;
    
    for(int i=2; i<=sqrt(MAX); i++)
    {
        if(primeNum[i] == 0)
            continue;
        for(int j=i*i; j<=MAX; j+=i)
            primeNum[j] = 0;
    }

    for(int i=2; i<=MAX; i++)
        if(primeNum[i] != 0)
            cout << primeNum[i] << "\n";
}

int main(void)
{
    primeNumberSieve();
    return 0;
}