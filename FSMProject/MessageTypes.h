#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
    Msg_DeliverMePizza,
    Msg_PizzaStoreNotResponse,
    Msg_PizzaStoreResponse,
    Msg_PizzaIsReady,
    Msg_PizzaArrived,
    Msg_RequestAccepted,
    Msg_RequestDeclined,
    Msg_RequestPizzaDeliver_ToStudent,
    Msg_RequestPizzaDeliver_ToSomeone,
    Msg_ArrivedDestination
};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
    case Msg_DeliverMePizza:
        return "���� ����ֹ� ��ȭ";
    case Msg_PizzaStoreNotResponse:
        return "���ڰ��� �� ����";
    case Msg_PizzaStoreResponse:
        return "���ڰ��� ����";
    case Msg_PizzaIsReady:
        return "���� ���� �Ϸ�";
    case Msg_PizzaArrived:
        return "���� ����";
    case Msg_RequestPizzaDeliver_ToStudent:
        return "���� ��� ��û(������: �л�)";
    case Msg_RequestPizzaDeliver_ToSomeone:
        return "���� ��� ��û(������: ������)";
    case Msg_RequestAccepted:
        return "���� ��� ��û ����";
    case Msg_RequestDeclined:
        return "���� ��� ��û ����";
    case Msg_ArrivedDestination:
        return "����� ����!";
    default:
        return "Not recognized!";
    }
}

#endif