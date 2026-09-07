#ifndef FAILEDSTATE_H
#define FAILEDSTATE_H

#include "QuestState.h"//because the pure virtual functions that i need to implement are defined here


class FailedState: public QuestState{
    public:
        void onUnlock();
        std::string getName();
        FailedState(QuestComponent* q);
        void onStart() ;
        void onComplete();
        void onFail();
};
#endif