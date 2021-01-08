#include <iostream>
#include <cassert>

using namespace std;
int n;
const int maxn = 100000+5;
int D[maxn] = {};
char path[maxn] = {};

int k = 0;
int out[maxn] = {};

int calc()
{
	for (int i = 2; i <=n; ++i)
	{
		D[i] = D[i-1]+1;
		path[i] = '1';
		if(i%2 == 0)
		{
			if(D[i/2]+1<D[i])
			{
				D[i] = D[i/2]+1;
        		        path[i] = '2';
			}

		}
                if(i%3 == 0)
                {
                        if(D[i/3]+1<D[i])
                        {
                                D[i] = D[i/3]+1;
                                path[i] = '3';
                        }

                }
	}

	return D[n];
}

void pathfinder()
{
	int v = n;
	for (int i = k; i>=0; --i)
	{
		out[i] = v;
		if(path[v] == '1') v-=1;
                else if(path[v] == '2') v/=2;
		else if(path[v] == '3') v/=3;
		//else assert(path[v]*0 != 0);
	}
}
int main()
{
	cin >> n;
	
	k = calc();	
	
	cout << k << endl;
	
	pathfinder();
	for (int i = 0; i <= k; ++i)
	{
		cout << out[i] << ' ';
	}
}

