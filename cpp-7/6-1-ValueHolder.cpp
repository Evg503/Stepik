struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder : ICloneable
{

	ValueHolder(const T& data):data_(data){}
        ValueHolder * clone() const
	{
		ValueHolder * p = new ValueHolder(data_);
		return p;
	}
	T data_;
};


class Any
{
public:
	Any():ptr(nullptr){}
	template<typename T>
	Any(const T& t):ptr(new ValueHolder<T>(t)){}

	Any(const Any& other)
	{
		ptr = other.ptr?other.ptr->clone():nullptr;
	}

	Any& operator=(Any other)
	{
		auto tmp = other.ptr;
		other.ptr = ptr;
		ptr = tmp;
		return *this;
	}
	
	template<typename T>
	T* cast()
	{
		ValueHolder<T>* t = dynamic_cast<ValueHolder<T>*>(ptr);
		if(t) return &(t->data_);
		return nullptr;
	}
	
	~Any() {delete ptr;}

private:
	ICloneable *ptr;	
};

int main()
{
	Any empty;
	Any i(10);
	Any cpy(i);
	empty = cpy;
	empty = 0;

	int * pi = i.cast<int>();
	char* pc = i.cast<char>();
	Any empty2;
	int* pi2 = empty2.cast<int>();

}


