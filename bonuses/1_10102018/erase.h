#ifndef META_PROGRAMMING_ERASE_H
#define META_PROGRAMMING_ERASE_H

#include "type_list.h"

template<typename TypeList, typename T>
struct EraseImpl;

// удаление типа из пустого списка
template<typename T>
struct EraseImpl<NullType, T> {
	using Result = NullType;
};

// удаление типа, совпадающего с первым элементом списка
template<typename T, typename ... U>
struct EraseImpl<TypeList<T, U...>, T> {
	using Result = TypeList<U...>;
};

// удаление типа, не совпадающего с первым элементом списка
template<typename T, typename ... U, typename R>
struct EraseImpl<TypeList<T, U...>, R> {
	using Result = TypeList<T, EraseImpl<TypeList<U...>, R>>;
};

template<typename TypeList, typename T>
struct Erase {
private:
	using TypeListNormalized = typename Normalized<TypeList>::type;
	using ResultInternal = typename EraseImpl<TypeListNormalized, T>::Result;
public:
	using Result = typename Denormalized<ResultInternal>::type;
};

#endif
