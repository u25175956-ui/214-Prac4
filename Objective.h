#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "QuestComponent.h"

/**
 * @brief GoF Leaf. The smallest unit of work; owns no children.
 *
 * Tracks progress toward a target. getReward() pays out only once satisfied,
 * which is what makes the aggregate xp figure change as the player advances.
 */
class Objective : public QuestComponent {
public:
    /**
     * @param name   Display name.
     * @param xp     XP awarded once satisfied. Negative values clamp to 0.
     * @param target Units of progress required. Values below 1 clamp to 1.
     */
    Objective(const std::string& name, int xp, int target);
    virtual ~Objective();

    /** @param amount Progress to add. Ignored once satisfied or failed. */
    void advance(int amount);

    int getProgress() const;
    int getTarget() const;

    virtual void start();
    virtual void complete();
    virtual void fail();
    virtual void reportStatus(int depth) const;
    virtual int getReward() const;
    virtual int countQuests() const;
    virtual bool isSatisfied() const;
    virtual QuestIterator* createIterator();

private:
    int xp;
    int progress;
    int target;
    bool satisfied;
    bool failed;
};

#endif