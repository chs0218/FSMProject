#include "DeliveryOwnedState.h"
#include "Delivery.h"
#include "Locations.h"
#include "State.h"
#include "EntityNames.h"
#include "CrudeTimer.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"

double GetDeliverChance() { return ((rand()) / (RAND_MAX + 1.0)); }

DeliveryGlobalState* DeliveryGlobalState::Instance()
{
    static DeliveryGlobalState instance;

    return &instance;
}


void DeliveryGlobalState::Execute(Delivery* pDelivery)
{
    if ((GetDeliverChance() < 0.3) &&
        pDelivery->GetFSM()->isInState(*WaitDeliveryRequest::Instance()))
    {
        pDelivery->ReadyforDeliver(false);
        pDelivery->GetFSM()->ChangeState(GoDeliver::Instance());
    }
}

bool DeliveryGlobalState::OnMessage(Delivery* pDelivery, const Telegram& msg)
{
    return false;
}

DeliveryStayHomeAndRest* DeliveryStayHomeAndRest::Instance()
{
    static DeliveryStayHomeAndRest instance;

    return &instance;
}

void DeliveryStayHomeAndRest::Enter(Delivery* pDelivery)
{
    if (pDelivery->Location() != home)
    {
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "������ ����..";

        pDelivery->ChangeLocation(home);
    }
}


void DeliveryStayHomeAndRest::Execute(Delivery* pDelivery)
{
    std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "������ ���� ��~";
    pDelivery->DecreaseFatigue();
    if (pDelivery->Rested())
    {
        pDelivery->GetFSM()->ChangeState(WaitDeliveryRequest::Instance());
    }
}


void DeliveryStayHomeAndRest::Exit(Delivery* pDelivery)
{
}


bool DeliveryStayHomeAndRest::OnMessage(Delivery* pDelivery, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_RequestPizzaDeliver_ToStudent:
    case Msg_RequestPizzaDeliver_ToSomeone:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pDelivery->ID()) << " at time: "
            << Clock->GetCurrentTime();

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDelivery->ID(),        //ID of sender
            ent_PizzaStoreOwner,   //ID of recipient
            Msg_RequestDeclined,    //the message
            NO_ADDITIONAL_INFO);

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "���� ���̶� ��� ��û�� ���� �� ���ڴ�.";
    }
    return true;
    }
    return false;
}

WaitDeliveryRequest* WaitDeliveryRequest::Instance()
{
    static WaitDeliveryRequest instance;

    return &instance;
}

void WaitDeliveryRequest::Enter(Delivery* pDelivery)
{
    if (pDelivery->Location() != road)
    {
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ��� ����! ��û�� �� ������ ��ٸ���!";

        pDelivery->ChangeLocation(road);
    }
}


void WaitDeliveryRequest::Execute(Delivery* pDelivery)
{
    std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��޿�û�� ����������..?";
    pDelivery->IncreaseFatigue();
    if (pDelivery->Fatigued())
    {
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "���� ������..";
        pDelivery->GetFSM()->ChangeState(DeliveryStayHomeAndRest::Instance());
    }
}


void WaitDeliveryRequest::Exit(Delivery* pDelivery)
{
}


bool WaitDeliveryRequest::OnMessage(Delivery* pDelivery, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_RequestPizzaDeliver_ToStudent:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pDelivery->ID()) << " at time: "
            << Clock->GetCurrentTime();

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDelivery->ID(),        //ID of sender
            ent_PizzaStoreOwner,   //ID of recipient
            Msg_RequestAccepted,    //the message
            NO_ADDITIONAL_INFO);

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        pDelivery->ReadyforDeliver(true);
        pDelivery->GetFSM()->ChangeState(GoDeliver::Instance());

    }
    case Msg_RequestPizzaDeliver_ToSomeone:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pDelivery->ID()) << " at time: "
            << Clock->GetCurrentTime();

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDelivery->ID(),        //ID of sender
            ent_PizzaStoreOwner,   //ID of recipient
            Msg_RequestAccepted,    //the message
            NO_ADDITIONAL_INFO);

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        pDelivery->ReadyforDeliver(false);
        pDelivery->GetFSM()->ChangeState(GoDeliver::Instance());

    }
    return true;
    }
    return false;
}

GoDeliver* GoDeliver::Instance()
{
    static GoDeliver instance;

    return &instance;
}

void GoDeliver::Enter(Delivery* pDelivery)
{
    std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ��û�̴�! ���� ����ؾ�����?";
    
    Dispatch->DispatchMessage(1.5, //time delay
        pDelivery->ID(),        //ID of sender
        pDelivery->ID(),   //ID of recipient
        Msg_ArrivedDestination,    //the message
        NO_ADDITIONAL_INFO);

    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}


void GoDeliver::Execute(Delivery* pDelivery)
{
    std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ���� ��!!";
}


void GoDeliver::Exit(Delivery* pDelivery)
{
    std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ��!! �ٽ� ��޿�û ��ٸ���";
}


bool GoDeliver::OnMessage(Delivery* pDelivery, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_RequestPizzaDeliver_ToStudent:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pDelivery->ID()) << " at time: "
            << Clock->GetCurrentTime();

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDelivery->ID(),        //ID of sender
            ent_PizzaStoreOwner,   //ID of recipient
            Msg_RequestDeclined,    //the message
            NO_ADDITIONAL_INFO);

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ���̶� ����� �� �� �� ����.";
    }
    return true;
    case Msg_RequestPizzaDeliver_ToSomeone:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pDelivery->ID()) << " at time: "
            << Clock->GetCurrentTime();

        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
            pDelivery->ID(),        //ID of sender
            ent_PizzaStoreOwner,   //ID of recipient
            Msg_RequestDeclined,    //the message
            NO_ADDITIONAL_INFO);

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ���̶� ����� �� �� �� ����.";
    }
    return true;
    case Msg_ArrivedDestination:
    {
        std::cout << "\nMessage handled by " << GetNameOfEntity(pDelivery->ID()) << " at time: "
            << Clock->GetCurrentTime();

        if (pDelivery->IsForStudent())
        {
            Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                pDelivery->ID(),        //ID of sender
                ent_Student,   //ID of recipient
                Msg_PizzaArrived,    //the message
                NO_ADDITIONAL_INFO);
        }

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << "\n" << GetNameOfEntity(pDelivery->ID()) << ": " << "��� ����!!";

        pDelivery->GetFSM()->ChangeState(WaitDeliveryRequest::Instance());
        pDelivery->FinishDeliver();
        SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    return true;
    }
    return false;
}