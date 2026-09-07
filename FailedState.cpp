#include "FailedState.h"
#include "QuestComponent.h"
#include "AvailableState.h"

std::string FailedState::getName(){
    return "State: Failed";
}

void FailedState::onUnlock(){
    quest->setState(new AvailableState(quest));
}

FailedState::FailedState(QuestComponent* q): QuestState(q){}

void FailedState::onComplete(){}

void FailedState::onStart(){}

void FailedState::onFail(){}