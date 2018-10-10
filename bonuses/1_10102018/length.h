#ifndef META_PROGRAMMING_LENGTH_H
#define META_PROGRAMMING_LENGTH_H

#include "type_list.h"

template<typename TypeList>
struct Length {
	static constexpr int value = Length<typename TypeList::tail>::value + 1;
};

template<>
struct Length<NullType> {
	static constexpr int value = 0;
};

template<>
struct Length<TypeList<>> {
	static constexpr int value = 0;
};


#endif
