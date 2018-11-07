#include "./abstract_factory.h"
#include "../base.h"

struct Infantry {};
struct Archer {};
struct Cavalry {};
using UnitsList = TypeList<Infantry, Archer, Cavalry>;

template<typename T, typename BaseType>
struct FactoryUnit : public BaseType {
	T *create(TypeDescriptor<T>) {
		return new T();
	}
};

using IArmyFactory = IAbstractFactory<UnitsList>;
using CArmyFactory = CAbstractFactory<UnitsList, FactoryUnit>;

int main() {
	IArmyFactory *factory = new CArmyFactory();
	Archer *archer = factory->create<Archer>();
	Cavalry *cavalry = factory->create<Cavalry>();
	return 0;
}