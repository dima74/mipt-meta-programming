#ifndef META_PROGRAMMING_BASE_H
#define META_PROGRAMMING_BASE_H

#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::string;
using std::strlen;

template<typename T>
void printType() {
	cout << "\n" << __PRETTY_FUNCTION__ << endl;
}

template<typename T>
string getTypeName() {
	// something like "std::__cxx11::string getTypeName() [T = int]"
	string function_signature = __PRETTY_FUNCTION__;
	size_t i = function_signature.find("getTypeName");
	return string(function_signature.begin() + i + strlen("getTypeName() [T = "), function_signature.end() - 1);
}

// type detector (works by generating error in compile-time)
template<typename T>
class TD;

#endif
