#include <sstream>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <string>
#include <typeinfo>

using namespace std;


template <typename T>
constexpr bool var_int = std::is_same<T, int>::value;

template <typename T>
struct is_int //предикат проверка на инт
{
	static constexpr bool value = is_same<T, int>::value;
};



template <bool b, typename T>
struct GetType
{
	typedef T Type;
};


template <typename T>
struct GetType<false, T>
{
	typedef int Type;
};




template <bool b, typename T>
struct KSelectValue
{
	static typename GetType<b, T>::Type GetValue(int c, T v)
	{
		
		if (c % 2) {
			if constexpr (b) return v; else return 0;
		}
		return 0;
	}
};

int FSum()
{
	return 0;
}

template <typename T>
decltype(auto) FSum(int c, T x)
{
	return KSelectValue<is_int<T>::value, T>::GetValue(c, x);
}

template <typename T, typename... Args>
auto FSum(int c, T x, Args... args)
{
	return KSelectValue<is_int<T>::value, T>::GetValue(c,x) + FSum(c+1, args...);
}


template <typename ... Args> struct NoInts;

template <typename T, typename T2, typename ... Args>
struct NoInts<T, T2, Args...>
{
	static constexpr int value = (is_int<T2>::value ? 1 : 0) + NoInts<Args...>::value;
};

template <typename T, typename T2>
struct NoInts<T,T2>
{
	static constexpr int value = is_int<T2>::value ? 1 : 0;
};


template <typename T>
struct NoInts<T>
{
	static constexpr int value = is_int<T>::value ? 1 : 0;
};


template <typename T, typename... Args>
 auto FSum3(T x, Args... args)
{
	static_assert(NoInts<T, Args...>::value != 0, "No ints");
	return FSum(0, x, args...);
}


 template <typename T>
 auto FSum3(T x)
 {
	 return 0;
 }

 auto FSum3()
 {
	 return 0;
 }

int main()
{
	
	cout<<FSum3();
}

