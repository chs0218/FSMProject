#include <iostream>

#include "EntityNames.h"
#include "EntityManager.h"
#include "ConsoleUtils.h"
#include "MessageDispatcher.h"
#include "Student.h"
#include "PizzaStoreOwner.h"
#include "Delivery.h"

int main()
{
	//seed random number generator
	srand((unsigned)time(NULL));

	std::cout << "FSM 과제(2018180044 최해성)" << std::endl;

	//create a student
	Student* Kim = new Student(ent_Student);
	PizzaStoreOwner* Lee = new PizzaStoreOwner(ent_PizzaStoreOwner);
	Delivery* Park = new Delivery(ent_Delivery);

	EntityMgr->RegisterEntity(Kim);
	EntityMgr->RegisterEntity(Lee);
	EntityMgr->RegisterEntity(Park);

	for (int i = 0; i < 30; ++i)
	{
		Kim->Update();
		Lee->Update();
		Park->Update();

		Dispatch->DispatchDelayedMessages();

		Sleep(800);
	}

	delete Kim;
	delete Lee;
	delete Park;

	PressAnyKeyToContinue();
	return 0;
}