#include "PizzaStoreOwnerOwnedStates.h"
#include "PizzaStoreOwner.h"
#include "Locations.h"
#include "State.h"
#include "EntityNames.h"
#include "CrudeTimer.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
double PizzaOrderChance() { return ((rand()) / (RAND_MAX + 1.0)); }

PSOGlobalState* PSOGlobalState::Instance()
{
    static PSOGlobalState instance;

    return &instance;
}


void PSOGlobalState::Execute(PizzaStoreOwner* pPSO)
{
    if ((PizzaOrderChance() < 0.2) &&
        pPSO->GetFSM()->isInState(*GoPizzaStore::Instance()))
    {
        pPSO->GetFSM()->ChangeState(MakePizza::Instance());
    }
}

bool PSOGlobalState::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    return false;
}

PSOStayHomeAndRest* PSOStayHomeAndRest::Instance()
{
    static PSOStayHomeAndRest instance;

    return &instance;
}


void PSOStayHomeAndRest::Enter(PizzaStoreOwner* pPSO)
{
    if (pPSO->Location() != home)
    {
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "집에 도착했어";

        pPSO->ChangeLocation(home);
    }
}


void PSOStayHomeAndRest::Execute(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "역시 집이 최고야";
    pPSO->DecreaseFatigue();
    if (pPSO->Rested())
    {
        pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
    }
}


void PSOStayHomeAndRest::Exit(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "충분히 쉬었어!! 힘이 나는군!!";
}


bool PSOStayHomeAndRest::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_DeliverMePizza:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pPSO->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) <<
            ": 지금은 부재중입니다. 다음에 다시 연락해주세요.";

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pPSO->ID(),        //ID of sender
            ent_Student,   //ID of recipient
            Msg_PizzaStoreNotResponse,    //the message
            NO_ADDITIONAL_INFO);
    }
    return true;
    }
    return false;
}

GoPizzaStore* GoPizzaStore::Instance()
{
    static GoPizzaStore instance;

    return &instance;
}


void GoPizzaStore::Enter(PizzaStoreOwner* pPSO)
{
    if (pPSO->Location() != pizzaStore)
    {
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "오늘 피자장사는 잘 됐으면 좋겠군!!";

        pPSO->ChangeLocation(pizzaStore);
    }
}


void GoPizzaStore::Execute(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "피자 주문은 언제 오려나...";
    pPSO->IncreaseFatigue();
    if (pPSO->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "어휴 지친다..";
        pPSO->GetFSM()->ChangeState(PSOStayHomeAndRest::Instance());
    }
}


void GoPizzaStore::Exit(PizzaStoreOwner* pPSO)
{
}


bool GoPizzaStore::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_DeliverMePizza:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pPSO->ID()) << " at time: "
            << Clock->GetCurrentTime();

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pPSO->ID(),        //ID of sender
            ent_Student,   //ID of recipient
            Msg_PizzaStoreResponse,    //the message
            NO_ADDITIONAL_INFO);

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) <<
            ": 네 전화받았습니다. 피자 금방 준비해드리겠습니다!";

        pPSO->GetOrder(true);
        pPSO->GetFSM()->ChangeState(MakePizza::Instance());
    }
    return true;
    }

    return false;
}

MakePizza* MakePizza::Instance()
{
    static MakePizza instance;

    return &instance;
}


void MakePizza::Enter(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "피자를 만들어보실까!!";
    if (!pPSO->IsCooking())
    {
        pPSO->SetCooking();
        Dispatch->DispatchMessage(1.0,                  //time delay
            pPSO->ID(),           //sender ID
            pPSO->ID(),           //receiver ID
            Msg_PizzaIsReady,        //msg
            NO_ADDITIONAL_INFO);
    }
}


void MakePizza::Execute(PizzaStoreOwner* pPSO)
{
    SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "맛있는 피자를 만드는 중..";
}


void MakePizza::Exit(PizzaStoreOwner* pPSO)
{
}


bool MakePizza::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_DeliverMePizza:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pPSO->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) <<
            ": 지금은 주문이 밀렸습니다. 다음에 다시 연락해주세요.";

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pPSO->ID(),        //ID of sender
            ent_Student,   //ID of recipient
            Msg_PizzaStoreNotResponse,    //the message
            NO_ADDITIONAL_INFO);
    }
    return true;
    case Msg_PizzaIsReady:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pPSO->ID()) << " at time: "
            << Clock->GetCurrentTime();
        
        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) <<
            ": 피자 완성! 배달 요청도 해야겠다.";
        pPSO->FinishCooking();
        pPSO->GetFSM()->ChangeState(RequestDeliver::Instance());
    }
    return true;
    }

    return false;
}

RequestDeliver* RequestDeliver::Instance()
{
    static RequestDeliver instance;

    return &instance;
}


void RequestDeliver::Enter(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "피자 배달을 요청하자";
    if (pPSO->IsForStudent())
    {
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,                  //time delay
            pPSO->ID(),           //sender ID
            ent_Delivery,           //receiver ID
            Msg_RequestPizzaDeliver_ToStudent,        //msg
            NO_ADDITIONAL_INFO);
    }
    else
    {
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,                  //time delay
            pPSO->ID(),           //sender ID
            ent_Delivery,           //receiver ID
            Msg_RequestPizzaDeliver_ToSomeone,        //msg
            NO_ADDITIONAL_INFO);
    }
}


void RequestDeliver::Execute(PizzaStoreOwner* pPSO)
{
}


void RequestDeliver::Exit(PizzaStoreOwner* pPSO)
{
}


bool RequestDeliver::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_RequestAccepted:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pPSO->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) <<
            ": 배달 요청 성공! 다시 주문 받으러가야겠다.";
        pPSO->ReadyForOrder();
        pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
    }
    return true;
    case Msg_RequestDeclined:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pPSO->ID()) << " at time: "
            << Clock->GetCurrentTime();

        if (pPSO->IsForStudent())
        {
            Dispatch->DispatchMessage(1.5,                  //time delay
                pPSO->ID(),           //sender ID
                ent_Student,           //receiver ID
                Msg_PizzaArrived,        //msg
                NO_ADDITIONAL_INFO);
        }
        else
        {
            Dispatch->DispatchMessage(1.5,                  //time delay
                pPSO->ID(),           //sender ID
                ent_Student,           //receiver ID
                Msg_PizzaArrived,        //msg
                NO_ADDITIONAL_INFO);
        }

        SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) <<
            ": 배달 요청 실패! 다른 배달부한테 부탁해야겠다";
        pPSO->ReadyForOrder();
        pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
    }
    return true;
    }

    return false;
}