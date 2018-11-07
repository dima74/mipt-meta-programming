#ifndef META_PROGRAMMING_HIERARCHY_SCATTER_H
#define META_PROGRAMMING_HIERARCHY_SCATTER_H

#include "../1_10102018/type_list.h"

template<typename TypeList, template<typename AtomicType> typename Unit>
struct GenScatterHierarchy;

template<typename ... Types, template<typename> typename Unit>
struct GenScatterHierarchy<TypeList<Types...>, Unit> : public Unit<Types> ... {};

#endif
