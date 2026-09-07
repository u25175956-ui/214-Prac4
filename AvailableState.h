#ifndef AVAILABLESTATE_H
#define AVAILABLESTATE_H

#include "QuestState.h"//because the pure virtual functions that i need to implement are defined here
#include "ActiveState.h"


class AvailableState: public QuestState{
    public:
        void onStart();
        std::string getName();
        AvailableState(QuestComponent* q);
        void onComplete();
        void onFail();
        void onUnlock() ;
};

#endif