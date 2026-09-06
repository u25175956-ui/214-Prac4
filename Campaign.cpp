#include "Campaign.h"
#include <iostream>

Campaign::Campaign(const std::string& name, int act) : QuestGroup(name), act(act) {}
Campaign::~Campaign() {}
int Campaign::getAct() const { return act; }

void Campaign::start() {
    std::cout << "=== Campaign begins: " << name << " (act " << act << ") ===\n";
    QuestGroup::start();
}

std::string Campaign::kindLabel() const { return "Campaign"; }
void Campaign::reportOwnDetail() const { std::cout << "  act=" << act; }