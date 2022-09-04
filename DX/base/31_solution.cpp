#define MAXN 100010

typedef struct _Heap{
    int id;
    int income;
}heapNode;

int heapSize, heapCopySize;
heapNode heap[MAXN];
heapNode heapcopy[MAXN];

void swap(heapNode* x, heapNode* y)
{
    heapNode tmp = *x;
    *x = *y;
    *y = tmp;
}

void init()
{
    heapSize = 1;
}

void addUser(int uID, int height) 
{
    heap[heapSize].id = uID;
    heap[heapSize].income = height;

    int current = heapSize;
    while(current > 1 && heap[current].income >= heap[current >> 1].income)
    {
        if(heap[current].income == heap[current >> 1].income)
        {
            if(heap[current].id < heap[current >> 1].id)
            {
                swap(&heap[current], &heap[current >> 1]);
                current = current >> 1;
            }
            else break;
        }
        else
        {
            swap(&heap[current], &heap[current >> 1]);
            current = current >> 1;
        }
    }

    ++heapSize;
}

int popUser()
{
    if(heapCopySize == 1)
        return -1;
    
    int ret = heapcopy[1].id;
    heapcopy[1] = heapcopy[--heapCopySize];

    int current = 1;

    while((current << 1) <= heapCopySize - 1)
    {
        if((current << 1) + 1 <= heapCopySize - 1)
        {
            heapNode priorNode;

            if(heapcopy[current << 1].income > heapcopy[(current << 1) + 1].income)
                priorNode = heapcopy[current << 1];
            else if(heapcopy[current << 1].income < heapcopy[(current << 1) + 1].income)
                priorNode = heapcopy[(current << 1) + 1];
            else
            {
                if(heapcopy[current << 1].id < heapcopy[(current << 1) + 1].id)
                    priorNode = heapcopy[current << 1];
                else priorNode = heapcopy[(current << 1) + 1];
            }

            if(heapcopy[current].income < priorNode.income)
            {
                if(priorNode.id == heapcopy[current << 1].id)
                {
                    swap(&heapcopy[current], &heapcopy[current << 1]);
                    current = current << 1;
                }
                else
                {
                    swap(&heapcopy[current], &heapcopy[(current << 1) + 1]);
                    current = (current << 1) + 1;
                }
            }
            else if(heapcopy[current].income == priorNode.income)
            {
                if(heapcopy[current].id > priorNode.id)
                {
                    if(priorNode.id == heapcopy[current << 1].id)
                    {
                        swap(&heapcopy[current], &heapcopy[current << 1]);
                        current = current << 1;
                    }
                    else
                    {
                        swap(&heapcopy[current], &heapcopy[(current << 1) + 1]);
                        current = (current << 1) + 1;
                    }
                }
                else break;
            }
            else break;
        }
        else
        {
            if(heapcopy[current].income < heapcopy[current << 1].income)
            {
                swap(&heapcopy[current], &heapcopy[current << 1]);
                current = current << 1;
            }
            else if(heapcopy[current].income == heapcopy[current << 1].income)
            {
                if(heapcopy[current].id > heapcopy[current << 1].id)
                {
                    swap(&heapcopy[current], &heapcopy[current << 1]);
                    current = current << 1;
                }
            }
            else break;
        }
    }

    return ret;
}

int getTop10(int result[10]) 
{
    heapCopySize = heapSize;

    for(int i=1; i<heapSize; ++i)
        heapcopy[i] = heap[i];
    
    int numRes = 0;

    while(numRes < 10)
    {
        int pop = popUser();
        
        if(pop == -1) break;
        result[numRes++] = pop;
    }
    
    return numRes;
}