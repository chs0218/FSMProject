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
    if (pStudent->Location() != home)
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "나는 집이다!!";

        pStudent->ChangeLocation(home);
    }
}


void StayHomeAndRest::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "쉬는 중";
    pStudent->IncreaseHunger();
    pStudent->DecreaseFatigue();
    if (pStudent->Hungry())
        pStudent->GetFSM()->ChangeState(EatPizza::Instance());

    if (pStudent->Rested())
    {
        if(pStudent->HaveToStudy())
            pStudent->GetFSM()->ChangeState(GoLibraryAndStudy::Instance());
        else
            pStudent->GetFSM()->ChangeState(PlayGame::Instance());
    }
}


void StayHomeAndRest::Exit(Student* pStudent)
{
    /*std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "이제 집에서 좀 나가볼까?";*/
}


bool StayHomeAndRest::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

EatPizza* EatPizza::Instance()
{
    static EatPizza instance;

    return &instance;
}


void EatPizza::Enter(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "배고프다! 피자를 먹어야겠어!!";
    if (pStudent->Location() != home)
    {
        pStudent->ChangeLocation(home);
    }
}


void EatPizza::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "피자는 역시 맛있어";
    pStudent->BuyAndEatPizza();
    pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
}


void EatPizza::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "아 배부르다! 다시 쉬어볼까~";
}


bool EatPizza::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

PlayGame* PlayGame::Instance()
{
    static PlayGame instance;

    return &instance;
}


void PlayGame::Enter(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "게임하러가야겠다~!!";
    if (pStudent->Location() != pcRoom)
    {
        pStudent->ChangeLocation(pcRoom);
    }
}


void PlayGame::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "게임은 너무 재밌어!!";
    pStudent->IncreaseFatigue();
    pStudent->IncreasStudyLeft();
    if (pStudent->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "에구 힘들다 쉬러가야겠어..";
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }

    else if(pStudent->HaveToStudy())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "공부가 밀렸어.. 이제 공부해야할 것 같은데..?";
        pStudent->GetFSM()->ChangeState(GoLibraryAndStudy::Instance());
    }
}


void PlayGame::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "게임 끝~";
}


bool PlayGame::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

GoLibraryAndStudy* GoLibraryAndStudy::Instance()
{
    static GoLibraryAndStudy instance;

    return &instance;
}


void GoLibraryAndStudy::Enter(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "공부하러가야해...";
    if (pStudent->Location() != library)
    {
        pStudent->ChangeLocation(library);
    }
}


void GoLibraryAndStudy::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "열심히 공부하는 중!!";
    pStudent->DoStudy();
    pStudent->IncreaseHunger();
    pStudent->IncreaseFatigue();
    if (pStudent->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "에구 힘들다 쉬러가야겠어..";
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }

    else if (pStudent->Hungry())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "배고프다.. 쉬러가야겠어..";
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }

    else if (pStudent->FinishStudy())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "공부 끝!!";
        pStudent->GetFSM()->ChangeState(PlayGame::Instance());
    }
}


void GoLibraryAndStudy::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "도서관은 역시 끔찍해..";
}


bool GoLibraryAndStudy::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}