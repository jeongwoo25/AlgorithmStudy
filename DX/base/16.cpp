#include <iostream>

int L, N;
int sList[100000];
int timeList[100000];
int sumList[100000];

int findIdx(int sidx, int eidx, int len, int target)
{
	int retidx = eidx + 1;

	while(sidx <= eidx)
	{
		int midx = (sidx + eidx)/2;

		if(sList[midx] > target)
		{
			retidx = midx;
			eidx = midx - 1;
		}
		else sidx = midx + 1;
	}

	return retidx;
}

int solve(int sidx, int eidx, int len)
{
	int target = sList[sidx] + len - 1;
	int k = findIdx(sidx, eidx, len, target) - 1;

	int ret = 0;
	
	if(sidx > 0) ret = sumList[k-1] - sumList[sidx-1];
	else ret = sumList[k-1];

	int tmp = target - sList[k] + 1;

	if(tmp > timeList[k]) ret += timeList[k];
	else ret += tmp;

	return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("16_input.txt", "r", stdin);
	scanf("%d", &T);

	for(test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d", &L, &N);
		
		int sum = 0;
		for(int i=0; i<N; i++)
		{
			scanf("%d %d", &sList[i], &timeList[i]);
			timeList[i] -= sList[i];

			sum += timeList[i];
			sumList[i] = sum;
		}

		int max = 0;
		for(int i=0; i<N; i++)
		{
			int res = solve(i, N-1, L);
			max = res > max ? res : max;
		}

		printf("#%d %d\n", test_case, max);
	}

	return 0;
}