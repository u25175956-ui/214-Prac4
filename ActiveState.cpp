#include "ActiveState.h"
#include "QuestComponent.h"
#include "FailedState.h"
#include "CompleteState.h"
//need to also include the state which we will be going to next

ActiveState::ActiveState(QuestComponent* q): QuestState(q){}

std::string ActiveState::getName(){
    return "State: Active";
}

void ActiveState::onFail(){
    //we use this state to switch to "Failed State"
    quest->setState(new FailedState(quest));//takes us to the failed state part of the class
}

void ActiveState::onComplete(){
    quest->setState(new CompleteState(quest));
}

void ActiveState::onUnlock(){}

void ActiveState::onStart(){}