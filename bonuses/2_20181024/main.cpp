#include "hierarchy_scatter.h"

#include <string>
#include <cassert>
using std::string;

template<typename T>
struct Holder {
	T value;
};

struct Value {
	int x;
	int y;
};

using Hierarchy = GenScatterHierarchy<TypeList<int, string, Value>, Holder>;

template<typename T, typename Hierarchy>
T get_value(Hierarchy hierarchy) {
	return (static_cast<Holder<T> &>(hierarchy)).value;
}

int main() {
	Hierarchy hierarchy;

	(static_cast<Holder<int> &>(hierarchy)).value = 7;
	assert(get_value<int>(hierarchy) == 7);
	(static_cast<Holder<int> &>(hierarchy)).value = 77;
	assert(get_value<int>(hierarchy) == 77);

	(static_cast<Holder<string> &>(hierarchy)).value = "foo";
	assert(get_value<string>(hierarchy) == "foo");
	(static_cast<Holder<string> &>(hierarchy)).value = "bar";
	assert(get_value<string>(hierarchy) == "bar");

	(static_cast<Holder<Value> &>(hierarchy)).value = {3, 4};
	assert(get_value<Value>(hierarchy).x == 3);
	assert(get_value<Value>(hierarchy).y == 4);
	return 0;
}