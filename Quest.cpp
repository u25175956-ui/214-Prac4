#include "Quest.h"
#include <iostream>

Quest::Quest(const std::string& name, int questId) : QuestGroup(name), questId(questId) {}
Quest::~Quest() {}
int Quest::getQuestId() const { return questId; }

bool Quest::allObjectivesSatisfied() const { return isSatisfied(); }

void Quest::complete() {
    QuestGroup::complete();
    std::cout << "  quest complete: " << name << " (#" << questId
              << ") awarding " << getReward() << " xp\n";
}

int Quest::countQuests() const { return 1; }
std::string Quest::kindLabel() const { return "Quest"; }
void Quest::reportOwnDetail() const { std::cout << "  id=" << questId; }