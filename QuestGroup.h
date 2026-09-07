#ifndef QUESTGROUP_H
#define QUESTGROUP_H

#include <vector>
#include "QuestComponent.h"

/**
 * @brief GoF Composite. A node that owns children and recurses into them.
 *
 * Abstract: Campaign, Questline and Quest supply kindLabel() and any extra
 * detail line. Child management lives here rather than on QuestComponent
 * (the "safety" variant of Composite), so add() cannot be called on a leaf.
 *
 * OWNERSHIP CONTRACT
 *   add(c)     - this group takes ownership of c and will delete it.
 *   remove(c)  - releases c WITHOUT deleting; the caller owns it afterwards.
 *   ~QuestGroup deletes every child still held, so deleting the root
 *                releases the entire subtree exactly once.
 */
class QuestGroup : public QuestComponent {
public:
    explicit QuestGroup(const std::string& name);

    /** @brief Deletes every child still owned. */
    virtual ~QuestGroup();

    /**
     * @brief Takes ownership of a child.
     * @param child Ignored if nullptr, if it is this group, or if already held.
     */
    void add(QuestComponent* child);

    /**
     * @brief Releases a child without deleting it.
     * @return true if it was held; the caller then owns the pointer.
     */
    bool remove(QuestComponent* child);

    /** @return Number of direct children. */
    int childCount() const;

    /**
     * @param index Position in this group.
     * @return The child, or nullptr when index is out of range.
     *
     * Exists for the Iterator classes to walk the tree. Client code must not
     * use it to traverse - that is what createIterator() is for.
     */
    QuestComponent* getChild(int index) const;

    virtual void start();
    virtual void complete();
    virtual void fail();
    virtual int getReward() const;
    virtual int countQuests() const;
    virtual bool isSatisfied() const;
    virtual QuestIterator* createIterator();

protected:
    /** @return Short name of this group kind, e.g. "Questline". */
    virtual std::string kindLabel() const = 0;

    /** @brief Appends a subclass-specific detail to the status line. */
    virtual void reportOwnDetail() const;

    virtual void reportStatus(int depth) const;

    std::vector<QuestComponent*> children;
};

#endif