#ifndef META_PROGRAMMING_HIERARCHY_LINEAR_H
#define META_PROGRAMMING_HIERARCHY_LINEAR_H

#include "../1_10102018/type_list.h"

template<typename TypeList, template<typename AtomicType, typename BaseType> typename Unit, typename Root = NullType>
struct GenLinearHierarchy;

template<typename T1, typename ... T2, template<typename AtomicType, typename BaseType> typename Unit, typename Root>
struct GenLinearHierarchy<TypeList<T1, T2...>, Unit, Root>
		: public Unit<T1, GenLinearHierarchy<TypeList<T2...>, Unit, Root>> {
};

template<typename T, template<typename, typename> typename Unit, typename Root>
struct GenLinearHierarchy<TypeList<T>, Unit, Root> : public Unit<T, Root> {};

#endif
