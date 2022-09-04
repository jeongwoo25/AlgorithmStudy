#include <iostream>
#include <cstdlib>
#define MAXN 101
using namespace std;

struct student{
    int num;
    int room;
};

int N, range, week, idx, total, cnt, M;

student *ptr1, *ptr2;
student list[MAXN];
student* arr[MAXN];

void swap(student **good, student **bad)
{
    ++(*good)->room;
    --(*bad)->room;

    (*good)->num += 2;
    (*bad)->num -= 2;

    student* tmp = *good;
    *good = *bad;
    *bad = tmp;
}

void assign() {
    for(int i=1; i<N; ++i) {
        int j = i+1;

        if(arr[i]->num >= 0 && arr[j]->num >= 0){
            if(arr[j]->num - arr[i]->num >= 2)
                swap(&arr[i], &arr[j]);
        }
        else if(arr[i]->num >= 0 && arr[j]->num < 0)
            continue;
        else if(arr[i]->num < 0 && arr[j]->num >= 0)
            swap(&arr[i], &arr[j]);
        else if(arr[i]->num < 0 && arr[j]->num < 0)
            if(arr[j]->num - arr[i]->num >= 4)
                swap(&arr[i], &arr[j]);
    }
}

void check() {
    if(abs(ptr1->room - ptr2->room) <= range) {
        ++cnt; ++total;
        if(M < cnt) M = cnt;
    }
    else cnt = 0;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> idx >> range >> week;
    total = cnt = M = 0;

    for(int i=1; i<=N; ++i) {
        list[i].room = i;
        arr[i] = &list[i];
    }

    ptr1 = &list[1];
    ptr2 = &list[idx];

    check();

    for(int i=2; i<=week; ++i) {
        int tmp;

        for(int j=1; j<=N; ++j)
            cin >> list[j].num;

        for(int j=1; j<=N; ++j) {
            cin >> tmp;
            list[j].num += tmp * (-1);
        }
        
        assign();
        check();
    }

    cout << total << " " << M;
    return 0;
}