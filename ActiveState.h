#ifndef ACTIVESTATE_H
#define ACTIVESTATE_H

#include "QuestState.h"//because the pure virtual functions that i need to implement are defined here


class ActiveState: public QuestState{
    public:
        void onComplete();
        std::string getName() ;
        void onFail() ;
        ActiveState(QuestComponent* q);
        void onStart();
        void onUnlock();
        
};

#endif//class definition of the concreteState: ActiveState done