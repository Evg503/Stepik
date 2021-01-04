#include <thread>

#include <cassert>
// заголовок <future> уже подключён.
// заново подключать не нужно

template<typename It, typename F1, typename F2>
auto map_reduce(It p, It q, F1 f1, F2 f2) ->decltype(f2(f1(*p), f1(*p)))
{
        auto res = f1(*p);
        while(++p != q)
                res = f2(res, f1(*p));
        return res;

}
// реализация функции mapreduce

template<typename It, typename F1, typename F2>
auto map_reduce(It p, It q, F1 f1, F2 f2,  size_t threads) ->decltype(f2(f1(*p), f1(*p)))
{
	using R1 = decltype(f1(*p));

	R1 results[threads];
	std::thread trds[threads];
	auto size = std::distance(p, q);
	It last = p;
	for(int i =0; i<threads; ++i)
	{
		It next = std::next(p, size*(i+1)/threads);
		trds[i] = std::thread([&results, i](It b, It e, F1 f1, F2 f2)
                                        {
                                                results[i] = map_reduce(b, e, f1, f2);
                                        }, last, next, f1, f2);

		last = next;
	}
	trds[0].join();
	auto res = results[0];
	for(int i = 1; i < threads; ++i)
	{
		trds[i].join();
		res = f2(res, results[i]);
	}
	return res;
}

#include <list>
#include <string>
#include <iostream>


int main()
{
std::list<int> l = {1,2,3,4,5,6,7,8,9,10};
// параллельное суммирование в 3 потока
auto sum = map_reduce(l.begin(), l.end(),
	[](int i){return i;},
	std::plus<int>(), 3);

std::cout << "sum = " << sum << std::endl;

// проверка наличия чётных чисел в четыре потока
auto has_even = map_reduce(l.begin(), l.end(),
	[](int i){return i % 2 == 0;},
	std::logical_or<bool>(), 4);

std::cout << "has_even = " << has_even << std::endl;

// параллельное суммирование в 3 потока
auto str_sum = map_reduce(l.begin(), l.end(),
        [](int i){return std::to_string(i);},
        std::plus<std::string>(), 5);

std::cout << "str_sum = " << str_sum << std::endl;

}


