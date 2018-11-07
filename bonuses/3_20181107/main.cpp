#include "../2_20181024/hierarchy_scatter.h"
#include "./hierarchy_linear.h"
#include "../base.h"

#include <utility>
using namespace std;

struct Infantry {};
struct Archer {};
struct Cavalry {};

// интерфейс

using UnitsList = TypeList<Infantry, Archer, Cavalry>;

template<typename T>
struct TypeDescriptor {};

template<typename T>
struct IAbstractFactoryUnit {
	virtual T *create(TypeDescriptor<T>) = 0;

	virtual ~IAbstractFactoryUnit() {}
};

template<typename TypeList>
struct IArmyFactory : public GenScatterHierarchy<TypeList, IAbstractFactoryUnit> {
	template<typename T>
	T *create() {
		return static_cast<IAbstractFactoryUnit<T> *>(this)->create(TypeDescriptor<T>());
	}
};

// реализация

template<typename T, typename BaseType>
struct CFactoryUnit : public BaseType {
	T *create(TypeDescriptor<T>) {
		return new T();
	}
};

using CArmyFactory = GenLinearHierarchy<
		UnitsList,
		CFactoryUnit,
		IArmyFactory<UnitsList>
>;

int main() {
	IArmyFactory<UnitsList> *factory = new CArmyFactory();
	Archer *archer = factory->create<Archer>();
	Cavalry *cavalry = factory->create<Cavalry>();
	return 0;
}