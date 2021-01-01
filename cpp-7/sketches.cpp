
struct Number {};

struct BigInt : Number
{
	BigInt(int x);
};

struct String
{
	explicit String(char const * s);
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
