#ifndef LOCKEDSTATE_H
#define LOCKEDSTATE_H
#include "QuestState.h"
#include "AvailableState.h"
#include "ActiveState.h"

class LockedState: public QuestState{
    public:
        void onUnlock();
        void onStart() ;
        std::string getName();
        LockedState(QuestComponent* q);
        void onFail();
        void onComplete();
};


#endif