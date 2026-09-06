#include "QuestDecorator.h"
#include "QuestIterator.h"

QuestDecorator::QuestDecorator(QuestComponent* wrapped)
    : QuestComponent(wrapped->getName()), wrapped(wrapped) {
}

QuestDecorator::~QuestDecorator() {
    delete wrapped;
}

void QuestDecorator::start() {
    wrapped->start();
}

void QuestDecorator::complete() {
    wrapped->complete();
}

void QuestDecorator::fail() {
    wrapped->fail();
}

void QuestDecorator::reportStatus(int depth) const {
    wrapped->reportStatus(depth);
}

int QuestDecorator::getReward() const {
    return wrapped->getReward();
}

int QuestDecorator::countQuests() const {
    return wrapped->countQuests();
}

bool QuestDecorator::isSatisfied() const {
    return wrapped->isSatisfied();
}

QuestIterator* QuestDecorator::createIterator() {
    return wrapped->createIterator();
}