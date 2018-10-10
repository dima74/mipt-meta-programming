#ifndef META_PROGRAMMING_ERASE_H
#define META_PROGRAMMING_ERASE_H

#include "type_list.h"
#include "append_front.h"

template<typename List, typename R>
struct EraseImpl;

// удаление типа, не совпадающего с первым элементом списка
template<typename First, typename ... Rest, typename Deleted>
struct EraseImpl<TypeList<First, Rest...>, Deleted> {
private:
	using ResultWithoutFirst = typename EraseImpl<TypeList<Rest...>, Deleted>::Result;
public:
	using Result = typename AppendFront<First, ResultWithoutFirst>::Result;
};

// удаление типа из пустого списка
template<typename T>
struct EraseImpl<NullType, T> {
	using Result = NullType;
};

template<typename T>
struct EraseImpl<EmptyList, T> {
	using Result = NullType;
};

// удаление типа, совпадающего с первым элементом списка
template<typename T, typename ... U>
struct EraseImpl<TypeList<T, U...>, T> {
	using Result = TypeList<U...>;
};

template<typename List, typename T>
struct Erase {
private:
	using TypeListNormalized = typename Normalized<List>::type;
	using ResultInternal = typename EraseImpl<TypeListNormalized, T>::Result;
public:
	using Result = typename Denormalized<ResultInternal>::type;
};

#endif
