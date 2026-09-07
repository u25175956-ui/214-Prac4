#ifndef COMPLETESTATE_H
#define COMPLETESTATE_H
#include "QuestState.h"

class CompleteState: public QuestState{
    public:
        std::string getName();
        CompleteState(QuestComponent* q);
        void onFail();
        void onComplete();
        void onStart();
        void onUnlock();
};


#endif