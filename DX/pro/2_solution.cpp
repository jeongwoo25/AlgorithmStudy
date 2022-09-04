#include <cstring>
#define MAXP 50010
#define MAXU 1010
#define MAXN 10010

struct Node{
    int pID;
    int row;
    int col;
    bool visit;
};

struct Person{
    int vListCnt;
    int vList[110];
};

int placeCnt;

Node place[MAXP];
Person user[MAXU];

int rowArrCnt[MAXN], colArrCnt[MAXN], rdArrCnt[MAXN+MAXN], ruArrCnt[MAXN+MAXN];
Node *rowArr[MAXN][11], *colArr[MAXN][11], *rdArr[MAXN+MAXN][11], *ruArr[MAXN+MAXN][11];

void init()
{
    for(int i=1; i<MAXP; ++i)
        place[i].visit = false;

    for(int i=1; i<MAXU; ++i)
        user[i].vListCnt = 0;

    memset(rowArrCnt, 0, sizeof(rowArrCnt));
    memset(colArrCnt, 0, sizeof(colArrCnt));
    memset(rdArrCnt, 0, sizeof(rdArrCnt));
    memset(ruArrCnt, 0, sizeof(ruArrCnt));
}

void addPlace(int pID, int r, int c)
{
    place[pID].row = r;
    place[pID].col = c;
    place[pID].pID = pID;

    rowArr[r][rowArrCnt[r]++] = &place[pID];
    colArr[c][colArrCnt[c]++] = &place[pID];
    rdArr[10000 + r - c][rdArrCnt[10000 + r - c]++] = &place[pID];
    ruArr[r + c][ruArrCnt[r + c]++] = &place[pID];
}

void removePlace(int pID)
{
    place[pID].visit = true;

    int r = place[pID].row;
    int c = place[pID].col;

    for(int i=0; i<rowArrCnt[r]; ++i){
        if(rowArr[r][i]->pID == pID){
            for(int j=i; j<rowArrCnt[r]-1; ++j){
                rowArr[r][j] = rowArr[r][j+1];
            }
            break;
        }
    }
    --rowArrCnt[r];

    for(int i=0; i<colArrCnt[c]; ++i){
        if(colArr[c][i]->pID == pID){
            for(int j=i; j<colArrCnt[c]-1; ++j){
                colArr[c][j] = colArr[c][j+1];
            }
            break;
        }
    }
    --colArrCnt[c];

    int idx = 10000 + r - c;
    for(int i=0; i<rdArrCnt[idx]; ++i){
        if(rdArr[idx][i]->pID == pID){
            for(int j=i; j<rdArrCnt[idx]-1; ++j){
                rdArr[idx][j] = rdArr[idx][j+1];
            }
            break;
        }
    }
    --rdArrCnt[idx];

    for(int i=0; i<ruArrCnt[r+c]; ++i){
        if(ruArr[r+c][i]->pID == pID){
            for(int j=i; j<ruArrCnt[r+c]-1; ++j){
                ruArr[r+c][j] = ruArr[r+c][j+1];
            }
            break;
        }
    }
    --ruArrCnt[r+c];
}

