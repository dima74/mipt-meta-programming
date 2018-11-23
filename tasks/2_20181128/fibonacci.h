#ifndef META_PROGRAMMING_FIBONACCI_H
#define META_PROGRAMMING_FIBONACCI_H

template<int n>
struct Fibonacci {
	static constexpr int result = Fibonacci<n - 1>::result + Fibonacci<n - 2>::result;
};

template<>
struct Fibonacci<0> {
	static constexpr int result = 1;
};

template<>
struct Fibonacci<1> {
	static constexpr int result = 1;
};

#endif
