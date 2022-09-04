#include <iostream>
#define MAXN 201
using namespace std;

struct Node{
    int id;
    char key;
    Node* leftChild;
    Node* rightChild;
};

bool isNum(char c)
{
    if('0' <= c && c <= '9') return true;
    else return false;
}

int N, numLeaf;
Node nodeList[MAXN];
Node tail;

int traverse(Node* cur)
{
    int check;
    
    if(cur->leftChild->id == -1)
    {
        if(isNum(cur->key)) return 1;
        else return 0;
    }
    
    check = traverse(cur->leftChild);
    if(!check) return 0;
    
    check = traverse(cur->rightChild);
    if(!check) return 0;
    
    if(isNum(cur->key)) return 0;
    else return 1;
    
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("27_input.txt", "r", stdin);
    
    int idx, left, right;
    char c;

    tail.id = -1;
    tail.leftChild = nullptr;
    tail.rightChild = nullptr;

	for(test_case = 1; test_case <= 10; ++test_case)
	{
        cin >> N;

        for(int i=0; i<(N-1)/2; ++i)
        {
            cin >> idx >> c >> left >> right;
            nodeList[idx].id = idx;
            nodeList[idx].key = c;
            nodeList[idx].leftChild = &nodeList[left];
            nodeList[idx].rightChild = &nodeList[right];
        }

        numLeaf = N - (N-1)/2;

        if(!(N & 1))
        {
            cin >> idx >> c >> left;
            nodeList[idx].id = idx;
            nodeList[idx].key = c;
            nodeList[idx].leftChild = &nodeList[left];
            nodeList[idx].rightChild = &tail;
            --numLeaf;
        }

        for(int i=0; i<numLeaf; ++i)
        {
            cin >> idx >> c;
            nodeList[idx].id = idx;
            nodeList[idx].key = c;
            nodeList[idx].leftChild = &tail;
            nodeList[idx].rightChild = &tail;
        }

        int res = traverse(&nodeList[1]);
        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}