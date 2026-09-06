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
    virtual void reportStatus(int depth) const;
    virtual int getReward() const;
    virtual int countQuests() const;
    virtual bool isSatisfied() const;
    virtual QuestIterator* createIterator();
};

#endif