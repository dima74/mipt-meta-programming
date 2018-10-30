#ifndef META_PROGRAMMING_HIERARCHY_H
#define META_PROGRAMMING_HIERARCHY_H

#include "../1_10102018/type_list.h"

template<typename TypeList, template<typename> typename Unit>
class GenScatterHierarchy;

template<typename T1, typename ... T2, template<typename> typename Unit>
class GenScatterHierarchy<TypeList<T1, T2...>, Unit> :
		public GenScatterHierarchy<T1, Unit>,
		public GenScatterHierarchy<TypeList<T2...>, Unit> {
};

template<typename AtomicType, template<typename> typename Unit>
class GenScatterHierarchy : public Unit<AtomicType> {};

template<template<typename> typename Unit>
class GenScatterHierarchy<NullType, Unit> {};

#endif
