#ifndef META_PROGRAMMING_HIERARCHY_COMPLEX_H
#define META_PROGRAMMING_HIERARCHY_COMPLEX_H

#include "../../bonuses/3_20181107/hierarchy_linear.h"
#include "../../bonuses/1_10102018/append_front.h"
#include "./fibonacci.h"
#include <cstddef>
#include <variant>
using std::enable_if_t;
using std::is_same_v;

template<typename List, size_t n, typename EnableFlag = void>
struct Split {
	// part0 --- первые n типов из List (меньше если Length<List> < n)
	using part0 = typename AppendFront<
			typename List::head,
			typename Split<typename List::tail, n - 1>::part0
	>::result;
	// part1 --- все остальные типы из List
	using part1 = typename Denormalized<typename Split<List, n - 1>::part1::tail>::type;
};

template<typename List>
struct Split<List, 0, enable_if_t<!is_same_v<List, NullType>>> {
	using part0 = TypeList<>;
	using part1 = List;
};

template<size_t n>
struct Split<NullType, n> {
	using part0 = TypeList<>;
	using part1 = TypeList<>;
};


template<typename TypeList, template<typename, typename> typename Unit, int i>
struct GenComplexHierarchyImpl :
		GenLinearHierarchy<typename Split<TypeList, Fibonacci<i>::result + 1>::part0, Unit>,
		GenComplexHierarchyImpl<typename Split<TypeList, Fibonacci<i>::result + 1>::part1, Unit, i + 1> {
};

template<template<typename, typename> typename Unit, int i>
struct GenComplexHierarchyImpl<TypeList<>, Unit, i> {};

template<typename TypeList, template<typename AtomicType, typename BaseType> typename Unit>
using GenComplexHierarchy = GenComplexHierarchyImpl<TypeList, Unit, 0>;

#endif
