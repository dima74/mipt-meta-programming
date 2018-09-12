#include <iostream>

class Singleton {
private:
	Singleton() = default;

public:
	Singleton(Singleton &) = delete;

	Singleton(Singleton &&) = delete;

	static Singleton &getInstance() {
		static Singleton instance;
		return *instance;
	}

	void printMessage() {
		std::cout << "hello" << std::endl;
	}
};

int main() {
	Singleton &instance = Singleton::getInstance();
	instance.printMessage();
	return 0;
}