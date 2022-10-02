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
        return "피자 배달주문 전화";
    case Msg_PizzaStoreNotResponse:
        return "피자가게 무 응답";
    case Msg_PizzaStoreResponse:
        return "피자가게 응답";
    case Msg_PizzaIsReady:
        return "피자 제작 완료";
    case Msg_PizzaArrived:
        return "피자 도착";
    case Msg_RequestPizzaDeliver_ToStudent:
        return "피자 배달 요청(목적지: 학생)";
    case Msg_RequestPizzaDeliver_ToSomeone:
        return "피자 배달 요청(목적지: 누군가)";
    case Msg_RequestAccepted:
        return "피자 배달 요청 수락";
    case Msg_RequestDeclined:
        return "피자 배달 요청 거절";
    case Msg_ArrivedDestination:
        return "배달지 도착!";
    default:
        return "Not recognized!";
    }
}

#endif