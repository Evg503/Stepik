#include <cstddef>
#include <new>

template <typename T>
class Array
{
public:
     explicit Array(size_t size, const T& value = T())
	:len(size)
	{
		data = new char[len * sizeof(T)];
		for(int i = 0; i < len; ++i)
			new (&data[i * sizeof(T)]) T(value);		
	}
    
    Array(const Array &other): len(other.len)
    {
               data = new char[len * sizeof(T)];
                for(int i = 0; i < len; ++i)
                        new (&data[i * sizeof(T)]) T(other[i]); 
    }

    Array():len(0), data(0){}

    ~Array()
    {
        for(int i = 0; i < len; ++i)
		(*this)[i].~T();

	delete[] data;
    }

    Array& operator=(Array other)
    {
	// swap data;
	char *tmp = data;
        data = other.data;
        other.data = tmp;
	
	size_t s = len;
        len = other.len;
	other.len = s;
    }

    size_t size() const {return len;}
   

    T& operator[](size_t n) {return *(T*)(data+n * sizeof(T));}

    const T& operator[](size_t n) const {return *(const T*)(data+n * sizeof(T));}

private:
	size_t len;
	char* data;
};


#include <iostream>

template<typename T>
void print(const char* msg, T a)
{
	std::cout <<msg << a.size() << ":";
	for(int i = 0; i<a.size();++i)
		std:: cout << a[i] << " ";
	std::cout << std::endl;
}
int main()
{
	Array<int> a(10, 1);
	print<Array<int>&> ("Array<int>& a", a);
	print<const Array<int>&> ("const Array<int>& a", a);
	print<Array<int>> ("Array<int> a", a);
	Array<Array<int>> b(12);

	b[1] = a;
	a[3] = 3;
	b[0] = a;
	b[0] = b[0];

        std::cout <<a.size() <<"\n";
        std::cout <<b.size() <<"\n";
	std::cout <<b[0].size() <<"\n";
	std::cout <<b[1].size() <<"\n";
	std::cout << b[0][3]<<b[1][3] << a[0]<<a[3]<<"\n";
}
