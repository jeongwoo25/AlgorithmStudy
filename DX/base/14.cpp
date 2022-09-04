#include <iostream>
#include <string>
using namespace std;

void merge(string* strList, int start, int mid, int end)
{
    int i=start, j=mid+1, k=0;
    string* buf = new string[end-start+1];

    while(i<=mid && j<=end)
    {
        if(strList[i].length() < strList[j].length())
            buf[k++] = strList[i++];
        else if(strList[i].length() > strList[j].length())
            buf[k++] = strList[j++];
        else
        {
            if(strList[i].compare(strList[j]) <= 0)
                buf[k++] = strList[i++];
            else buf[k++] = strList[j++];
        }
    }
    while(i<=mid)
        buf[k++] = strList[i++];
    while(j<=end)
        buf[k++] = strList[j++];

    for(int i=start, k=0; i<=end; i++, k++)
        strList[i] = buf[k];

    delete[] buf;
}

void mergeSort(string* strList, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(strList, start, mid);
        mergeSort(strList, mid+1, end);
        merge(strList, start, mid, end);
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("14_input.txt", "r", stdin);
	cin >> T;

    string str;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#" << test_case << "\n";

        int N;
        cin >> N;
        
        string* strList = new string[N];
        for(int i=0; i<N; i++)
            cin >> strList[i];

        mergeSort(strList, 0, N-1);

        cout << strList[0] << "\n";
        for(int i=1; i<N; i++)
            if(strList[i].compare(strList[i-1]) != 0)
                cout << strList[i] << "\n";

        delete[] strList;
	}

	return 0;
}