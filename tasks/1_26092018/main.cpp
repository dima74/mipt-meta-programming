#include "base.h"
#include "proxy.h"
#include "mediator.h"
#include "observer.h"

void exampleProxyUsage() {
	DataBase *databaseOriginal = new DataBase();
	IDataBase *database = new ComplexClass<ComplexClassType::PROXY>(databaseOriginal);

	database->setData(7);
	int data = database->getData();
}

void exampleMediatorUsage() {
	IButtonComponent *buttonComponent = new ButtonComponent();
	IDialogComponent *dialogComponent = new DialogComponent();
	IMediator *mediator = new ComplexClass<ComplexClassType::MEDIATOR>(buttonComponent, dialogComponent);

	buttonComponent->click();
}

void exampleObserverUsage() {
	ISubscriber *subscriber1 = new ExampleSubscriber();
	ISubscriber *subscriber2 = new ExampleSubscriber();
	auto *observer = new ComplexClass<ComplexClassType::OBSERVER>(subscriber1, subscriber2);

	observer->changeState();
}

int main() {
	exampleProxyUsage();
	exampleMediatorUsage();
	exampleObserverUsage();
}
