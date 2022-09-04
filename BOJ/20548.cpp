#include <iostream>
using namespace std;

int ans;
long long spicy;
int arr3[13];
long long arr7[13];

int main(void) {
    arr3[0] = arr7[0] = 1;
    for(int i=1; i<=12; ++i) {
        arr3[i] = (arr3[i-1] << 1) + arr3[i-1];
        arr7[i] = (arr7[i-1] << 3) - arr7[i-1];
    }

    cin >> spicy;
    ans = 0;

    for(int i=12; i>=0; --i) {
        for(int j=0; j<2; ++j) {
            if(spicy >= arr7[i]) {
                spicy -= arr7[i];
                ans += arr3[i];
            }
            else break;
        }
    }


    cout << ans;
    return 0;
}