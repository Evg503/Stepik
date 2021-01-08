#include <iostream>
#include <algorithm>
#include <vector>



int main()
{
	std::vector<int> v;

	int i;
	std::cin >> i;
	while(std::cin)
	{
		v.push_back(i);
		std::cin >> i;
	}
	std::sort(begin(v), end(v));

	for(auto n:v)
	{
		std::cout << n << " "; 
	}
}
