#include "./abstract_factory.h"
#include "../base.h"

struct Infantry {};
struct Archer {};
struct Cavalry {};
using UnitsList = TypeList<Infantry, Archer, Cavalry>;

template<typename T, template<typename> typename Allocator>
struct FactoryUnit {
	T *create(Allocator<T> &allocator) {
		return allocator.allocate();
	}
};

using IArmyFactory = IAbstractFactory<UnitsList>;
using CArmyFactory = CAbstractFactory<UnitsList, FactoryUnit, AllocatorUsingNew>;

int main() {
	IArmyFactory *factory = new CArmyFactory();
	Archer *archer = factory->create<Archer>();
	Cavalry *cavalry = factory->create<Cavalry>();
	return 0;
}