void contactTracing(int uID, int visitNum, int moveInfo[], int visitList[])
{
    Node* start = &place[moveInfo[0]];
    visitList[0] = moveInfo[0];
    user[uID].vList[user[uID].vListCnt++] = visitList[0];

    int dir;

    for(int i=1; i<visitNum; ++i)
    {
        dir = moveInfo[i];

        int tmp, vID;

        if(dir == 0 || dir == 4)
        {
            if(dir == 0)
            {
                tmp = -1;

                for(int i=0; i<colArrCnt[start->col]; ++i){
                    if(!colArr[start->col][i]->visit && colArr[start->col][i]->row < start->row){
                        if(tmp < colArr[start->col][i]->row){
                            tmp = colArr[start->col][i]->row;
                            vID = colArr[start->col][i]->pID;
                        }
                    }
                }
            }
            else
            {
                tmp = MAXN;

                for(int i=0; i<colArrCnt[start->col]; ++i){
                    if(!colArr[start->col][i]->visit && colArr[start->col][i]->row > start->row){
                        if(tmp > colArr[start->col][i]->row){
                            tmp = colArr[start->col][i]->row;
                            vID = colArr[start->col][i]->pID;
                        }
                    }
                }
            }
        }
        else if(dir == 2 || dir == 6)
        {
            if(dir == 2)
            {
                tmp = MAXN;

                for(int i=0; i<rowArrCnt[start->row]; ++i){
                    if(!rowArr[start->row][i]->visit && rowArr[start->row][i]->col > start->col){
                        if(tmp > rowArr[start->row][i]->col){
                            tmp = rowArr[start->row][i]->col;
                            vID = rowArr[start->row][i]->pID;
                        }
                    }
                }
            }
            else
            {
                tmp = -1;

                for(int i=0; i<rowArrCnt[start->row]; ++i){
                    if(!rowArr[start->row][i]->visit && rowArr[start->row][i]->col < start->col){
                        if(tmp < rowArr[start->row][i]->col){
                            tmp = rowArr[start->row][i]->col;
                            vID = rowArr[start->row][i]->pID;
                        }
                    }
                }
            }
        }
        else if(dir == 1 || dir == 5)
        {
            if(dir == 1)
            {
                tmp = -1;

                for(int i=0; i<ruArrCnt[start->row + start->col]; ++i){
                    if(!ruArr[start->row + start->col][i]->visit && ruArr[start->row + start->col][i]->row < start->row){
                        if(tmp < ruArr[start->row + start->col][i]->row){
                            tmp = ruArr[start->row + start->col][i]->row;
                            vID = ruArr[start->row + start->col][i]->pID;
                        }
                    }
                }
            }
            else
            {
                tmp = MAXN;

                for(int i=0; i<ruArrCnt[start->row + start->col]; ++i){
                    if(!ruArr[start->row + start->col][i]->visit && ruArr[start->row + start->col][i]->row > start->row){
                        if(tmp > ruArr[start->row + start->col][i]->row){
                            tmp = ruArr[start->row + start->col][i]->row;
                            vID = ruArr[start->row + start->col][i]->pID;
                        }
                    }
                }
            }
        }
        else if(dir == 3 || dir == 7)
        {
            if(dir == 3)
            {
                tmp = MAXN;

                for(int i=0; i<rdArrCnt[10000 + start->row - start->col]; ++i){
                    if(!rdArr[10000 + start->row - start->col][i]->visit && rdArr[10000 + start->row - start->col][i]->row > start->row){
                        if(tmp > rdArr[10000 + start->row - start->col][i]->row){
                            tmp = rdArr[10000 + start->row - start->col][i]->row;
                            vID = rdArr[10000 + start->row - start->col][i]->pID;
                        }
                    }
                }
            }
            else
            {
                tmp = -1;

                for(int i=0; i<rdArrCnt[10000 + start->row - start->col]; ++i){
                    if(!rdArr[10000 + start->row - start->col][i]->visit && rdArr[10000 + start->row - start->col][i]->row < start->row){
                        if(tmp < rdArr[10000 + start->row - start->col][i]->row){
                            tmp = rdArr[10000 + start->row - start->col][i]->row;
                            vID = rdArr[10000 + start->row - start->col][i]->pID;
                        }
                    }
                }
            }
        }

        visitList[i] = vID;
        user[uID].vList[user[uID].vListCnt++] = vID;
        start = &place[vID];
    }

    for(int i=0; i<visitNum; ++i)
        place[visitList[i]].visit = true;
}

void disinfectPlaces(int uID)
{
    for(int i=0; i<user[uID].vListCnt; ++i)
        place[user[uID].vList[i]].visit = false;
}