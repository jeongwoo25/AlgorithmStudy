#include <iostream>
#include <cstring>
#define MAXB 500010
#define MAXS 100010
#define MOD (1 << 30) - 1
using namespace std;

char base[MAXB];
char str[MAXS];

int ans;
unsigned long strKey;
unsigned long strKey2;
unsigned long baseKey;
unsigned long baseKey2;

unsigned long pow(int b, int n)
{
    long long res = 1;

    for(int i=0; i<n; ++i)
        res = ((res * b) & MOD);

    return res;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int test_case;
	int T;
	freopen("38_input.txt", "r", stdin);
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        ans = 0;
        strKey = baseKey = 0;
        strKey2 = baseKey2 = 0;

        cin >> base >> str;

        int lenS = strlen(str);
        int lenB = strlen(base);

        unsigned long power = pow(5, lenS-1);
        unsigned long power2 = pow(17, lenS-1);
        
        for(int i=0; i<lenS; ++i)
        {
            strKey = (((strKey << 2) + strKey) + str[i]) & MOD;
            baseKey = (((baseKey << 2) + baseKey) + base[i]) & MOD;

            strKey2 = (((strKey2 << 4) + strKey2) + str[i]) & MOD;
            baseKey2 = (((baseKey2 << 4) + baseKey2) + base[i]) & MOD;
        }
        
        if(strKey == baseKey && strKey2 == baseKey2) ++ans;
        
        for(int i=lenS; i<lenB; ++i)
        {
            baseKey -= power * base[i-lenS];
            baseKey = (((baseKey << 2) + baseKey) + base[i]) & MOD;

            baseKey2 -= power2 * base[i-lenS];
            baseKey2 = (((baseKey2 << 4) + baseKey2) + base[i]) & MOD;

            if(strKey == baseKey && strKey2 == baseKey2) ++ans;
        }

        cout << "#" << test_case << " " << ans << "\n";
	}

	return 0;
}