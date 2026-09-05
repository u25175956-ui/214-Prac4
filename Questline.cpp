#include "Questline.h"
#include <iostream>

Questline::Questline(const std::string& name, const std::string& giver)
    : QuestGroup(name), giver(giver) {}
Questline::~Questline() {}
const std::string& Questline::getGiver() const { return giver; }
std::string Questline::kindLabel() const { return "Questline"; }
void Questline::reportOwnDetail() const { std::cout << "  giver=" << giver; }