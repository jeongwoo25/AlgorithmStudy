#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node head, tail;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head.data = -1;
    tail.data = -1;
    head.next = &tail;
    tail.next = nullptr;
}

void addNode2Head(int data) 
{
    Node* newNode = getNode(data);
    Node* ptr = &head;

    newNode->next = ptr->next;
    ptr->next = newNode;

    return;
}

void addNode2Tail(int data) 
{
    Node* newNode = getNode(data);
    Node* ptr = &head;

    while(ptr->next)
    {
        if(ptr->next->data == -1)
            break;

        ptr = ptr->next;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;

    return;
}

void addNode2Num(int data, int num) 
{
    Node* newNode = getNode(data);
    Node* ptr = &head;

    int i;
    for(i=0; i<num-1; i++)
    {
        if(ptr->next->data == -1)
            break;

        ptr = ptr->next;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;

    return;
}

void removeNode(int data) 
{
    Node* ptr = &head;

    while(ptr->next)
    {
        if(ptr->next->data == data || ptr->next->data == -1)
            break;
        
        ptr = ptr->next;
    }
    
    if(ptr->next->data == data)
        ptr->next = ptr->next->next;

    return;
}

int getList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* ptr = &head;

    while(ptr->next->data != -1)
    {
        output[cnt++] = ptr->next->data;
        ptr = ptr->next;
    }

    return cnt;
}