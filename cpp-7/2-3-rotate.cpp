
void swap(int &a, int& b)
{
	a^=b^=a^=b;
}

void flip(int*b, int* e)
{
	int * mid = b+ (e-b)/2;
	--e;
	for (;b<mid;++b,--e)
	{
		swap(*b, *e);
	}
}

void rotate(int a[], unsigned size, int shift)
{

	if(shift != 0)
	{
		shift = (shift+size) % size; 

		int* c = a+shift;
		int* e = a+size;


		flip(a, c);
		flip(c, e);
		flip(a, e);
	}

}

/* test area */
#include <cassert>
#include <iostream>

void print(const char* msg, int* b, int* e)
{
	std::cout << msg;
	for(int* i=b; i<e; ++i)
	{
		std::cout <<" " << *i;
	}
	std::cout << "\n";
}

int main()
{

	int a = 11;
	int b = 22;
	swap(a, b);
	assert(a == 22 && b == 11);

	{
		int a[]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		//print("a:", a, a+10);

		flip(a, a+2);
		//print("flip(a, a+2):", a, a+10);
		assert(a[0]==2);
		assert(a[1]==1);
		for(int i = 3; i < 10;++i)
			assert(a[i] == i+1);
	}

	{
                int a[]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                //print("a:", a, a+10);

                rotate(a,10,  12);

                //print("flip(a, a+2):", a, a+10);
                for(int i = 0; i < 10;++i)
                        assert(a[i] == (i+2)%10+1);

	}

}



