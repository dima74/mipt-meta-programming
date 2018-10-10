#ifndef META_PROGRAMMING_LENGTH_H
#define META_PROGRAMMING_LENGTH_H

#include "type_list.h"

template<typename List>
struct Length {
	static constexpr int value = Length<typename List::tail>::value + 1;
};

template<>
struct Length<NullType> {
	static constexpr int value = 0;
};

template<>
struct Length<EmptyList> {
	static constexpr int value = 0;
};


#endif
