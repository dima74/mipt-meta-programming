#ifndef META_PROGRAMMING_BASE_H
#define META_PROGRAMMING_BASE_H

#include "iostream"
using std::cout;
using std::endl;

template<typename T>
void printType() {
	cout << "\n" << __PRETTY_FUNCTION__ << endl;
}

// type detector (works by generating error in compile-time)
template<typename T>
class TD;

#endif
