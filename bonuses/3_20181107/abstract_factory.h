#ifndef META_PROGRAMMING_ABSTRACT_FACTORY_H
#define META_PROGRAMMING_ABSTRACT_FACTORY_H

#include "../2_20181024/hierarchy_scatter.h"
#include "./hierarchy_linear.h"
#include "./allocator.h"

// интерфейс

template<typename T>
struct TypeDescriptor {};

template<typename T>
struct IAbstractFactoryUnit {
	virtual T *create(TypeDescriptor<T>) = 0;

	virtual ~IAbstractFactoryUnit() {}
};

template<typename TypeList>
struct IAbstractFactory : GenScatterHierarchy<TypeList, IAbstractFactoryUnit> {
	template<typename T>
	T *create() {
		return static_cast<IAbstractFactoryUnit<T> *>(this)->create(TypeDescriptor<T>());
	}
};

// реализация

template<
		template<typename T, template<typename> typename Allocator> typename FactoryUnit,
		template<typename> typename Allocator,
		typename T,
		typename Base
>
struct FactoryUnitWrapper : FactoryUnit<T, Allocator>, Base {
	virtual T *create(TypeDescriptor<T>) {
		return FactoryUnit<T, Allocator>::create(allocator);
	}

private:
	Allocator<T> allocator;
};

template<
		template<typename T, template<typename> typename Allocator> typename FactoryUnit,
		template<typename> typename Allocator
>
struct GetFactoryUnitWrapper {
	template<typename T, typename Base>
	using FactoryUnitWrapperAlias = FactoryUnitWrapper<FactoryUnit, Allocator, T, Base>;
};

template<
		typename TypeList,
		template<typename, template<typename> typename> typename FactoryUnit,
		template<typename> typename Allocator
>
using CAbstractFactory = GenLinearHierarchy<
		TypeList,
		GetFactoryUnitWrapper<FactoryUnit, Allocator>::template FactoryUnitWrapperAlias,
		IAbstractFactory<TypeList>
>;

#endif
