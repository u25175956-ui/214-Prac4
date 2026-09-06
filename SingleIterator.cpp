#include "SingleIterator.h"

SingleIterator::SingleIterator(QuestComponent* node) : node(node), done(false) {
}

SingleIterator::~SingleIterator() {
}

void SingleIterator::first() {
    done = false;
}

void SingleIterator::next() {
    done = true;
}

bool SingleIterator::isDone() const {
    return done;
}

QuestComponent* SingleIterator::current() const {
    return done ? 0 : node;
}