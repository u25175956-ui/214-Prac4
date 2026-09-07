#ifndef CONCRETEDECORATORS_H
#define CONCRETEDECORATORS_H

#include "QuestDecorator.h"

class TimedQuest : public QuestDecorator {
private:
    int limitSeconds;
    int elapsed;

public:
    TimedQuest(QuestComponent* wrapped, int limitSeconds);
    ~TimedQuest();

    virtual void start();
    void tick(int seconds);
};

class BonusRewardQuest : public QuestDecorator {
private:
    double multiplier;

public:
    BonusRewardQuest(QuestComponent* wrapped, double multiplier);
    ~BonusRewardQuest();

    virtual int getReward() const;
};

class StealthQuest : public QuestDecorator {
private:
    bool detected;

public:
    StealthQuest(QuestComponent* wrapped);
    virtual ~StealthQuest();

    virtual void fail();
    void setDetected(bool detected);
};

class HardcoreQuest : public QuestDecorator {
private:
    int livesLeft;

public:
    HardcoreQuest(QuestComponent* wrapped, int livesLeft);
    virtual ~HardcoreQuest();

    virtual void fail();
};

#endif