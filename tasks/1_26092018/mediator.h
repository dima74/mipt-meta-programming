#ifndef META_PROGRAMMING_MEDIATOR_H
#define META_PROGRAMMING_MEDIATOR_H

#include "base.h"

enum class EventType {
	BUTTON_CLICK,
};

// definition 0

struct IMediator {
	virtual void notify(EventType eventType) = 0;

	virtual ~IMediator() {}
};

class IComponent {
private:
	void attachToMediator(IMediator *mediator) {
		this->mediator = mediator;
	}

	friend ComplexClass<ComplexClassType::MEDIATOR>;

protected:
	IMediator *mediator;

public:
	virtual ~IComponent() {}
};

struct IButtonComponent : public IComponent {
	virtual void click() = 0;

	virtual ~IButtonComponent() {}
};

struct IDialogComponent : public IComponent {
	virtual void show() = 0;

	virtual ~IDialogComponent() {}
};

// definition 1

class ButtonComponent : public IButtonComponent {
public:
	void click() {
		this->mediator->notify(EventType::BUTTON_CLICK);
	}
};

class DialogComponent : public IDialogComponent {
public:
	void show() {
		// код показывающий диалог
	}
};

template<>
class ComplexClass<ComplexClassType::MEDIATOR> : public IMediator {
private:
	IButtonComponent *showDialogButton;
	IDialogComponent *dialogComponent;

public:
	ComplexClass(IButtonComponent *showDialogButton, IDialogComponent *dialogComponent) : showDialogButton(showDialogButton), dialogComponent(dialogComponent) {
		showDialogButton->attachToMediator(this);
		dialogComponent->attachToMediator(this);
	}

	void notify(EventType eventType) {
		if (eventType == EventType::BUTTON_CLICK) {
			dialogComponent->show();
		}
	}
};

#endif
