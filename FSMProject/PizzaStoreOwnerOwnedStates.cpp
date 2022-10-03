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
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� �����߾�";

        pPSO->ChangeLocation(home);
    }
}


void PSOStayHomeAndRest::Execute(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� ���� �ְ��";
    pPSO->DecreaseFatigue();
    if (pPSO->Rested())
    {
        pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
    }
}


void PSOStayHomeAndRest::Exit(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "����� ������!! ���� ���±�!!";
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
            ": ������ �������Դϴ�. ������ �ٽ� �������ּ���.";

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
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� �������� �� ������ ���ڱ�!!";

        pPSO->ChangeLocation(pizzaStore);
    }
}


void GoPizzaStore::Execute(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� �ֹ��� ���� ������...";
    pPSO->IncreaseFatigue();
    if (pPSO->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� ��ģ��..";
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
            ": �� ��ȭ�޾ҽ��ϴ�. ���� �ݹ� �غ��ص帮�ڽ��ϴ�!";

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
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���ڸ� �����Ǳ�!!";
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

    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���ִ� ���ڸ� ����� ��..";
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
            ": ������ �ֹ��� �зȽ��ϴ�. ������ �ٽ� �������ּ���.";

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
            ": ���� �ϼ�! ��� ��û�� �ؾ߰ڴ�.";
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
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� ����� ��û����";
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
            ": ��� ��û ����! �ٽ� �ֹ� ���������߰ڴ�.";
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
            ": ��� ��û ����! �ٸ� ��޺����� ��Ź�ؾ߰ڴ�";
        pPSO->ReadyForOrder();
        pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
    }
    return true;
    }

    return false;
}