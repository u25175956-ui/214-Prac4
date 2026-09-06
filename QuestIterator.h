#ifndef QUESTITERATOR_H
#define QUESTITERATOR_H

class QuestComponent;

class QuestIterator {
public:
    virtual ~QuestIterator() {}

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual QuestComponent* current() const = 0;
};

#endif