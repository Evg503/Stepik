#include <vector>
#include <list>
#include <iterator>

template<class T>
class VectorList
{
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q); // определена снаружи
/*  {
        if (p != q)
            data_.push_back(VectT(p,q));
    } 
*/

    bool empty() const { return size() == 0; } 

    // определите метод size
    size_t size() const 
    {
	size_t r = 0;
	for(auto const &v:data_)
		r+=v.size();
        return r;
    }

    // определите const_iterator
    //... const_iterator ... 
    struct const_iterator : std::iterator<std::bidirectional_iterator_tag, T, std::ptrdiff_t, T const*, T const &>
	{
                const_iterator() = default;

		const_iterator(
			typename ListT::const_iterator list_it, 
			typename ListT::const_iterator list_end)
			:list_it(list_it), list_end(list_end)
			{
				if(list_it != list_end)
					vec_it = list_it->begin();
			}

		const_iterator(const_iterator const & it) = default;

		const_iterator& operator++()
		{

                       if(list_it != list_end)
                        {
                                ++vec_it;
                                if(vec_it == list_it->end())
                                {
                                        ++list_it;

                                        if(list_it != list_end)
                                                vec_it = list_it->begin();
                                }
                        }
                        return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator r = *this;
			++*this;
			return r;
		}


                const_iterator& operator--()
		{
                       if(list_it != list_end)
                        {
                                if(vec_it == list_it->begin())
                                {
                                        --list_it;
                                        vec_it = list_it->end();
                                }
                                --vec_it;

                        }
			else
			{
				--list_it;
                                vec_it = list_it->end();
                                --vec_it;

			}
                        return *this;
		}
                
		const_iterator operator--(int)
                {
                        const_iterator r = *this;
                        --*this;
                        return r;
                }


                T const & operator*() const {return *vec_it;}
                T const * operator->() const {return vec_it.operator->();};

                bool operator == (const_iterator const& rhs) const 
		{
			if(list_it != rhs.list_it) return false;
			if(list_it == list_end) return true;
			return vec_it == rhs.vec_it;
		}
		bool operator != (const_iterator const& rhs) const {return !operator== (rhs);}

			
		typename ListT::const_iterator list_it;
		typename ListT::const_iterator list_end;
		typename VectT::const_iterator vec_it;
	};

    // определите методы begin / end
    const_iterator begin() const { return const_iterator(data_.begin(), data_.end()); }
    const_iterator end()   const { return const_iterator(data_.end(), data_.end()); }

    // определите const_reverse_iterator
    ///... const_reverse_iterator ...
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end());   }
    const_reverse_iterator rend()   const { return const_reverse_iterator(begin()); }

private:
    ListT data_;
};
/*helpers*/
    template<class T>
    template<class It>
    void VectorList<T>::append(It p, It q) // определена снаружи
    {
        if (p != q)
            data_.push_back(VectT(p,q));
    } 



/*tests*/
#include <iostream>


int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,11,22,33,44,55,66,77,88,99};

	VectorList<int> v;
	std::cout << "v.size() == " << v.size() << std::endl;

	v.append(a, a+9);
	std::cout << "v.size() == " << v.size() << std::endl;

	v.append(a+9, a+18);
	std::cout << "v.size() == " << v.size() << std::endl;
	
	for(auto & i:v)
		std::cout << i <<" ";
	std::cout << std::endl;

        for(auto i = v.begin(); i != v.end(); i++)
                std::cout << *i <<" ";
        std::cout << std::endl;

        for(auto i = v.rbegin(); i != v.rend(); ++i)
                std::cout << *i <<" ";
        std::cout << std::endl;
}




