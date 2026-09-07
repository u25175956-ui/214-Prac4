//the state design pattern
#ifndef QUESTSTATE_H
#define QUESTSTATE_H

#include <string>
#include "QuestComponent.h"
class QuestComponent;
//although the QuestComponent is the composite pattern, it serves as the context (the guy that holds the current state and delegates its work to that state) for state

class QuestState{
    protected:
        QuestComponent* quest;

    public:
        QuestState(QuestComponent* q);//our constructor
        virtual std::string getName() =0;
        virtual void onStart() =0;
        virtual void onComplete() =0;
        virtual void onFail() =0;
        virtual void onUnlock() =0;
        virtual ~QuestState();
};

#endif//class definition done