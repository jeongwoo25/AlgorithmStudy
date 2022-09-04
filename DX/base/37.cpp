#include <iostream>
#include <cstring>
#define MAXN 100010
#define HASH_SIZE (1 << 18)
#define DIV (HASH_SIZE - 1)
using namespace std;

struct Node{
    int data;
    char str[51];
    Node* next;
};

int N, M, bufCnt, ans;
char tmp[51];

Node buf[MAXN];
Node hashTable[HASH_SIZE];

void init()
{
    ans = 0;
    bufCnt = 1;

    for(int i=0; i<HASH_SIZE; ++i)
    {
        hashTable[i].next = nullptr;
        hashTable[i].data = 0;
    }
}

int getKey(const char* str)
{
    int hash = 5381;
    
    for(int i=0; str[i]; ++i)
        hash = ((hash << 5) + hash) + (str[i] - 'a' + 1);

    return (int)(hash & DIV);
}

void strCpy(char* empty, char *str)
{
    while(*str) *empty++ = *str++;
    *empty = 0;
}

bool strCmp(char* strA, char* strB)
{
    while(*strA)
        if(*strA++ != *strB++) return false;
    
    return *strA == *strB;
}

void hashAdd(char str[])
{
    strCpy(buf[bufCnt].str, str);
    buf[bufCnt].next = nullptr;
    buf[bufCnt].data = 1;

    Node* ptr = &hashTable[getKey(str)];

    while(ptr->next)
        ptr = ptr->next;

    ptr->next = &buf[bufCnt];
    ++bufCnt;
}

void hashFind(char str[])
{
    Node* ptr = &hashTable[getKey(str)];

    while(ptr->next)
    {
        if(strCmp(ptr->next->str, str))
        {
            ++ans;
            break;
        }

        ptr = ptr->next;
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
	int test_case;
    freopen("37_input.txt", "r", stdin);
	int T;
	cin >> T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        init();

        cin >> N >> M;

        for(int i=1; i<=N; ++i)
        {
            cin >> tmp;
            hashAdd(tmp);
        }

        for(int i=1; i<=M; ++i)
        {
            cin >> tmp;
            hashFind(tmp);
        }

        cout << "#" << test_case << " " << ans << "\n";
	}

	return 0;
}