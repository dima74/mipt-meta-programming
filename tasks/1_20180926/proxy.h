#ifndef META_PROGRAMMING_PROXY_H
#define META_PROGRAMMING_PROXY_H

#include "base.h"
#include <string>
using std::string;

struct IDataBase {
	virtual int getData() = 0;

	virtual void setData(int data) = 0;

	virtual ~IDataBase() {}
};

class DataBase : public IDataBase {
private:
	int data = -1;

public:
	int getData() {
		return data;
	}

	void setData(int data) {
		this->data = data;
	}
};

template<>
class ComplexClass<ComplexClassType::PROXY> : public IDataBase {
private:
	IDataBase *database = nullptr;

	void log(string message) {
		// log message
	}

public:
	ComplexClass(IDataBase *database) : database(database) {}

	int getData() {
		log("getData");
		return database->getData();
	}

	void setData(int data) {
		log("setData");
		database->setData(data);
	}
};

#endif
