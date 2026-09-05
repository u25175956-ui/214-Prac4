#ifndef QUESTDECORATOR_H
#define QUESTDECORATOR_H

#include "QuestComponent.h"

class QuestDecorator : public QuestComponent {
protected:
    QuestComponent* wrapped;

public:
    QuestDecorator(QuestComponent* wrapped);
    virtual ~QuestDecorator();

    virtual void start();
    virtual void complete();
    virtual void fail();
    virtual void reportStatus();
    virtual int getReward();
    virtual QuestIterator* createIterator();
};

#endif