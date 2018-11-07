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

using IArmyFactory = GenScatterHierarchy<
		UnitsList,
		IAbstractFactoryUnit
>;

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
		IArmyFactory
>;

int main() {
	IArmyFactory *factory = new CArmyFactory();
	Archer *archer = static_cast<IAbstractFactoryUnit<Archer>*>(factory)->create(TypeDescriptor<Archer>());
	return 0;
}