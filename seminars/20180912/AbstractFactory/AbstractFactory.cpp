#include <iostream>
using namespace std;

struct Unit {
	virtual void attack() = 0;

	virtual ~Unit() {}
};

struct Soldier : public Unit {
	int power;

	Soldier(int power) : power(power) {}

	void attack() {
		cout << "solder attack, power = " << power << endl;
	}
};

struct Archer : public Unit {
	int range;

	Archer(int range) : range(range) {}

	void attack() {
		cout << "archer attack, range = " << range << endl;
	}
};

struct AbstractFactory {
	virtual Soldier createSoldier() = 0;

	virtual Archer createArcher() = 0;
};

struct EasyFactory : public AbstractFactory {
	Soldier createSoldier() {
		return Soldier(10);
	}

	Archer createArcher() {
		return Archer(10);
	}
};

struct DifficultFactory : public AbstractFactory {
	Soldier createSoldier() {
		return Soldier(100);
	}

	Archer createArcher() {
		return Archer(100);
	}
};

struct Game {
	AbstractFactory *factory;

	Game(string difficulty) {
		if (difficulty == "easy") {
			factory = new EasyFactory();
		} else {
			factory = new DifficultFactory();
		}
	}

	void createUnitsAndAttack() {
		Soldier soldier = factory->createSoldier();
		Archer archer = factory->createArcher();

		soldier.attack();
		archer.attack();
	}
};

int main() {
	Game gameEasy("easy");
	gameEasy.createUnitsAndAttack();

	Game gameDifficult("difficult");
	gameDifficult.createUnitsAndAttack();
	return 0;
}