#include "AvailableState.h"
#include "QuestComponent.h"
#include "ActiveState.h"

std::string AvailableState::getName(){
    return "State: Available";
}

void AvailableState::onStart(){
    quest->setState(new ActiveState(quest));
}

AvailableState::AvailableState(QuestComponent* q): QuestState(q){}

void AvailableState::onComplete(){}

void AvailableState::onFail(){}

void AvailableState::onUnlock(){}