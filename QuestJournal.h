#ifndef QUESTJOURNAL_H
#define QUESTJOURNAL_H

#include <string>
#include "QuestComponent.h"

// NOT YET IMPLEMENTED - added in the Iterator milestone, do not add now:
//   void listStoryOrder();   // walks a StoryOrderIterator
//   void listAvailable();    // walks an AvailableQuestIterator
// Both obtain their iterator from root->createIterator(). The journal must
// never call getChild()/childCount() to traverse - that would defeat Iterator.

/**
 * @brief Client of the Composite tree. Not part of the tree itself.
 *
 * Holds the root as a NON-OWNING pointer: main() creates the campaign and
 * deletes it. The journal only ever calls QuestComponent operations, so it
 * cannot tell a Campaign from an Objective - which is the point.
 */
class QuestJournal {
public:
    /** @param title Heading printed above the tree. */
    explicit QuestJournal(const std::string& title);

    /** @brief Deletes nothing; the root is not owned. */
    ~QuestJournal();

    /** @param root Campaign to report on. Non-owning; must outlive the journal. */
    void setRoot(QuestComponent* root);

    QuestComponent* getRoot() const;

    /** @brief Prints the whole tree, then the aggregate totals. */
    void printTree() const;

    /** @return Total XP earned across the tree, or 0 when no root is set. */
    int totalReward() const;

    /** @return Number of quests in the tree, or 0 when no root is set. */
    int questCount() const;

    /** @brief Starts the campaign; the call recurses down on its own. */
    void beginAdventure();

private:
    QuestJournal(const QuestJournal&);
    QuestJournal& operator=(const QuestJournal&);

    std::string title;
    QuestComponent* root; ///< non-owning
};

#endif