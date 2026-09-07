#ifndef QUESTCOMPONENT_H
#define QUESTCOMPONENT_H

#include <string>

class QuestIterator;
class QuestState;

// NOT YET IMPLEMENTED - added in later milestones, do not add now:
//   - QuestState* state          (State milestone: replaces nothing here,
//                                 adds a protected member + setState())
//   - virtual QuestIterator* createIterator() const
//                                (Iterator milestone: pure virtual here,
//                                 QuestGroup returns a StoryOrderIterator,
//                                 Objective returns a null iterator)

/**
 * @brief GoF Component for the TaskForge quest tree.
 *
 * The single abstraction the client works through. A caller holding a
 * QuestComponent* cannot tell whether it has one Objective or an entire
 * Campaign, and never needs to.
 *
 * Ownership: a QuestComponent owns nothing by itself. QuestGroup owns its
 * children; see QuestGroup.h.
 */
class QuestComponent {
public:
    /** @param name Display name shown in the journal. */
    explicit QuestComponent(const std::string& name);

    /** @brief Virtual so deleting through a QuestComponent* is well defined. */
    virtual ~QuestComponent();

    /** @return This component's display name. */
    const std::string& getName() const;

    /** @brief Begins this component and, for a group, everything inside it. */
    virtual void start() = 0;

    /** @brief Marks this component finished, recursing for a group. */
    virtual void complete() = 0;

    /** @brief Marks this component failed, recursing for a group. */
    virtual void fail() = 0;

    /**
     * @brief Prints this component and its subtree.
     * @param depth Indentation level; a group passes depth+1 to its children.
     */
    virtual void reportStatus(int depth) const = 0;

    /**
     * @brief The recursive aggregate query.
     * @return XP earned so far: a leaf's own xp once satisfied, or the sum
     *         over a group's children.
     */
    virtual int getReward() const = 0;

    /** @return How many Quest nodes sit in this subtree. */
    virtual int countQuests() const = 0;

    /**
     * @return true when this component counts as finished. A leaf answers for
     *         itself; a group is satisfied only when every child is. This is
     *         what lets Quest check its objectives with no type inspection.
     */
    virtual bool isSatisfied() const = 0;

    virtual QuestIterator* createIterator() = 0;

     void setState(QuestState* newState);
    virtual std::string getStateName() const;

protected:
    /** @brief Writes 2*depth spaces. Shared by every reportStatus override. */
    void indent(int depth) const;

    std::string name;
 /** @brief Current State owned by this component. */
    QuestState* state;
private:
    QuestComponent(const QuestComponent&);
    QuestComponent& operator=(const QuestComponent&);
};

#endif