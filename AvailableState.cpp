#include "AvailableState.h"

std::string AvailableState::getName(){
    return "State: Rerouting - Next Available State";
}

void AvailableState::onStart(){
    quest->setState(new ActiveState(quest));
}

AvailableState::AvailableState(QuestComponent* q): QuestState(q){}

void AvailableState::onComplete(){}

void AvailableState::onFail(){}

void AvailableState::onUnlock(){}