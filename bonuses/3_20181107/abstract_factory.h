#ifndef META_PROGRAMMING_ABSTRACT_FACTORY_H
#define META_PROGRAMMING_ABSTRACT_FACTORY_H

#include "../2_20181024/hierarchy_scatter.h"
#include "./hierarchy_linear.h"

// интерфейс

template<typename T>
struct TypeDescriptor {};

template<typename T>
struct IAbstractFactoryUnit {
	virtual T *create(TypeDescriptor<T>) = 0;

	virtual ~IAbstractFactoryUnit() {}
};

template<typename TypeList>
struct IAbstractFactory : public GenScatterHierarchy<TypeList, IAbstractFactoryUnit> {
	template<typename T>
	T *create() {
		return static_cast<IAbstractFactoryUnit<T> *>(this)->create(TypeDescriptor<T>());
	}
};

// реализация

template<typename TypeList, template<typename, typename> typename FactoryUnit>
struct CAbstractFactory : public GenLinearHierarchy<TypeList, FactoryUnit, IAbstractFactory<TypeList>> {

};

#endif
