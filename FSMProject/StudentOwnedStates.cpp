#include "StudentOwnedStates.h"
#include "Student.h"
#include "Locations.h"
#include "State.h"
#include "EntityNames.h"

StayHomeAndRest* StayHomeAndRest::Instance()
{
    static StayHomeAndRest instance;

    return &instance;
}


void StayHomeAndRest::Enter(Student* pStudent)
{
    //if the miner is not already located at the goldmine, he must
    //change location to the gold mine
    if (pStudent->Location() != home)
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ���̴�!!";

        pStudent->ChangeLocation(home);
    }
}


void StayHomeAndRest::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ��";
}


void StayHomeAndRest::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "���� ������ �� ��������?";
}


bool StayHomeAndRest::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}