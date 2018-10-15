#include <type_traits>
#include <cassert>
#include "length.h"
#include "erase.h"
using std::is_same;

void testLength() {
	static_assert(0 == Length<EmptyList>::value);
	static_assert(1 == Length<TypeList<int>>::value);
	static_assert(2 == Length<TypeList<int, int>>::value);
	static_assert(3 == Length<TypeList<int, int, int>>::value);
}

void testErase() {
	// length = 1
	using Int = TypeList<int>;
	using Char = TypeList<char>;
	// length = 2
	using IntInt = TypeList<int, int>;
	using IntChar = TypeList<int, char>;
	using CharInt = TypeList<char, int>;
	using CharChar = TypeList<char, char>;
	// length = 3
	using IntIntChar = TypeList<int, int, char>;
	using IntBoolChar = TypeList<int, bool, char>;

	// length = 0
	static_assert(is_same<Erase<EmptyList, int>::Result, EmptyList>::value);
	// length = 1
	static_assert(is_same<Erase<Int, int>::Result, EmptyList>::value);
	static_assert(is_same<Erase<Int, char>::Result, Int>::value);
	// length = 2
	static_assert(is_same<Erase<IntInt, int>::Result, Int>::value);
	static_assert(is_same<Erase<IntChar, int>::Result, Char>::value);
	static_assert(is_same<Erase<CharInt, int>::Result, Char>::value);
	static_assert(is_same<Erase<CharChar, int>::Result, CharChar>::value);
	// length = 3
	static_assert(is_same<Erase<IntIntChar, int>::Result, IntChar>::value);
	static_assert(is_same<Erase<IntIntChar, char>::Result, IntInt>::value);
	static_assert(is_same<Erase<IntBoolChar, int>::Result, TypeList<bool, char>>::value);
	static_assert(is_same<Erase<IntBoolChar, bool>::Result, IntChar>::value);
	static_assert(is_same<Erase<IntBoolChar, char>::Result, TypeList<int, bool>>::value);
}

int main() {
	testLength();
	testErase();
	return 0;
}