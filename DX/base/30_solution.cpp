#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX 50010

struct Node{
    char pathName[NAME_MAXLEN + 1];
    int childCnt;
    int findRet;
    int id;
    Node* parent;
};

bool notFirstStart;
int memPoolCnt;
Node *root, *curr;
Node memPool[MAX];
Node child[MAX][31];

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}
int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}
int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

Node* makeNode(char name[NAME_MAXLEN + 1])
{
    mstrcpy(memPool[memPoolCnt].pathName, name);
    memPool[memPoolCnt].childCnt = 0;
    memPool[memPoolCnt].findRet = 0;
    memPool[memPoolCnt].id = memPoolCnt;
    
    return &memPool[memPoolCnt++];
}

Node* findPath(char path[PATH_MAXLEN])
{
    int len = mstrlen(path);
    curr = root;

    int j=0;
    char nowPath[NAME_MAXLEN + 1];
    
    for(int i=1; i<=len; ++i)
    {
        if(path[i] == '/')
        {
            nowPath[j] = '\0';

            for(int i=0; i<curr->childCnt; ++i)
            {
                if(mstrcmp(child[curr->id][i].pathName, nowPath) == 0)
                {
                    curr = &memPool[child[curr->id][i].id];
                    break;
                }
            }

            j = 0;
        }
        else nowPath[j++] = path[i];
    }
    
    return curr;
}

void init(int n)
{
    if(!notFirstStart)
        root = new Node();

    notFirstStart = true;

    memPoolCnt = 1;
    root->childCnt = 0;
    root->findRet = 0;
    root->id = 0;
    root->pathName[0] = '/';
    root->parent = nullptr;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1])
{
    Node* now = findPath(path);
    Node* newNode = makeNode(name);

    newNode->parent = now;
    child[now->id][now->childCnt++] = *newNode;

    while(now->parent)
    {
        ++now->findRet;
        now = now->parent;
    }

    ++root->findRet;
}

void cmd_rm(char path[PATH_MAXLEN + 1])
{
    Node* now = findPath(path);
    
    int sub = now->findRet + 1;

    char rmName[NAME_MAXLEN + 1];
    mstrcpy(rmName, now->pathName);

    now = now->parent;

    for(int i=0; i<now->childCnt; ++i)
    {
        if(mstrcmp(child[now->id][i].pathName, rmName) == 0)
        {
            for(int j=i; j<now->childCnt - 1; ++j)
                child[now->id][j] = child[now->id][j+1];
            break;
        }
    }
    
    --now->childCnt;

    while(now->parent)
    {
        now->findRet -= sub;
        now = now->parent;
    }

    root->findRet -= sub;
}

void copyTree(Node* parNode, Node* copyNode)
{
    Node* newNode = makeNode(copyNode->pathName);
    
    mstrcpy(newNode->pathName, copyNode->pathName);
    newNode->findRet = copyNode->findRet;

    newNode->parent = parNode;
    
    for(int i=0; i<copyNode->childCnt; ++i)
        copyTree(newNode, &memPool[child[copyNode->id][i].id]);

    child[parNode->id][parNode->childCnt++] = *newNode;
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
    Node* par = findPath(dstPath);
    Node* copyNode = findPath(srcPath);

    Node* newNode = makeNode(copyNode->pathName);

    mstrcpy(newNode->pathName, copyNode->pathName);
    newNode->findRet = copyNode->findRet;
    newNode->parent = par;
    
    for(int i=0; i<copyNode->childCnt; ++i)
        copyTree(newNode, &memPool[child[copyNode->id][i].id]);

    child[par->id][par->childCnt++] = *newNode;

    int inc = newNode->findRet + 1;

    while(par->parent)
    {
        par->findRet += inc;
        par = par->parent;
    }

    root->findRet += inc;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1])
{
    Node* par = findPath(dstPath);
    Node* mvNode = findPath(srcPath);
    
    cmd_rm(srcPath);

    mvNode->parent = par;
    child[par->id][par->childCnt++] = *mvNode;

    int inc = mvNode->findRet + 1;

    while(par->parent)
    {
        par->findRet += inc;
        par = par->parent;
    }

    root->findRet += inc;
}

int cmd_find(char path[PATH_MAXLEN + 1])
{
    Node* now = findPath(path);
    return now->findRet;
}