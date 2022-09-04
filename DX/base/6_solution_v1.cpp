#include <malloc.h>
#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head = (Node*)malloc(sizeof(Node*));
    head->data = -1;
    head->next = nullptr;
}

void addNode2Head(int data) 
{
    Node* newNode = getNode(data);
    
    newNode->next = head->next;
    head->next = newNode;

    return;
}

void addNode2Tail(int data) 
{
    Node* ptr = head;
    Node* newNode = getNode(data);

    while(ptr->next)
        ptr = ptr->next;

    ptr->next = newNode;
    return;
}

void addNode2Num(int data, int num) 
{
    Node* ptr = head;
    Node* newNode = getNode(data);

    for(int i=0; i<num-1; i++)
        ptr = ptr->next;

    newNode->next = ptr->next;
    ptr->next = newNode;

    return;
}

void removeNode(int data) 
{
    Node* ptr = head;

    while(ptr->next)
    {
        if(ptr->next->data == data)
        {
            ptr->next = ptr->next->next;
            break;
        }

        ptr = ptr->next;
    }
    
    return;
}

int getList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* ptr = head;

    while(ptr->next)
    {
        output[cnt++] = ptr->next->data;
        ptr = ptr->next;
    }

    return cnt;
}