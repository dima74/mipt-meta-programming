#include <iostream>
#include <vector>
using namespace std;

struct Entity {
	virtual int getTotalPrice() = 0;

	virtual ~Entity() = default;
};

struct Item : public Entity {
	int price;

	explicit Item(int price) : price(price) {}

	int getTotalPrice() override {
		return price;
	}
};

struct Package : public Entity {
	vector<Entity *> entities;

	Package(const initializer_list<Entity *> &entities) : entities(entities) {}

	int getTotalPrice() override {
		int totalPrice = 0;

		for (Entity *entity : entities) {
			totalPrice += entity->getTotalPrice();
		}
		return totalPrice;
	}
};

int main() {
	Item *item1 = new Item(1);
	Item *item2 = new Item(2);
	Item *item3 = new Item(3);

	Package *package1 = new Package({item1, item2});
	Package *package2 = new Package({package1, item3});

	cout << package1->getTotalPrice() << endl;
	cout << package2->getTotalPrice() << endl;
	return 0;
}