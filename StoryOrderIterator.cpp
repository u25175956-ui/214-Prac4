#include "StoryOrderIterator.h"
#include "QuestGroup.h"

StoryOrderIterator::StoryOrderIterator(QuestGroup* group)
    : group(group), index(0), childIt(0) {

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

    enterChild();
}

void StoryOrderIterator::next() {

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

    return childIt == 0;
}

QuestComponent* StoryOrderIterator::current() const {

    if (childIt == 0) {
        return 0;
    }

    return childIt->current();
}