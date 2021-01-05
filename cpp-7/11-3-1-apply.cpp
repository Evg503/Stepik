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

template<typename F, typename T, int ... Ints>
auto apply_impl(F f, T t, IntList<Ints...>) -> decltype( f(std::get<(Ints)>(t)...) )
{
        return f(std::get<(Ints)>(t)...);
}

template<typename F, typename ... Args>
auto apply(F f, std::tuple<Args ...> t) -> decltype( apply_impl(f, t, typename Generate<sizeof... (Args)>::type()) )
{
	return apply_impl(f, t, typename Generate<sizeof... (Args)>::type());
}


#include <iostream>
#include <string>

int main()
{
	auto f = [](int x, double y, double z) { return x + y + z; };
	auto t = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
	auto res = apply(f, t);                // res = 36.6

	std::cout << "Res=" << res << std::endl;



        auto f2 = [](int x, double y, double z) { return std::to_string(x) + std::to_string(y) + std::to_string(z); };
        auto t2 = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
        auto res2 = apply(f2, t2);                // res = 36.6

        std::cout << "Res2=" << res2 << std::endl;
}


