#ifndef META_PROGRAMMING_TYPE_LIST_H
#define META_PROGRAMMING_TYPE_LIST_H

struct NullType {};

template<typename ... Types>
struct TypeList;

template<typename First, typename ... Rest>
struct TypeList<First, Rest...> {
	using head = First;
	using tail = TypeList<Rest...>;
};

template<typename T>
struct TypeList<T> {
	using head = T;
	using tail = NullType;
};

template<>
struct TypeList<> {
	using head = NullType;
	using tail = NullType;
};

using EmptyList = TypeList<>;

// у нас есть проблема, что EmptyList это TypeList { head = tail = NullType }, хотя было гораздо лучше, если EmptyList был бы NullType
// поэтому нужна данная функция
template<typename List>
struct Normalized {
	using type = List;
};

template<>
struct Normalized<EmptyList> {
	using type = NullType;
};

template<typename List>
struct Denormalized {
	using type = List;
};

template<>
struct Denormalized<NullType> {
	using type = EmptyList;
};

#endif
