#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node head, tail;


Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head.data = -1;      tail.data = -1;
    head.prev = nullptr; tail.prev = &head;
    head.next = &tail;   tail.next = nullptr;
}

void addNode2Head(int data) 
{
    Node* newNode = getNode(data);
    
    newNode->next = head.next;
    head.next = newNode;
    newNode->next->prev = newNode;
    newNode->prev = &head;
}

void addNode2Tail(int data) 
{
    Node* newNode = getNode(data);
    
    newNode->prev = tail.prev;
    tail.prev = newNode;
    newNode->prev->next = newNode;
    newNode->next = &tail;
}

void addNode2Num(int data, int num) 
{
    Node* newNode = getNode(data);
    Node* ptr = &head;
    
    for(int i=0; i<num-1; i++)
        ptr = ptr->next;

    newNode->next = ptr->next;
    ptr->next = newNode;
    newNode->next->prev = newNode;
    newNode->prev = ptr;
}

int findNode(int data) 
{
    int idx = 1;
    Node* ptr = &head;

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
    Node* ptr = &head;

    while(ptr->next)
    {
        if(ptr->next->data == data)
        {
            Node* tmp = ptr->next;

            ptr->next = tmp->next;
            tmp->next->prev = ptr;
        }

        ptr = ptr->next;
    }
    
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

int getReversedList(int output[MAX_NODE]) 
{
    int cnt = 0;
    Node* ptr = &tail;
    
    while(ptr->prev->data != -1)
    {
        output[cnt++] = ptr->prev->data;
        ptr = ptr->prev;
    }

    return cnt;
}