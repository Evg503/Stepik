#include <string>
#include <sstream>
#include <exception>
#include <cassert>


// описание класса исключения bad_from_string
class bad_from_string : public std::exception
{
    public:
	bad_from_string(std::string const & msg):msg(msg){}
        const char * what() const noexcept override
        {
            return msg.c_str();
        }
	std::string msg;
};
// функция from_string
template<class T>
T from_string(std::string const& s)
{
    T t;
    std::istringstream in(s);
    in >> std::noskipws >> t;
    if ((in.eof() || in.peek() == EOF)  && !in.fail() && !in.bad())
        return t;
    throw bad_from_string(s);
    
    // реализация
}

#include <iostream>
int main()
{
std::string s1("123");
try{
int    a1 = from_string<int>   (s1); // a1 = 123
double b1 = from_string<double>(s1); // b1 = 123.0
std::string c1 = from_string<std::string>(s1); // c1 = "123"
} catch(...)
{
	std::cout << "unexpected exception" << std::endl;
}
std::string s2("12.3");
try{
try{
int    a2 = from_string<int>   (s2); // исключение
}catch(std::exception &e)
{
	std::cout << "expected x3 from from_string<int>:" << e.what() << std::endl;
}
double b2 = from_string<double>(s2); // b2 = 12.3
std::string c2 = from_string<std::string>(s2); // c2 = "12.3"
} catch(...)
{
        std::cout << "unexpected exception" << std::endl;
}

std::string s3("abc");
try{
try{
int    a3 = from_string<int>   (s3); // исключение
}catch(std::exception &e)
{
        std::cout << "expected x3 from from_string<int>:" << e.what() << std::endl;
}
try{
double b3 = from_string<double>(s3); // исключение
}catch(std::exception &e)
{
        std::cout << "expected x3 from from_string<double>:" << e.what() << std::endl;
}
std::string c3 = from_string<std::string>(s3); // c3 = "abc"
} catch(...)
{
        std::cout << "unexpected exception" << std::endl;
}

try{
char    c1 = from_string<char>   ("c");
assert (c1 == 'c');
char    c2 = from_string<char>   (" "); 
assert (c2 == ' ');
char    c3 = from_string<char>   ("x3"); // исключение
assert (c3 == 257); // not executed
}catch(std::exception &e)
{
        std::cout << "expected x3 from from_string<char>:" << e.what() << std::endl;
}


}
