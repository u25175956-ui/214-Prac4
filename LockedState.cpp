#include "LockedState.h"//has the QuestState, ActiveState and AvailableState already included in the .h file

LockedState::LockedState(QuestComponent* q): QuestState(q){}

std::string LockedState::getName(){
    return "State: Locked.\nRerouting To An Available State";
}

void LockedState::onStart(){
    quest->setState(new ActiveState(this->quest));
}

void LockedState::onUnlock(){
    quest->setState(new AvailableState(this->quest));
}

void LockedState::onFail(){}

void LockedState::onComplete(){}