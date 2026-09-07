#include "QuestComponent.h"
#include "QuestState.h"
#include <iostream>

QuestComponent::QuestComponent(const std::string& name) : name(name), state(0) {}

QuestComponent::~QuestComponent() {
    delete state;
    state = 0;
}

const std::string& QuestComponent::getName() const { return name; }

void QuestComponent::indent(int depth) const {
    for (int i = 0; i < depth; ++i) std::cout << "  ";
}

void QuestComponent::setState(QuestState* newState) {
    if (state == newState) { return; }
    
    delete state;
    state = newState;
}

std::string QuestComponent::getStateName() const {
    return state == 0 ? "State: None" : state->getName();
}