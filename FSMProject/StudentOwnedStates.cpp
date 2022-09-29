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
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ���̴�!!";

        pStudent->ChangeLocation(home);
    }
}


void StayHomeAndRest::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ��";
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
        << "���� ������ �� ��������?";*/
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
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�������! ���ڸ� �Ծ�߰ھ�!!";
    if (pStudent->Location() != home)
    {
        pStudent->ChangeLocation(home);
    }
}


void EatPizza::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���ڴ� ���� ���־�";
    pStudent->BuyAndEatPizza();
    pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
}


void EatPizza::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "�� ��θ���! �ٽ� �����~";
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
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�����Ϸ����߰ڴ�~!!";
    if (pStudent->Location() != pcRoom)
    {
        pStudent->ChangeLocation(pcRoom);
    }
}


void PlayGame::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "������ �ʹ� ��վ�!!";
    pStudent->IncreaseFatigue();
    pStudent->IncreasStudyLeft();
    if (pStudent->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ����� �������߰ھ�..";
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }

    else if(pStudent->HaveToStudy())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���ΰ� �зȾ�.. ���� �����ؾ��� �� ������..?";
        pStudent->GetFSM()->ChangeState(GoLibraryAndStudy::Instance());
    }
}


void PlayGame::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "���� ��~";
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
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�����Ϸ�������...";
    if (pStudent->Location() != library)
    {
        pStudent->ChangeLocation(library);
    }
}


void GoLibraryAndStudy::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "������ �����ϴ� ��!!";
    pStudent->DoStudy();
    pStudent->IncreaseHunger();
    pStudent->IncreaseFatigue();
    if (pStudent->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ����� �������߰ھ�..";
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }

    else if (pStudent->Hungry())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�������.. �������߰ھ�..";
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }

    else if (pStudent->FinishStudy())
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ��!!";
        pStudent->GetFSM()->ChangeState(PlayGame::Instance());
    }
}


void GoLibraryAndStudy::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "�������� ���� ������..";
}


bool GoLibraryAndStudy::OnMessage(Student* pStudent, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}