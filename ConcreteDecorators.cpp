#include "ConcreteDecorators.h"
#include <iostream>

// TimedQuestDecorator
TimedQuest::TimedQuest(QuestComponent* wrapped, int limitSeconds)
    : QuestDecorator(wrapped), limitSeconds(limitSeconds), elapsed(0) {
}

TimedQuest::~TimedQuest() {
}

void TimedQuest::start() {
    wrapped->start();
    elapsed = 0;
}

void TimedQuest::tick(int seconds) {
    elapsed += seconds;
    if (elapsed >= limitSeconds) {
        fail();
    }
}

//BonusRewardQuestDecorator
BonusRewardQuest::BonusRewardQuest(QuestComponent* wrapped, double multiplier)
    : QuestDecorator(wrapped), multiplier(multiplier) {
}

BonusRewardQuest::~BonusRewardQuest() {
}

int BonusRewardQuest::getReward() const {
    return static_cast<int>(wrapped->getReward() * multiplier);
}

// StealthQuestDecorator
StealthQuest::StealthQuest(QuestComponent* wrapped)
    : QuestDecorator(wrapped), detected(false) {
}

StealthQuest::~StealthQuest() {
}

void StealthQuest::fail() {
    if (detected) {
        wrapped->fail();
    }
}

void StealthQuest::setDetected(bool detected) {
    this->detected = detected;
}

// HardcoreQuestDecorator
HardcoreQuest::HardcoreQuest(QuestComponent* wrapped, int livesLeft)
    : QuestDecorator(wrapped), livesLeft(livesLeft) {
}

HardcoreQuest::~HardcoreQuest() {
}

void HardcoreQuest::fail() {
    livesLeft--;
    if (livesLeft <= 0) {
        wrapped->fail();
    }
}

