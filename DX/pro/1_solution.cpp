#include <cstring>
#define MAX_N 90010
#define MAX_HW 310
using namespace std;

struct Node{
	char data;
	Node* next;
	Node* prev;
};

bool notFirstStart;
int maxRow, maxCol, nodeCnt, rowCnt, nowRow, nowCol, lastRow, total;
int rowChar[MAX_HW][27], prevCount[27];
Node *head, *tail, *now, *rowStart[MAX_HW];
Node node[MAX_N];

void add(Node* ptr, char c)
{
	Node* tmp = &node[nodeCnt++];

	tmp->data = c;
	tmp->next = ptr->next; ptr->next = tmp;
	tmp->prev = ptr; tmp->next->prev = tmp;
}

void init(int H, int W, char mStr[])
{
	if(!notFirstStart)
	{
		head = new Node();
		tail = new Node();
	}

	head->next = tail; head->prev = nullptr;
	tail->prev = head; tail->next = nullptr;

	notFirstStart = true;

	maxRow = H; maxCol = W;
	nodeCnt = rowCnt = 1;
	nowRow = 0;
	total = 0;
	memset(rowChar, 0, sizeof(rowChar));
	memset(prevCount, 0, sizeof(prevCount));

	now = head;

	for(int i=0; mStr[i]; ++i)
	{
		add(now, mStr[i]);
		
		if(i % maxCol == 0)
		{
			++nowRow;
			rowStart[nowRow] = now;
		}

		now = now->next;
		++rowChar[nowRow][mStr[i] - 'a' + 1];
		++total;
	}

	lastRow = nowRow;

	now = head;
	nowRow = 1; nowCol = 1;
}

void insert(char mChar)
{
	add(now, mChar);
	now = now->next;
	++total;
	++rowChar[nowRow][mChar - 'a' + 1];
	++prevCount[mChar - 'a' + 1];
	
	for(int i=nowRow; i<lastRow; ++i)
	{
		--rowChar[i][rowStart[i+1]->data - 'a' + 1];
		++rowChar[i+1][rowStart[i+1]->data - 'a' + 1];
		rowStart[i+1] = rowStart[i+1]->prev;
	}

	if((total-1) % maxCol == 0)
	{
		++lastRow;
		rowStart[lastRow] = tail->prev->prev;
		
		--rowChar[lastRow-1][rowStart[lastRow]->next->data - 'a' + 1];
		++rowChar[lastRow][rowStart[lastRow]->next->data - 'a' + 1];
	}

	++nowCol;
	if(nowCol > maxCol)
	{
		++nowRow;
		nowCol = 1;
		memset(prevCount, 0, sizeof(prevCount));
	}
}

char moveCursor(int mRow, int mCol)
{
	nowRow = mRow; nowCol = mCol;

	if((mRow-1) * maxCol + mCol > total)
	{
		nowRow = total / maxCol + 1;
		nowCol = total % maxCol + 1;
	}

	if(nowRow > lastRow)
		rowStart[nowRow] = tail->prev;

	now = rowStart[nowRow];
	memset(prevCount, 0, sizeof(prevCount));

	for(int i=0; i<nowCol-1; ++i)
	{
		++prevCount[(now->next->data) - 'a' + 1];
		now = now->next;
	}

	if(now->next == tail) return '$';
	return now->next->data;
}

int countCharacter(char mChar)
{
	int ret = 0;

	for(int i=nowRow; i<=lastRow; ++i)
		ret += rowChar[i][mChar - 'a' + 1];
		
	return ret - prevCount[mChar - 'a' + 1];
}
