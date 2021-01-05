#include <tuple>


template< int ...N>
struct IntList;

template <int n, int ... N>
struct IntList<n, N...>
{
    static const int Head = n;
    using Tail = IntList<N...>;
};

template <>
struct IntList<>
{
};


template <int n, typename IL>
struct IntCons;

template <int N, int ... TAIL>
struct IntCons<N, IntList<TAIL...>>
{
    using type = IntList<N, TAIL...>;
};

// реализация метафункции Generate


template <int n, int s = 0>
struct Generate
{
    using type = typename IntCons<s, typename Generate<n, s+1>::type>::type;
};

template <int n>
struct Generate<n, n>
{
    using type = IntList<>;
};





template<typename L1, typename L2, template<int a, int b> typename F>
struct Zip
{
    using type = typename IntCons<F<L1::Head, L2::Head>::value, 
                    typename Zip<typename L1::Tail, typename L2::Tail, F>::type>::type;
};

template<template<int a, int b> typename F>
struct Zip< IntList<>,IntList<>, F>
{
      using type = IntList<>;  
};


template<int a, int b>
struct Plus
{
    static int const value = a + b;    
};

template<int a, int b>
struct Minus
{
    static int const value = a - b;    
};

template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
using Dimension = IntList<m, kg, s, A, K, mol, cd>;

template<typename Dimension>
struct Quantity
{
	Quantity():v(0.0){}
	explicit Quantity(double v):v(v){}
	double value()const {return v;}
	double v;
};

template<typename T>
Quantity<T> operator+(Quantity<T>const &lhs, Quantity<T>const &rhs)
{
	return Quantity<T>{lhs.value() + rhs.value()};
}

template<typename T>
Quantity<T> operator-(Quantity<T>const &lhs, Quantity<T>const &rhs)
{
        return Quantity<T>{lhs.value() - rhs.value()};
}

template<typename T>
Quantity<T> operator*(double lhs, Quantity<T>const &rhs)
{
        return Quantity<T>{lhs * rhs.value()};
}

template<typename T>
Quantity<T> operator*(Quantity<T>const &lhs, double rhs)
{
        return Quantity<T>{lhs.value() * rhs};
}

template<typename T>
Quantity<T> operator/(Quantity<T>const &lhs, double rhs)
{
        return Quantity<T>{lhs.value() / rhs};
}

template<typename T>
auto operator/(double lhs, Quantity<T>const &rhs) -> decltype(Quantity<Dimension<>>{lhs} / rhs)
{
        return Quantity<Dimension<>>{lhs} / rhs;
}



template<typename T1, typename T2>
Quantity<typename Zip<T1, T2, Plus>::type> operator*(Quantity<T1>const &lhs, Quantity<T2>const & rhs)
{
        return Quantity<typename Zip<T1, T2, Plus>::type>{lhs.value() * rhs.value()};
}

template<typename T1, typename T2>
Quantity<typename Zip<T1, T2, Minus>::type> operator/(Quantity<T1>const &lhs, Quantity<T2>const & rhs)
{
        return Quantity<typename Zip<T1, T2, Minus>::type>{lhs.value() / rhs.value()};
}


using NumberQ   = Quantity<Dimension<>>;          // число без размерности
using LengthQ   = Quantity<Dimension<1>>;          // метры
using MassQ     = Quantity<Dimension<0, 1>>;       // килограммы
using TimeQ     = Quantity<Dimension<0, 0, 1>>;    // секунды
using VelocityQ = Quantity<Dimension<1, 0, -1>>;   // метры в секунду
using AccelQ    = Quantity<Dimension<1, 0, -2>>;   // ускорение, метры в секунду в квадрате
using ForceQ    = Quantity<Dimension<1, 1, -2>>;   // сила в ньютонах

#include <cassert>
int main()
{
LengthQ   l{30000};      // 30 км
TimeQ     t{10 * 60};    // 10 минут
// вычисление скорости
VelocityQ v = l / t;     // результат типа VelocityQ, 50 м/с

AccelQ    a{9.8};        // ускорение свободного падения
MassQ     m{80};         // 80 кг
// сила притяжения, которая действует на тело массой 80 кг
ForceQ    f = m * a;     // результат типа ForceQ

VelocityQ v2 = 1 / t * l;     // результат типа VelocityQ, 50 м/с

assert(v.value() == v2.value());
assert((2*f).value() == (f+f+f-f).value());
}
