#include "FailedState.h"


std::string FailedState::getName(){
    return "State: Failed.\nRerouting To An Available State";
}

void FailedState::onUnlock(){
    quest->setState(new AvailableState(quest));
}

FailedState::FailedState(QuestComponent* q): QuestState(q){}

void FailedState::onComplete(){}

void FailedState::onStart(){}

void FailedState::onFail(){}