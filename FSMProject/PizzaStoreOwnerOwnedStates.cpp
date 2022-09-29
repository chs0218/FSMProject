#include "PizzaStoreOwnerOwnedStates.h"
#include "PizzaStoreOwner.h"
#include "Locations.h"
#include "State.h"
#include "EntityNames.h"

double RandFloat() { return ((rand()) / (RAND_MAX + 1.0)); }

PSOGlobalState* PSOGlobalState::Instance()
{
    static PSOGlobalState instance;

    return &instance;
}


void PSOGlobalState::Execute(PizzaStoreOwner* pPSO)
{
    if ((RandFloat() < 0.2) &&
        !pPSO->GetFSM()->isInState(*GetPizzaOrder::Instance()) &&
        !pPSO->GetFSM()->isInState(*PSOStayHomeAndRest::Instance()))
    {
        pPSO->GetFSM()->ChangeState(GetPizzaOrder::Instance());
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
        std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "����� ������!! ���� ���±�!!";
        pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
    }
}


void PSOStayHomeAndRest::Exit(PizzaStoreOwner* pPSO)
{
}


bool PSOStayHomeAndRest::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    //send msg to global message handler
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
    //send msg to global message handler
    return false;
}

GetPizzaOrder* GetPizzaOrder::Instance()
{
    static GetPizzaOrder instance;

    return &instance;
}


void GetPizzaOrder::Enter(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� �ֹ��̴�! ���ڸ� ������!";
}


void GetPizzaOrder::Execute(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���ִ� ���ڸ� ����� ��..";
    pPSO->GetFSM()->ChangeState(GoPizzaStore::Instance());
}


void GetPizzaOrder::Exit(PizzaStoreOwner* pPSO)
{
    std::cout << "\n" << GetNameOfEntity(pPSO->ID()) << ": " << "���� �ϼ�!! �߰� �ֹ��� ����..?";
}


bool GetPizzaOrder::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}