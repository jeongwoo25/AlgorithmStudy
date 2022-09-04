#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

Node nodeList[3000];
Node head, tail;
int nodeCnt = 0;

void init()
{
    nodeCnt = 0;
    head.data = -1; head.next = &tail;   head.prev = nullptr;
    tail.data = -1; tail.next = nullptr; tail.prev = &head;
}

Node* makeNode(int _data)
{
    nodeList[nodeCnt].data = _data;
    nodeList[nodeCnt].next = nullptr;
    nodeList[nodeCnt].prev = nullptr;
    return &nodeList[nodeCnt++];
}

void addNode2Tail(int _data)
{
    Node* newNode = makeNode(_data);

    newNode->next = &tail;
    tail.prev->next = newNode;
    newNode->prev = tail.prev;
    tail.prev = newNode;

    return;
}

Node* findNode(int _idx)
{
    Node* ptr = &head;

    for(int i=0; i<_idx; i++)
    {
        if(ptr->next->data == -1)
            break;
        
        ptr = ptr->next;
    }
    
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

void removeNode(Node* ptr)
{
    Node* mid = ptr->next;

    ptr->next = mid->next;
    mid->next->prev = ptr;

    return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("5_input.txt", "r", stdin);
	cin >> T;
    
    int len, edit, idxPrint, _data;
    char type;

	for(test_case = 1; test_case <= T; ++test_case)
    {
        cout << "#" << test_case << " ";

        init();
        cin >> len >> edit >> idxPrint;

        for(int i=0; i<len; i++)
        {
            cin >> _data;
            addNode2Tail(_data);
        }

        int idx, num;
        Node* ptr;

        for(int i=0; i<edit; i++)
        {
            cin >> type;

            if(type == 'I')
            {
                cin >> idx >> num;
                ptr = findNode(idx);
                addNode2Next(ptr, num);
            }
            else if(type == 'D')
            {
                cin >> idx;
                ptr = findNode(idx);
                removeNode(ptr);
            }
            else if(type == 'C')
            {
                cin >> idx >> num;
                ptr = findNode(idx);
                ptr->next->data = num;
            }
        }

        ptr = findNode(idxPrint);
        cout << ptr->next->data << "\n";
	}

	return 0;
}