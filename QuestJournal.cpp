#include "QuestJournal.h"
#include "QuestIterator.h"
#include "AvailableQuestIterator.h"
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

//Story Order traversal
void QuestJournal::listStoryOrder() const {

    std::cout << "\n===== Story Order =====\n";

    if (root == 0) {
        std::cout << "  (no campaign loaded)\n";
        return;
    }

    QuestIterator* iterator = root->createIterator();

    for (iterator->first();
         !iterator->isDone();
         iterator->next()) {

        QuestComponent* current = iterator->current();

        if (current != 0) {
            std::cout << "  - "
                      << current->getName()
                      << " ["
                      << current->getStateName()
                      << "]\n";
        }
    }

    delete iterator;
}


// Available Quest Traversal
void QuestJournal::listAvailable() const {

    std::cout << "\n===== Available Quests =====\n";

    if (root == 0) {
        std::cout << "  (no campaign loaded)\n";
        return;
    }

    QuestIterator* iterator =
        new AvailableQuestIterator(root);

    for (iterator->first();
         !iterator->isDone();
         iterator->next()) {

        QuestComponent* current = iterator->current();

        if (current != 0) {
            std::cout << "  - "
                      << current->getName()
                      << "\n";
        }
    }

    delete iterator;
}