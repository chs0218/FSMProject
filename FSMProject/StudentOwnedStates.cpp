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
        << "이제 집에서 좀 나가볼까?";*/
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
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "배고프다! 피자를 먹어야겠어!!";
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
        pStudent->ID(),        //ID of sender
        ent_PizzaStoreOwner,   //ID of recipient
        Msg_DeliverMePizza,    //the message
        NO_ADDITIONAL_INFO);
}


void OrderPizza::Execute(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "피자 주문 중..";
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
            ": 뭐야 이 피자집 전화를 안 받네.. 다른 피자집에서 시켜먹어야겠다";

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
            ": 피자 주문 완료!!";

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
        << "피자 언제오려나~";
}


void WaitAndEatPizza::Exit(Student* pStudent)
{
    if(!pStudent->Waiting())
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "피자 맛있었다! 잘 먹었습니다~";
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

        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "피자 도착했다!! 잘 먹겠습니다~";
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
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "게임하러가야겠다~!!";
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
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "공부하러가야해...";
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

CallAndTalkToParent* CallAndTalkToParent::Instance()
{
    static CallAndTalkToParent instance;

    return &instance;
}


void CallAndTalkToParent::Enter(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "어? 부모님한테 전화왔다.";
}


void CallAndTalkToParent::Execute(Student* pStudent)
{
    switch (pStudent->Location())
    {
    case home:
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "여보세요? 나 지금 집이야";
        break;
    case library:
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "여보세요? 나 지금 도서관이야";
        break;
    case pcRoom:
        std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": " << "여보세요? 나 지금 PC방이야";
        break;
    }

    pStudent->GetFSM()->RevertToPreviousState();
}


void CallAndTalkToParent::Exit(Student* pStudent)
{
    std::cout << "\n" << GetNameOfEntity(pStudent->ID()) << ": "
        << "전화 끝~";
}


bool CallAndTalkToParent::OnMessage(Student* pStudent, const Telegram& msg)
{
    return false;
}