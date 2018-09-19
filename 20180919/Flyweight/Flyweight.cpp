#include <bits/stdc++.h>
using namespace std;

struct UnitType {
	string name;
	int attack;

	UnitType(string name, int attack) : name(std::move(name)), attack(attack) {}
};

struct Unit {
	UnitType *type;

	explicit Unit(UnitType *type) : type(type) {}

	void attack() {
		cout << type->name << " attack: " << type->attack << endl;
	}
};

int main() {
	UnitType soldierType("soldier", 7);
	Unit soldier(&soldierType);
	soldier.attack();
}