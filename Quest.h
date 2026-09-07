#ifndef QUEST_H
#define QUEST_H
#include "QuestGroup.h"

/**
 * @brief Lowest Composite: a quest made of Objectives.
 *
 * The node the State milestone will attach a lifecycle to, and the node the
 * Decorator milestone will wrap.
 */
class Quest : public QuestGroup {
public:
    Quest(const std::string& name, int questId);
    virtual ~Quest();
    int getQuestId() const;

    /** @return true when every objective below is satisfied. No type checks. */
    bool allObjectivesSatisfied() const;

    /** @brief Completes every objective, then announces the XP awarded. */
    virtual void complete();

    /** @return 1 - a quest counts itself; groups above sum these. */
    virtual int countQuests() const;

protected:
    virtual std::string kindLabel() const;
    virtual void reportOwnDetail() const;

private:
    int questId;
};
#endif