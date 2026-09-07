#ifndef AVAILABLEQUESTITERATOR_H
#define AVAILABLEQUESTITERATOR_H

#include "QuestIterator.h"

class QuestComponent;

class AvailableQuestIterator : public QuestIterator {
private:
    QuestIterator* traversal;
    QuestComponent* currentNode;

    void skipUnavailable();

public:
    explicit AvailableQuestIterator(QuestComponent* root);
    virtual ~AvailableQuestIterator();

    virtual void first();
    virtual void next();
    virtual bool isDone() const;
    virtual QuestComponent* current() const;
};

#endif