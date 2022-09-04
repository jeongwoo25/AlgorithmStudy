#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#define MAXN 1001
using namespace std;

struct Node{
    int num;
    char key;
    Node* leftChild;
    Node* rightChild;
};

int N;
Node nodeList[MAXN];
Node tail;

double calculate(double op1, double op2, char c)
{
    if(c == '+') return op1 + op2;
    else if(c == '-') return op1 - op2;
    else if(c == '*') return op1 * op2;
    else return op1 / op2;
}

double traverse(Node* cur)
{
    if(cur->leftChild->num == -1)
        return cur->num;
    
    double op1 = traverse(cur->leftChild);
    double op2 = traverse(cur->rightChild);
    double result = calculate(op1, op2, cur->key);

    return result;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("28_input.txt", "r", stdin);
    
    tail.key = '!';
    tail.num = -1;
    tail.leftChild = nullptr;
    tail.rightChild = nullptr;

    int idx, num, left, right;
    char op;
    string str;
    string strBuffer;
    vector<string> strList;

	for(test_case = 1; test_case <= 10; ++test_case)
	{
        cin >> N;
        cin.ignore();

        for(int i=0; i<N; ++i)
        {
            getline(cin, str);
            istringstream ss(str);
            while(getline(ss, strBuffer, ' '))
                strList.push_back(strBuffer);
            
            if(strList.size() == 2)
            {
                idx = stoi(strList.at(0));
                num = stoi(strList.at(1));
                nodeList[idx].num = num;
                nodeList[idx].leftChild = &tail;
                nodeList[idx].rightChild = &tail;
            }
            else
            {
                idx = stoi(strList.at(0));
                strcpy(&op, strList.at(1).c_str());
                left = stoi(strList.at(2));
                right = stoi(strList.at(3));

                nodeList[idx].key = op;
                nodeList[idx].leftChild = &nodeList[left];
                nodeList[idx].rightChild = &nodeList[right];
            }

            strList.clear();
        }

        int res = traverse(&nodeList[1]);
        cout << "#" << test_case << " " << res << "\n";
	}

	return 0;
}