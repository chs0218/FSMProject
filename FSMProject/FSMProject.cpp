#include <iostream>

#include "EntityNames.h"
#include "EntityManager.h"
#include "ConsoleUtils.h"
#include "Student.h"

int main()
{
	//seed random number generator
	srand((unsigned)time(NULL));

	//create a student
	Student* Kim = new Student(ent_Student);

	EntityMgr->RegisterEntity(Kim);

	for (int i = 0; i < 30; ++i)
	{
		Kim->Update();
	}

	delete Kim;
	PressAnyKeyToContinue();
	return 0;
}