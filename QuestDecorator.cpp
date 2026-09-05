#include "QuestDecorator.h"
#include "QuestIterator.h"

QuestDecorator::QuestDecorator(QuestComponent* wrapped) : wrapped(wrapped) {
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

void QuestDecorator::reportStatus() {
    wrapped->reportStatus();
}

int QuestDecorator::getReward() {
    return wrapped->getReward();
}

QuestIterator* QuestDecorator::createIterator() {
    return wrapped->createIterator();
}