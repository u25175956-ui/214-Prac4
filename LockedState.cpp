#include "LockedState.h"//has the QuestState, ActiveState and AvailableState already included in the .h file
#include "QuestComponent.h"
#include "AvailableState.h"

LockedState::LockedState(QuestComponent* q): QuestState(q){}

std::string LockedState::getName(){
    return "State: Locked ";
}

void LockedState::onStart(){
    //quest->setState(new ActiveState(this->quest));
}

void LockedState::onUnlock(){
    quest->setState(new AvailableState(this->quest));
}

void LockedState::onFail(){}

void LockedState::onComplete(){}