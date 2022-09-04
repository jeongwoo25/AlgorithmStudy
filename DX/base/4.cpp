#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* prev;
    Node* next;
};

Node text[10000];
int nodeCnt = 0;

Node head, tail;

Node* makeNode(int _data)
{
    text[nodeCnt].data = _data;
    text[nodeCnt].prev = nullptr;
    text[nodeCnt].next = nullptr;
    return &text[nodeCnt++];
}

void addNode2Tail(int _data)
{
    Node* newNode = makeNode(_data);
    
    newNode->prev = tail.prev;
    tail.prev = newNode;
    newNode->prev->next = newNode;
    newNode->next = &tail;

    return;
}

Node* findNode(int _idx)
{
    Node* ptr = &head;

    for(int i=0; i<_idx; i++)
        ptr = ptr->next;

    return ptr;
}

void addNode2Next(Node* ptr, int _data)
{
    Node* newNode = makeNode(_data);

    newNode->next = ptr->next;
    ptr->next = newNode;
    newNode->next->prev = newNode;
    newNode->prev = ptr;

    return;
}

void removeNode(int _idx, int num)
{
    Node* front = findNode(_idx);
    Node* back = front;

    for(int i=0; i<num; i++)
        back = back->next;

    front->next = back->next;
    back->next->prev = front;

    return;
}

int main(int argc, char** argv)
{   
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);

	int test_case;
	int T = 10;
	freopen("4_input.txt", "r", stdin);
    
    int textLen, cmdLen;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << " ";

        nodeCnt = 0;
        head.data = -1; head.prev = nullptr; head.next = &tail;
        tail.data = -1; tail.prev = &head;   tail.next = nullptr;

        int pw;
        
        cin >> textLen;
        
        for(int i=0; i<textLen; i++)
        {
            cin >> pw;
            addNode2Tail(pw);
        }

        char type;
        int idx, num;
        Node* ptr;

        cin >> cmdLen;
        for(int i=0; i<cmdLen; i++)
        {
            cin >> type;

            if(type == 'I')
            {
                cin >> idx;
                ptr = findNode(idx);

                cin >> num;
                for(int i=0; i<num; i++)
                {
                    cin >> pw;
                    addNode2Next(ptr, pw);
                    ptr = ptr->next;
                }
            }
            else if(type == 'D')
            {
                cin >> idx >> num;
                removeNode(idx, num);
            }
            else if(type == 'A')
            {
                cin >> num;

                for(int i=0; i<num; i++)
                {
                    cin >> pw;
                    addNode2Tail(pw);
                }
            }
        }

        ptr = &head;
        for(int i=0; i<10; i++)
        {
            cout << ptr->next->data << " ";
            ptr = ptr->next;
        }
        cout << "\n";
	}

	return 0;
}