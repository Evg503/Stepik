#include <iostream>

// базовый класс фигуры (полиморфный)
struct Shape { 
	Shape(const char*s):s(s){};
	virtual ~Shape(){};
	const char* s;
 };

// прямоугольник
struct Rectangle : Shape 
{
	Rectangle(const char*s):Shape(s){};
};

// треугольник
struct Triangle : Shape 
{
	Triangle(const char*s):Shape(s){}; 
};

// функция для проверки пересечения двух прямоугольников
bool is_intersect_r_r(Shape * a, Shape * b)
{
	std::cout << "is_intersect_r_r(" << a->s << ", " << b->s << ")\n";	
}

// функция для проверки пересечения прямоугольника и треугольника
bool is_intersect_r_t(Shape * a, Shape * b)
{
        std::cout << "is_intersect_r_t(" << a->s << ", " << b->s << ")\n"; 
}


#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>

// Base - базовый класс иерархии
// Result - тип возвращаемого значения мультиметода
// Commutative - флаг, который показывает, что
// мультиметод коммутативный (т.е. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
	using Func = std::function<Result (Base *, Base*)>;
    // устанавливает реализацию мультиметода
    // для типов t1 и t2 заданных через typeid 
    // f - это функция или функциональный объект
    // принимающий два указателя на Base 
    // и возвращающий значение типа Result
    void addImpl( std::type_index t1, std::type_index t2, Func f )
    {
	table[t1][t2] = f;
	if(Commutative && t1 != t2)
		table[t2][t1] = [f](Base *p1, Base *p2){return f(p2, p1);}; 
    }

    // проверяет, есть ли реализация мультиметода
    // для типов объектов a и b
    bool hasImpl(Base * a, Base * b) const
    {
        // возвращает true, если реализация есть
        // если операция коммутативная, то нужно 
        // проверить есть ли реализация для b и а 
	
        return !!table[typeid(*a)][typeid(*b)]; 
    }

    // Применяет мультиметод к объектам
    // по указателям a и b
    Result call(Base * a, Base * b) const
    {
        // возвращает результат применения реализации
        // мультиметода к a и b
        return table[typeid(*a)][typeid(*b)](a, b);
    }
    mutable std::map<std::type_index, std::map<std::type_index, Func>> table;
};

int main() 
{
    // мультиметод для наследников Shape
    // возращающий bool и являющийся коммутативным 
    Multimethod2<Shape, bool, true> is_intersect;

    // добавляем реализацию мультиметода для двух прямоугольников
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    // добавляем реализацию мультиметода для прямоугольника и треугольника
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // создаём две фигуры    
    Shape * s1 = new Triangle("Triangle s1");
    Shape * s2 = new Rectangle("Rectangle s2");

    // проверяем, что реализация для s1 и s2 есть
    if (is_intersect.hasImpl(s1, s2))
    {
         // вызывается функция is_intersect_r_t(s2, s1)
         bool res = is_intersect.call(s1, s2);

         // Замечание: is_intersect_r_t ожидает,
         // что первым аргументом будет прямоугольник
         // а вторым треугольник, а здесь аргументы
         // передаются в обратном порядке. 
         // ваша реализация должна самостоятельно 
         // об этом позаботиться
    }
}


