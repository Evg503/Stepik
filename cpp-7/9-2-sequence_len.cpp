#include <cstddef>

template<class It>
size_t max_increasing_len(It p, It q)
{
    size_t md = 0;
    size_t d = 0;
    It prev = p;
    if(p != q) d = 1;
    for(It i = p; i != q; ++i)
    {
        md = md<d?d:md;      
	if (*i > *prev)
		++d;
        else 
        	d=1;
        md = md<d?d:md;
	prev = i;
    }
    return md;
}

#include <list>
#include <cassert>
#include <iostream>

int main()
{
std::list<int> const l1 = {7,8,9,4,5,6,1,2,3,4};
size_t len1 = max_increasing_len(l1.begin(), l1.end()); // 4, соответствует подотрезку 1,2,3,4
std::cout << "len1=" << len1 << std::endl;

std::list<int> const l2 = {-3,-2,-1,0,0,1,2,3,4,5};
size_t len2 = max_increasing_len(l2.begin(), l2.end()); // 6, соответствует подотрезку 0,1,2,3,4,5
std::cout << "len2=" << len2 << std::endl;
assert(len1 == 4);
assert(len2 == 6);
std::list<int> const l3 = {};
size_t len3 = max_increasing_len(l3.begin(), l3.end()); // 0
std::cout << "len3=" << len3 << std::endl;
}
