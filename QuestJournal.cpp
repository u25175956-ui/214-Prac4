#include "QuestJournal.h"
#include <iostream>

QuestJournal::QuestJournal(const std::string& title) : title(title), root(0) {}

QuestJournal::~QuestJournal() {}

void QuestJournal::setRoot(QuestComponent* r) { root = r; }

QuestComponent* QuestJournal::getRoot() const { return root; }

void QuestJournal::printTree() const {
    std::cout << "\n===== " << title << " =====\n";
    if (root == 0) { std::cout << "  (no campaign loaded)\n"; return; }
    root->reportStatus(0);
    std::cout << "  total xp available: " << root->getReward()
              << "   quests: " << root->countQuests() << "\n";
}

int QuestJournal::totalReward() const { return root == 0 ? 0 : root->getReward(); }
int QuestJournal::questCount() const { return root == 0 ? 0 : root->countQuests(); }
void QuestJournal::beginAdventure() { if (root != 0) root->start(); }