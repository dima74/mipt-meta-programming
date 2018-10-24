#ifndef META_PROGRAMMING_OBSERVER_H
#define META_PROGRAMMING_OBSERVER_H

#include "base.h"
#include <vector>
using std::vector;

struct ISubscriber {
	virtual void update() = 0;

	virtual ~ISubscriber() {}
};

struct ExampleSubscriber : public ISubscriber {
	void update() {
		// handle update
	}
};

template<>
class ComplexClass<ComplexClassType::OBSERVER> {
private:
	vector<ISubscriber *> subscribers;
	int state = 0;

	void notifySubscribers() {
		for (ISubscriber *subscriber : subscribers) {
			subscriber->update();
		}
	}

public:
	ComplexClass(ISubscriber *subscriber1, ISubscriber *subscriber2) : subscribers({subscriber1, subscriber2}) {}

	void changeState() {
		++state;
		notifySubscribers();
	}
};

#endif
