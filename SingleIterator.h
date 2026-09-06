#ifndef SINGLEITERATOR_H
#define SINGLEITERATOR_H

#include "QuestIterator.h"

class QuestComponent;

class SingleIterator : public QuestIterator {
private:
    QuestComponent* node;
    bool done;

public:
    explicit SingleIterator(QuestComponent* node);
    virtual ~SingleIterator();

    virtual void first();
    virtual void next();
    virtual bool isDone() const;
    virtual QuestComponent* current() const;
};

#endif