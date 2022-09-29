#include "PizzaStoreOwnerOwnedStates.h"
#include "PizzaStoreOwner.h"
#include "Locations.h"
#include "State.h"
#include "EntityNames.h"

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
}


void PSOStayHomeAndRest::Exit(PizzaStoreOwner* pPSO)
{
}


bool PSOStayHomeAndRest::OnMessage(PizzaStoreOwner* pPSO, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}