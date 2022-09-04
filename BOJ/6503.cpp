#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int m, ans, len, cnt;
string str;
int use[128];

int main(void) {
    while(1) {
        cin >> m;
        if(m == 0) break;

        ans = len = 1;
        cnt = m - 1;

        cin.ignore();
        getline(cin, str);
        
        int strLen = str.length();
        memset(use, 0, sizeof(use));
        use[str.at(0)] = 1;

        int front=0, rear=0;

        while(1) {
            if(cnt > 0 || (cnt == 0 && use[str[rear+1]])) {
                ++rear; ++len;
                if(ans < len) ans = len;
                ++use[str[rear]];

                if(use[str[rear]] == 1) --cnt;
            }
            else {
                --use[str[front]];
                if(use[str[front]] == 0) {
                    ++front; --len; ++cnt;
                }
                else {
                    ++front; --len;
                }
            }

            if(rear == strLen - 1) break;
        }

        cout << ans << "\n";
    }

    return 0;
}