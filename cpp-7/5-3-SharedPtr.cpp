#include <iostream>


struct Expression
{


	Expression(const char*p=0){std::cout << "Expression()\n";}
	Expression(const Expression&){std::cout << "Expression(const Expression&)\n";}
	virtual ~Expression(){std::cout << "~Expression()\n";}
	Expression& operator=(const Expression&){std::cout << "Expression::operator=()\n";}
};

struct Number : Expression
{
        Number(){std::cout << "Number()\n";}
        Number(const Number&){std::cout << "Number(const Number&)\n";}
        ~Number(){std::cout << "~Number()\n";}
        Number& operator=(const Number&){std::cout << "Number::operator=()\n";}
};

struct BinaryOperation : Expression
{
        BinaryOperation(){std::cout << "BinaryOperation()\n";}
        BinaryOperation(const BinaryOperation&){std::cout << "BinaryOperation(const BinaryOperation&)\n";}
        ~BinaryOperation(){std::cout << "~BinaryOperation()\n";}
        BinaryOperation& operator=(const BinaryOperation&){std::cout << "BinaryOperation::operator=()\n";}
};


template<typename T>
void swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}


int nexid=0;

struct SharedPtr
{
    // реализуйте следующие методы
    //
    explicit SharedPtr(Expression *ptr = 0)
    :ptr(ptr), counter(nullptr), id(nexid++){
	if(ptr)
	{
	   counter = new int(1);
	   std::cout << "id:"<<id<<":" << ptr << "+:" << *counter << "\n";
	}
	else
	{
	   std::cout << "id:"<<id<<":" << ptr << "+:---\n";
	}
    }
    ~SharedPtr()
    	{
		if(counter){
			--*counter;
			std::cout << "id:"<<id<<":" << ptr << "-:" << *counter << "\n";
			if(*counter == 0)
			{
				delete ptr;
				delete counter;
			}
		}
		std::cout << "id:"<<id<<"~\n";
	}
    SharedPtr(const SharedPtr & other)
	:ptr(other.ptr), counter(other.counter),id(nexid++){
		if(counter)
		{
			++*counter;
			std::cout << "id:"<<id<<" from " << other.id<<":" << ptr << "+:" << *counter << "\n";
		}
		else
		{
			std::cout << "id:"<<id<<" from " << other.id <<":" << ptr << "+:---\n";
		}
		
	}
    SharedPtr& operator=(const SharedPtr &other)
	{
		std::cout << "id:"<<id<<": operator=\n";
		SharedPtr p(other);
		swap(this->ptr, p.ptr);
		swap(this->counter, p.counter);
		return *this;

	}
    Expression* get() const {return ptr;}
    void reset(Expression *other = 0)
	{
		std::cout << "id:"<<id<<": reset\n";
		SharedPtr p(other);
                swap(this->ptr, p.ptr);
                swap(this->counter, p.counter);
	}
    Expression& operator*() const {return *ptr;}
    Expression* operator->() const { return ptr;}

    Expression *ptr;
    int * counter;
    int id;
};

int main()
{
	std::cout << "=================START=========================\n";
{
	SharedPtr a(new Number());
	SharedPtr b1, b2;
	SharedPtr c(new BinaryOperation());
	SharedPtr d(c);
	a = a;
	b1 = b2;
	b1 = a;
	b1 = c;
	c.reset();
}
	std::cout << "=================FINISH========================\n";
}
