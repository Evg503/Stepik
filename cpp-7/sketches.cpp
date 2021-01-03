#include <iostream>

/*
struct Number {};

struct BigInt : Number
{
	BigInt(int x);
};

struct String
{
	explicit String(char const * s);
	explicit operator char const *() const;
};


void a()
{
int a = 3.5;
double b = 7;
BigInt c = 100500;
String d = static_cast<String>("Stepik");
Number * e = &c;
BigInt * f = static_cast<BigInt *>(e);
void * g = f;
BigInt * h = static_cast<BigInt *>(g); 

}

void f2()
{
int a = 27;
int const b = 412;
int * pa = &a;

int const c = a;
int d = b;//const_cast<int &>(b);
int const * p1 = pa;//const_cast<int const *>(pa);
int * const * p2 = &pa;
int const ** p3 = const_cast<int const **>(&pa);
int const * const * p4 = &pa;//const_cast<int const * const *>(&pa); 
}


void f3()

{
String s("Hello");

//delete s;    // 1

//if (s) { }   // 2

//char const * p1 = s;  // 3

char const * p2 = (char const*)s;  // 4

char const * p3 = static_cast<char const*>(s);  // 5

//char const * s2 = s + 4;  // 6
}
*/
struct Str
{
	Str()=default;
	Str(Str const &)=default;
	Str(Str &&) 
	{
		std::cout << "Str(Str &&)" << std::endl;
	}; 
};

Str & fun1(Str & s)
{
    return s;
}

Str && fun2(Str & s)
{
    return std::move(s);
}

Str fun3(Str & s)
{
    return std::move(s);
}

Str fun4(Str s)
{
    return std::move(s);
}

Str fun5(Str s)
{
    return std::forward<Str>(s);
}

Str && fun6(Str && s)
{
    return std::move(s);
}

Str fun7(Str && s)
{
    return s;
}
int mainfun()
{
	Str s;

	std:: cout << "\nfun1:";
	fun1(s);
	std:: cout << "\nfun2:";
	fun2(s);
	std:: cout << "\nfun3:";
	fun3(s);
	std:: cout << "\nfun4:";
	fun4(s);
	std:: cout << "\nfun5:";
	fun5(s);
	std:: cout << "\nfun6:";
	fun6(Str());
	std:: cout << "\nfun7:";
	fun7(Str());
}

#include <list>
int mainlists()
{
std::list<int> l = {1,2,3};
l.insert(l.begin(), 4);
l.insert(l.end(), 5);

auto it = l.begin();
++it;
++it;

l.insert(it, 6);

auto rit1 = l.rbegin();
++rit1;
++rit1;
l.insert(rit1.base(), 7);

auto rit2 = l.rbegin();
++rit2;
++rit2;
l.insert(rit2.base(), 8);

for(auto i:l)
	std::cout << i << ' ';

}

template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    FwdIt i = p;
    for(; p != q; --n)
    {
        if(n==0)
        {
            ++p;
            continue;
        }
        *i++ = *p++;
    }
    return i;
}

#include <vector>
int main_remove_nth(){
std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
for(auto i:v)
        std::cout << i << ' ';
std::cout <<std::endl;

v.erase(remove_nth(v.begin(), v.end(), 11), v.end());
// теперь в v = {0,1,2,3,4,6,7,8,9,10};

for(auto i:v)
        std::cout << i << ' ';
std::cout <<std::endl;
}


struct ElementN 
{
    explicit ElementN(size_t n)
        : n(n), i(0)
    {}    

    template<class T>    
    bool operator()(T const& t) { return (i++ == n); }
    
    size_t n;
    size_t i;
};

#include <algorithm>

int mainElementN()
{
    std::vector<int> v = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };

    v.erase(std::remove_if(v.begin(), v.end(), ElementN(3)), v.end());

    for (int i: v)
        std::cout << i << ' ';

    return 0;
}
#include <algorithm>
#include <vector>

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    using T = typename std::iterator_traits<Iterator>::value_type;
    size_t count = 0;
    std::vector<T> v(p,q);
    auto b = v.begin();
    auto e = v.end();
    std::sort(b, e);
    do{
        if(std::adjacent_find(b, e) == e) ++count;
    }while(std::next_permutation(b, e));
    return count;
}

#include <array>

int main()
{
std::array<int, 3> a1 = {1,2,3};
size_t c1 = count_permutations(a1.begin(), a1.end()); // 6

std::cout << "c1(6)=" << c1 <<std::endl;


std::array<int, 5> a2 = {1,2,3,4,4};
size_t c2 = count_permutations(a2.begin(), a2.end()); // 36

std::cout << "c2(36)=" << c2 <<std::endl;

}
