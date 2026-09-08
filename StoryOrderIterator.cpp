#include "StoryOrderIterator.h"
#include "QuestGroup.h"

StoryOrderIterator::StoryOrderIterator(QuestGroup* group)
    : group(group), index(0), childIt(0), selfReturned(false) {

    first();
}

StoryOrderIterator::~StoryOrderIterator() {
    delete childIt;
}

void StoryOrderIterator::enterChild() {

    delete childIt;
    childIt = 0;

    if (group == 0) {
        return;
    }

    if (index < group->childCount()) {

        QuestComponent* child =
            group->getChild(index);

        if (child != 0) {
            childIt = child->createIterator();
            childIt->first();
        }
    }
}

void StoryOrderIterator::first() {

    index = 0;
    selfReturned = false;
    delete childIt;
    childIt = 0;
}

void StoryOrderIterator::next() {

    if (!selfReturned) {
        selfReturned = true;
        enterChild();
        return;
    }

    if (childIt == 0) {
        return;
    }

    childIt->next();

    if (childIt->isDone()) {
        index++;
        enterChild();
    }
}

bool StoryOrderIterator::isDone() const {
    if (!selfReturned) {
        return false;
    }
    return childIt == 0;
}

QuestComponent* StoryOrderIterator::current() const {

    if (!selfReturned) {
        return group;
    }

    if (childIt == 0) {
        return 0;
    }

    return childIt->current();
}