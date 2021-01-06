#include <iostream>
#include <cassert>

int W;
int n;

const int maxW = 1005;
const int maxn = 305;
int D[maxW][maxn];
int gold[maxn];

void init_D()
{
	for(int w = 0; w<maxW; ++w)
		for(int i =0; i<maxn; ++i)
			D[w][i] = w*i==0?0:-1;
}

int backpack(int w, int i)
{
	if ( w <=0 || i<=0) return 0;
	if (D[w][i] ==-1)
	{
		D[w][i]=backpack(w, i-1);
		if(w>=gold[i])
			D[w][i]=std::max(backpack(w-gold[i], i-1)+gold[i], D[w][i]);
	}
	return D[w][i];
}

int main() {

	std::cin >> W >> n;
	assert(W<maxW);
	assert(n<maxn);
	for (int i = 1; i<=n; ++i)
		std::cin >> gold[i];

	init_D();
	std::cout<< backpack(W, n);

	return 0;
}

