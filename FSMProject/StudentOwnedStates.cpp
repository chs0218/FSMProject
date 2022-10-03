#include "StudentOwnedStates.h"
#include "Student.h"
#include "Locations.h"
#include "State.h"
#include "EntityNames.h"
#include "CrudeTimer.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"

double MotherCallingChance() { return ((rand()) / (RAND_MAX + 1.0)); }

StudentGlobalState* StudentGlobalState::Instance()
{
    static StudentGlobalState instance;

    return &instance;
}


void StudentGlobalState::Execute(Student* pStudent)
{
    if (MotherCallingChance() < 0.2)
    {
        pStudent->GetFSM()->ChangeState(CallAndTalkToParent::Instance());
    }
}

bool StudentGlobalState::OnMessage(Student* pStudent, const Telegram& msg)
{
    return false;

}

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
        pStudent->GetFSM()->ChangeState(OrderPizza::Instance());

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

OrderPizza* OrderPizza::Instance()
{
    static OrderPizza instance;

    return &instance;
}


void OrderPizza::Enter(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�������! ���ڸ� �Ծ�߰ھ�!!";
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
        pStudent->ID(),        //ID of sender
        ent_PizzaStoreOwner,   //ID of recipient
        Msg_DeliverMePizza,    //the message
        NO_ADDITIONAL_INFO);
}


void OrderPizza::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "���� �ֹ� ��..";
}


void OrderPizza::Exit(Student* pStudent)
{
}


bool OrderPizza::OnMessage(Student* pStudent, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_PizzaStoreNotResponse:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pStudent->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) <<
            ": ���� �� ������ ��ȭ�� �� �޳�.. �ٸ� ���������� ���ѸԾ�߰ڴ�";

        pStudent->SetPizzaDeclined();
        pStudent->GetFSM()->ChangeState(WaitAndEatPizza::Instance());
    }
    return true;
    case Msg_PizzaStoreResponse:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pStudent->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) <<
            ": ���� �ֹ� �Ϸ�!!";

        pStudent->SetPizzaAccpeted();
        pStudent->GetFSM()->ChangeState(WaitAndEatPizza::Instance());
    }
    return true;
    }
    return false;
}

WaitAndEatPizza* WaitAndEatPizza::Instance()
{
    static WaitAndEatPizza instance;

    return &instance;
}


void WaitAndEatPizza::Enter(Student* pStudent)
{
    if (!pStudent->Waiting())
    {
        if (!pStudent->PizzaAccepted())
        {
            Dispatch->DispatchMessage(2.5, //time delay
                pStudent->ID(),        //ID of sender
                ent_Student,   //ID of recipient
                Msg_PizzaArrived,    //the message
                NO_ADDITIONAL_INFO);
        }

        pStudent->SetWaiting();
    }
}


void WaitAndEatPizza::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "���� ����������~";
}


void WaitAndEatPizza::Exit(Student* pStudent)
{
    if(!pStudent->Waiting())
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� ���־���! �� �Ծ����ϴ�~";
}


bool WaitAndEatPizza::OnMessage(Student* pStudent, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_PizzaArrived:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pStudent->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "���� �����ߴ�!! �� �԰ڽ��ϴ�~";
        pStudent->BuyAndEatPizza();
        pStudent->SetNotWaiting();
        pStudent->GetFSM()->ChangeState(StayHomeAndRest::Instance());
    }
    return true;
    }
    return false;
}


PlayGame* PlayGame::Instance()
{
    static PlayGame instance;

    return &instance;
}


void PlayGame::Enter(Student* pStudent)
{
    if (pStudent->Location() != pcRoom)
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�����Ϸ����߰ڴ�~!!";
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
    if (pStudent->Location() != library)
    {
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "�����Ϸ�������...";
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

CallAndTalkToParent* CallAndTalkToParent::Instance()
{
    static CallAndTalkToParent instance;

    return &instance;
}


void CallAndTalkToParent::Enter(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "��? �θ������ ��ȭ�Դ�.";
}


void CallAndTalkToParent::Execute(Student* pStudent)
{
    switch (pStudent->Location())
    {
    case home:
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "��������? �� ���� ���̾�";
        break;
    case library:
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "��������? �� ���� �������̾�";
        break;
    case pcRoom:
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "��������? �� ���� PC���̾�";
        break;
    }

    pStudent->GetFSM()->RevertToPreviousState();
}


void CallAndTalkToParent::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "��ȭ ��~";
}


bool CallAndTalkToParent::OnMessage(Student* pStudent, const Telegram& msg)
{
    return false;
}