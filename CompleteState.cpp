#include "CompleteState.h"

CompleteState::CompleteState(QuestComponent* q): QuestState(q){}

std::string CompleteState::getName(){
    return "State: Complete";
}

void CompleteState::onFail(){}

void CompleteState::onComplete(){}

void CompleteState::onStart(){}

void CompleteState::onUnlock(){}