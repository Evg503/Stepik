#include <iostream>
#include <cassert>

using namespace std;
const int maxn = 105;

const int empty = 0x7ffffff;

int n;
int a[maxn];
int D[maxn];

int stair(int i)
{
	if(D[i] == empty) 
	{
		D[i] = a[i] + max(stair(i-1), stair(i-2));
	}

	return D[i];

	
}

int main()
{
	cin >> n;
	assert(1<=n);
	assert(n<=100);
	a[0] = 0;
	D[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		D[i] = empty;
		cin >> a[i];
		assert(-10000 <= a[i]);
		assert(a[i] <= 10000);
	}
	D[1]=a[1]; // Base of recursion 0, a[1]

	cout << stair(n);
		
}
