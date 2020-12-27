#include <cstddef> // size_t
#include <cstring>

struct String {

    String(const char *str = "")
    {
        size = strlen(str);
        this->str = new char[size+1];
        strcpy(this->str, str);
    }

    /* Реализуйте этот конструктор */
	String(size_t n, char c):size(n)
    {
        str = new char[size+1];
        for(int i = 0; i < n;++i)
            str[i] = c;
        str[size] = 0;
    }

    /* и деструктор */
	~String()
    {
        delete[] str;
    }

    String(const String &other)
    {
        size = other.size;
        str = new char[size+1];
        strcpy(str, other.str);
    }

    String &operator=(const String &other)
    {
        if( this != &other)
        {
            size = other.size;
            delete[] str;
            str = new char[size+1];
            strcpy(str,other.str);
        }
        return *this;
    }

	void append(String &other)
    {
        size_t new_size = size + other.size;
        char* buff = new char [new_size+1];
        strcpy(buff, str);
        strcpy(buff+size, other.str);
        delete[] str;
        str = buff;
        size = new_size;
    }

	struct Proxy
	{
		int begin;
		const String& str;
		String operator[](int end) const
		{
			String r(end-begin, ' ');
			for (int i = begin; i< end; ++i)
				r.str[i-begin] = str.str[i];
			return r;
		}		
	};

	Proxy operator[](int start) const
	{
		return Proxy{start, *this};
	}
	size_t size;
	char *str;
};

#include <iostream>

int main()
{
String const hello("hello");
std::cout <<"hello:\"" << hello.str<<"\"\n";

String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
std::cout <<"hell:\"" << hell.str<<"\"\n";

String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
std::cout <<"ell:\"" << ell.str<<"\"\n";

}
