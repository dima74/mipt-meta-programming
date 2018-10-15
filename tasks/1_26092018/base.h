#ifndef META_PROGRAMMING_BASE_H
#define META_PROGRAMMING_BASE_H

enum class ComplexClassType {
	PROXY,
	MEDIATOR,
	OBSERVER,
};

template<ComplexClassType classType>
class ComplexClass;

#endif
