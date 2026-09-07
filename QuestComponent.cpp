#include "QuestComponent.h"
#include <iostream>

QuestComponent::QuestComponent(const std::string& name) : name(name) {}

QuestComponent::~QuestComponent() {}

const std::string& QuestComponent::getName() const { return name; }

void QuestComponent::indent(int depth) const {
    for (int i = 0; i < depth; ++i) std::cout << "  ";
}