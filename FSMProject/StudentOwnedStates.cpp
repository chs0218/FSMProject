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
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "나는 집이다!!";

        pStudent->ChangeLocation(home);
    }
}


void StayHomeAndRest::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "쉬는 중";
}


void StayHomeAndRest::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "이제 집에서 좀 나가볼까?";
}


bool StayHomeAndRest::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}