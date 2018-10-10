#ifndef META_PROGRAMMING_APPEND_FRONT_H
#define META_PROGRAMMING_APPEND_FRONT_H

#include "type_list.h"

template<typename T, typename List>
struct AppendFront;

template<typename T, typename ... U>
struct AppendFront<T, TypeList<U...>> {
	using Result = TypeList<T, U...>;
};

template<typename T>
struct AppendFront<T, NullType> {
	using Result = TypeList<T>;
};

#endif
