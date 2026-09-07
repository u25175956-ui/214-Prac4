#ifndef QUESTLINE_H
#define QUESTLINE_H
#include "QuestGroup.h"

/** @brief Middle Composite: a themed chain of quests from one giver. */
class Questline : public QuestGroup {
public:
    Questline(const std::string& name, const std::string& giver);
    virtual ~Questline();
    const std::string& getGiver() const;
protected:
    virtual std::string kindLabel() const;
    virtual void reportOwnDetail() const;
private:
    std::string giver;
};
#endif