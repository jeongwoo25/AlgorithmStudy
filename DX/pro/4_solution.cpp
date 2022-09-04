#include <bits/stdc++.h>
#define N 510
using namespace std;

struct Product{
    int pId;
    int lineId;
    int eId;
    int nTime;
};

struct Request{
    int time;
    Product p;

    bool operator<(const Request& y) const {
        return time > y.time;
    }
};

int line, machine, timeNow;
bool lineUse[N], eUse[N];
queue<Product> lineQ[N];
priority_queue<Request> timeQ;

int casheLine[N];
unordered_map< int, int > casheProduct;

void init(int L, int M)
{
    line = L;
    machine = M;
    timeNow = 0;

    for(int i=0; i<line; i++)
        lineQ[i] = queue<Product>();

    timeQ = priority_queue<Request>();

    memset(lineUse, false, L);
    memset(eUse, false, M);

    casheProduct.clear();
}

void timeFlow(int t)
{
    while(!timeQ.empty() && timeQ.top().time <= t)
    {
        timeNow = timeQ.top().time;

        while(!timeQ.empty() && timeQ.top().time == timeNow)
        {
            Product p = timeQ.top().p;
            timeQ.pop();

            if(p.pId < 0)
                continue;

            lineUse[p.lineId] = false;
            eUse[p.eId] = false;
            casheProduct[p.pId] = 3;
        }

        for(int i=0; i<line; i++)
        {
            if(!lineUse[i] && !lineQ[i].empty())
            {
                Product p = lineQ[i].front();

                if(!eUse[p.eId])
                {
                    lineUse[i] = true;
                    casheLine[i] = p.pId;

                    eUse[p.eId] = true;
                    casheProduct[p.pId] = 2;

                    timeQ.push({ timeNow + p.nTime, p });
                    lineQ[i].pop();
                }
            }
        }
    }
}

int request(int tStamp, int pId, int mLine, int eId, int mTime)
{
    timeFlow(tStamp-1);

    lineQ[mLine].push({ pId, mLine, eId, mTime });
    timeQ.push({ tStamp, { -1 } });
    casheProduct[pId] = 1;

    timeNow = tStamp;
    timeFlow(tStamp);

    return lineUse[mLine] ? casheLine[mLine] : -1;
}

int status(int tStamp, int pId)
{
    timeFlow(tStamp);
    return casheProduct[pId];
}