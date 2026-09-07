#include "Objective.h"
#include "SingleIterator.h"
#include <iostream>

Objective::Objective(const std::string& name, int xp, int target)
    : QuestComponent(name), xp(xp < 0 ? 0 : xp), progress(0),
      target(target < 1 ? 1 : target), satisfied(false), failed(false) {}

Objective::~Objective() {}

void Objective::advance(int amount) {
    if (amount <= 0 || satisfied || failed) return;
    progress += amount;
    if (progress >= target) {
        progress = target;
        satisfied = true;
        std::cout << "    objective satisfied: " << name << "\n";
    }
}

int Objective::getProgress() const { return progress; }
int Objective::getTarget() const { return target; }

void Objective::start() { failed = false; }

void Objective::complete() { progress = target; satisfied = true; failed = false; }

void Objective::fail() { failed = true; satisfied = false; }

void Objective::reportStatus(int depth) const {
    indent(depth);
    std::cout << "- " << name << "  " << progress << "/" << target
              << "  xp=" << xp
              << (satisfied ? "  [done]" : (failed ? "  [failed]" : "")) << "\n";
}

int Objective::getReward() const { return satisfied ? xp : 0; }
int Objective::countQuests() const { return 0; }
bool Objective::isSatisfied() const { return satisfied; }

QuestIterator* Objective::createIterator() {
    return new SingleIterator(this);
}