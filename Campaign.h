#ifndef CAMPAIGN_H
#define CAMPAIGN_H
#include "QuestGroup.h"

/** @brief Root Composite: the whole storyline for one act. */
class Campaign : public QuestGroup {
public:
    Campaign(const std::string& name, int act);
    virtual ~Campaign();
    int getAct() const;

    /** @brief Prints the act banner, then starts every questline below. */
    virtual void start();

protected:
    virtual std::string kindLabel() const;
    virtual void reportOwnDetail() const;

private:
    int act;
};
#endif