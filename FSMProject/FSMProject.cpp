#include <iostream>

#include "EntityNames.h"
#include "EntityManager.h"
#include "ConsoleUtils.h"
#include "Student.h"
#include "PizzaStoreOwner.h"

int main()
{
	//seed random number generator
	srand((unsigned)time(NULL));

	//create a student
	Student* Kim = new Student(ent_Student);
	PizzaStoreOwner* Lee = new PizzaStoreOwner(ent_PizzaStoreOwner);

	EntityMgr->RegisterEntity(Kim);
	EntityMgr->RegisterEntity(Lee);

	for (int i = 0; i < 30; ++i)
	{
		Kim->Update();
		Lee->Update();
	}

	delete Kim;
	delete Lee;

	PressAnyKeyToContinue();
	return 0;
}