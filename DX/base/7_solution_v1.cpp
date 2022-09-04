#include <malloc.h>
#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;


Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head = (Node*)malloc(sizeof(Node*));
    head->data = -1;
    head->prev = nullptr;
    head->next = nullptr;
}

void addNode2Head(int data) 
{
    Node* newNode = getNode(data);
    Node* ptr = head;
    
    if(head->next)
    {
        newNode->next = head->next;
        newNode->next->prev = newNode;
    }
    
    head->next = newNode;
    newNode->prev = head;
    
    return;
}

void addNode2Tail(int data) 
{
    Node* newNode = getNode(data);
    Node* ptr = head;

    while(ptr->next)
        ptr = ptr->next;
        
    ptr->next = newNode;
    newNode->prev = ptr;

    return;
}

void addNode2Num(int data, int num) 
{
    Node* newNode = getNode(data);
    Node* ptr = head;

    for(int i=0; i<num-1; i++)
        ptr = ptr->next;

    if(ptr->next)
    {
        newNode->next = ptr->next;
        newNode->next->prev = newNode;
    }

    ptr->next = newNode;
    newNode->prev = ptr;

    return;
}

int findNode(int data) 
{
    int idx = 1;
    Node* ptr = head;

    while(ptr->next)
    {
        if(ptr->next->data == data)
            break;

        idx++;
        ptr = ptr->next;
    }

    return idx;
}

void removeNode(int data) 
{
    Node* ptr = head;

    while(ptr->next)
    {
        if(ptr->next->data == data)
        {
            if(ptr->next->next)
            {
                Node* tmp = ptr->next;

                ptr->next = tmp->next;
                tmp->next->prev = ptr;
                break;
            }
            else
            {
                ptr->next = nullptr;
                break;
            }
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

int getReversedList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* ptr = head;

    while(ptr->next)
        ptr = ptr->next;

    if(ptr->data != -1)
    {
        output[cnt++] = ptr->data;

        while(ptr->prev->data != -1)
        {
            output[cnt++] = ptr->prev->data;
            ptr = ptr->prev;
        }
    }

    return cnt;
}