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
	using Int = TypeList<int>;
	// using Char = TypeList<char>;
	using IntChar = TypeList<int, char>;

	static_assert(is_same<EmptyList, Erase<Int, int>::Result>::value);
	static_assert(!is_same<Int, Erase<Int, char>::Result>::value);
}

int main() {
	testLength();
	testErase();
	return 0;
}