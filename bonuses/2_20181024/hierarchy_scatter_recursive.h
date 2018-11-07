#ifndef META_PROGRAMMING_HIERARCHY_SCATTER_H
#define META_PROGRAMMING_HIERARCHY_SCATTER_H

#include "../1_10102018/type_list.h"

template<typename TypeList, template<typename AtomicType> typename Unit>
struct GenScatterHierarchy;

template<typename T1, typename ... T2, template<typename> typename Unit>
struct GenScatterHierarchy<TypeList<T1, T2...>, Unit> :
		public Unit<T1>,
		public GenScatterHierarchy<TypeList<T2...>, Unit> {
};

template<template<typename> typename Unit>
struct GenScatterHierarchy<TypeList<>, Unit> {};

#endif
