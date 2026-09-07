#include "AvailableQuestIterator.h"
#include "QuestComponent.h"

AvailableQuestIterator::AvailableQuestIterator(QuestComponent* root)
    : traversal(0), currentNode(0) {

    if (root != 0) {
        traversal = root->createIterator();
    }

    first();
}

AvailableQuestIterator::~AvailableQuestIterator() {
    delete traversal;
}

void AvailableQuestIterator::first() {

    currentNode = 0;

    if (traversal == 0) {
        return;
    }

    traversal->first();

    skipUnavailable();
}

void AvailableQuestIterator::next() {

    if (traversal == 0 || traversal->isDone()) {
        currentNode = 0;
        return;
    }

    traversal->next();

    skipUnavailable();
}

void AvailableQuestIterator::skipUnavailable() {

    currentNode = 0;

    while (traversal != 0 && !traversal->isDone()) {

        QuestComponent* candidate =
            traversal->current();

        if (candidate != 0 &&
            candidate->getStateName() == "State: Available") {

            currentNode = candidate;
            return;
        }

        traversal->next();
    }
}

bool AvailableQuestIterator::isDone() const {
    return currentNode == 0;
}

QuestComponent* AvailableQuestIterator::current() const {
    return currentNode;
}