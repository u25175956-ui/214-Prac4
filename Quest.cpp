#include "Quest.h"
#include "QuestState.h"
#include "LockedState.h"
#include <iostream>


Quest::Quest(const std::string& name, int questId)
    : QuestGroup(name), questId(questId)
{
    setState(new LockedState(this));
}

Quest::~Quest() {}
int Quest::getQuestId() const { return questId; }

bool Quest::allObjectivesSatisfied() const { return isSatisfied(); }

void Quest::start() {
    if (state == 0) return;

    QuestState* oldState = state;

    state->onStart();
// Ava -> Active
    if (state != oldState && getStateName() == "State: Active") {
        QuestGroup::start();
    }
}

void Quest::complete() {
    if (state == 0) return;

    QuestState* oldState = state;

    state->onComplete();

    
     // Active -> Complete
     
    if (state != oldState && getStateName() == "State: Complete") {
        QuestGroup::complete();

        std::cout << "  quest complete: " << name
                  << " (#" << questId
                  << ") awarding " << getReward()
                  << " xp\n";
    }
}

void Quest::fail() {
    if (state == 0) return;

    QuestState* oldState = state;

    state->onFail();

    // Active-> Fail
    if (state != oldState && getStateName() == "State: Failed") {
        QuestGroup::fail();
    }
}

void Quest::unlock() {
    if (state == 0) return;

    state->onUnlock();
}


int Quest::countQuests() const { return 1; }
std::string Quest::kindLabel() const { return "Quest"; }
void Quest::reportOwnDetail() const { std::cout << "  id=" << questId; }