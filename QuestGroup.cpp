#include "QuestGroup.h"
#include <iostream>

QuestGroup::QuestGroup(const std::string& name) : QuestComponent(name) {}

QuestGroup::~QuestGroup() {
    for (size_t i = 0; i < children.size(); ++i) delete children[i];
    children.clear();
}

void QuestGroup::add(QuestComponent* child) {
    if (child == 0 || child == this) return;
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i] == child) return;
    }
    children.push_back(child);
}

bool QuestGroup::remove(QuestComponent* child) {
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i] == child) {
            children.erase(children.begin() + i);
            return true;
        }
    }
    return false;
}

int QuestGroup::childCount() const { return static_cast<int>(children.size()); }

QuestComponent* QuestGroup::getChild(int index) const {
    if (index < 0 || index >= static_cast<int>(children.size())) return 0;
    return children[static_cast<size_t>(index)];
}

void QuestGroup::start() {
    for (size_t i = 0; i < children.size(); ++i) children[i]->start();
}

void QuestGroup::complete() {
    for (size_t i = 0; i < children.size(); ++i) children[i]->complete();
}

void QuestGroup::fail() {
    for (size_t i = 0; i < children.size(); ++i) children[i]->fail();
}

int QuestGroup::getReward() const {
    int total = 0;
    for (size_t i = 0; i < children.size(); ++i) total += children[i]->getReward();
    return total;
}

int QuestGroup::countQuests() const {
    int total = 0;
    for (size_t i = 0; i < children.size(); ++i) total += children[i]->countQuests();
    return total;
}

bool QuestGroup::isSatisfied() const {
    if (children.empty()) return false;
    for (size_t i = 0; i < children.size(); ++i) {
        if (!children[i]->isSatisfied()) return false;
    }
    return true;
}

void QuestGroup::reportOwnDetail() const {}

void QuestGroup::reportStatus(int depth) const {
    indent(depth);
    std::cout << "[" << kindLabel() << "] " << name
              << "  children=" << children.size()
              << "  xp=" << getReward();
    reportOwnDetail();
    std::cout << "\n";
    for (size_t i = 0; i < children.size(); ++i) children[i]->reportStatus(depth + 1);
}