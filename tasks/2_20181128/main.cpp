#include "../../bonuses/1_10102018/type_list.h"
#include "../../bonuses/base.h"
#include "./hierarchy_complex.h"

// stub type
template<int>
struct T;

template<typename T, typename Base>
struct Unit : Base {
	T *create() {
		return new T();
	}
};

using Example0 = GenComplexHierarchy<TypeList<>, Unit>;
using Example1 = GenComplexHierarchy<TypeList<T<1>>, Unit>;
using Example2 = GenComplexHierarchy<TypeList<T<1>, T<2>>, Unit>;
using Example3 = GenComplexHierarchy<TypeList<T<1>, T<2>, T<3>>, Unit>;
using Example4 = GenComplexHierarchy<TypeList<T<1>, T<2>, T<3>, T<4>>, Unit>;
using Example5 = GenComplexHierarchy<TypeList<T<1>, T<2>, T<3>, T<4>, T<5>>, Unit>;
using Example6 = GenComplexHierarchy<TypeList<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>>, Unit>;
using Example7 = GenComplexHierarchy<TypeList<T<1>, T<2>, T<3>, T<4>, T<5>, T<6>, T<7>>, Unit>;

int main() {
	Example0 example0;
	Example1 example1;
	Example2 example2;
	Example3 example3;
	Example4 example4;
	Example5 example5;
	Example6 example6;
	Example7 example7;
	return 0;
}