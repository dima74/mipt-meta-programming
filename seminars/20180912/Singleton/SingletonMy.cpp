#include <iostream>

class Singleton {
private:
	static Singleton *instance;

	Singleton() = default;

public:
	Singleton(Singleton &) = delete;

	Singleton(Singleton &&) = delete;

	static Singleton &getInstance() {
		return *instance;
	}

	void printMessage() {
		std::cout << "hello" << std::endl;
	}
};

Singleton *Singleton::instance = new Singleton();

int main() {
	Singleton &instance = Singleton::getInstance();
	instance.printMessage();
	return 0;
}