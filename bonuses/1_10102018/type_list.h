#ifndef META_PROGRAMMING_TYPE_LIST_H
#define META_PROGRAMMING_TYPE_LIST_H

struct NullType {};

template<typename ... T>
struct TypeList;

template<typename T, typename ... U>
struct TypeList<T, U...> {
	using head = T;
	using tail = TypeList<U...>;
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

template<typename TypeList>
struct Normalized {
	using type = TypeList;
};

template<>
struct Normalized<EmptyList> {
	using type = NullType;
};

template<typename TypeList>
struct Denormalized {
	using type = TypeList;
};

template<>
struct Denormalized<NullType> {
	using type = EmptyList;
};

#endif
