#ifndef STORYORDERITERATOR_H
#define STORYORDERITERATOR_H

#include "QuestIterator.h"

class QuestGroup;

class StoryOrderIterator : public QuestIterator {
private:
    QuestGroup* group;
    int index;
    QuestIterator* childIt;
    bool selfReturned;

    void enterChild();

public:
    explicit StoryOrderIterator(QuestGroup* group);
    virtual ~StoryOrderIterator();

    virtual void first();
    virtual void next();
    virtual bool isDone() const;
    virtual QuestComponent* current() const;
};

#endif