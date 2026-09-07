#include <iostream>

#include "Campaign.h"
#include "Questline.h"
#include "Quest.h"
#include "Objective.h"
#include "QuestJournal.h"
#include "QuestComponent.h"
#include "QuestIterator.h"
#include "ConcreteDecorators.h"

static void printFullTraversal(const std::string& label, QuestComponent* root) {
    std::cout << "\n-- " << label << " --\n";
    QuestIterator* it = root->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        QuestComponent* node = it->current();
        if (node != 0) {
            std::cout << "  visiting: " << node->getName()
                       << "  [" << node->getStateName() << "]\n";
        }
    }
    delete it;
}

int main() {
    // ---------------------------------------------------------------
    // 1. Build the hierarchy (Composite): Campaign -> Questline -> Quest -> Objective
    // ---------------------------------------------------------------
    Campaign* campaign = new Campaign("The Shattered Realm", 1);

    Questline* elderPath  = new Questline("Elder's Path", "Elder Rowan");
    Questline* smithTrials = new Questline("Smith's Trials", "Blacksmith Dorn");
    campaign->add(elderPath);
    campaign->add(smithTrials);

    // Keep raw pointers to the Quest nodes so we can reach Quest-specific
    // API (unlock(), getQuestId()) that isn't part of the QuestComponent
    // interface and therefore isn't forwarded by a decorator.
    Quest* gatherHerbsRaw   = new Quest("Gather Herbs", 101);
    Quest* defeatBanditsRaw = new Quest("Defeat Bandits", 102);
    Quest* forgeBladeRaw    = new Quest("Forge Blade", 201);

    Objective* sunpetal  = new Objective("Collect Sunpetal", 20, 5);
    Objective* moonleaf  = new Objective("Collect Moonleaf", 20, 3);
    gatherHerbsRaw->add(sunpetal);
    gatherHerbsRaw->add(moonleaf);

    Objective* slayBandits = new Objective("Slay bandits", 50, 3);
    defeatBanditsRaw->add(slayBandits);

    Objective* mineOre     = new Objective("Mine ore", 15, 4);
    Objective* smithBlade  = new Objective("Smith the blade", 60, 1);
    forgeBladeRaw->add(mineOre);
    forgeBladeRaw->add(smithBlade);

    // ---------------------------------------------------------------
    // 2. Decorate (Decorator) - stacked, runtime responsibilities.
    // ---------------------------------------------------------------
    // Gather Herbs: a timer wraps a stealth check. The quest only truly
    // fails when the timer runs out *and* the player has been detected.
    StealthQuest* gatherHerbsStealth = new StealthQuest(gatherHerbsRaw);
    TimedQuest*   gatherHerbsTimed   = new TimedQuest(gatherHerbsStealth, 60);

    // Defeat Bandits: bonus reward for the extra risk, then a hardcore
    // "lives" buffer stacked on top so a single failure isn't fatal.
    BonusRewardQuest* defeatBanditsBonus    = new BonusRewardQuest(defeatBanditsRaw, 1.5);
    HardcoreQuest*     defeatBanditsHard    = new HardcoreQuest(defeatBanditsBonus, 2);

    // Forge Blade is left undecorated to show the tree happily mixes
    // decorated and plain components through the same QuestComponent*.
    elderPath->add(gatherHerbsTimed);
    elderPath->add(defeatBanditsHard);
    smithTrials->add(forgeBladeRaw);

    // ---------------------------------------------------------------
    // 3. Journal + first report.
    // ---------------------------------------------------------------
    QuestJournal journal("Shattered Realm Quest Journal");
    journal.setRoot(campaign);
    journal.printTree();

    // ---------------------------------------------------------------
    // 4. State (unlock the quests, then begin the adventure).
    // Locked -[unlock]-> Available -[start]-> Active
    // ---------------------------------------------------------------
    std::cout << "\n-- Unlocking quests --\n";
    gatherHerbsRaw->unlock();
    defeatBanditsRaw->unlock();
    forgeBladeRaw->unlock();

    journal.beginAdventure();  // Campaign::start() -> recurses through the tree,
                                // driving every Quest from Available to Active
                                // (and, in turn, resetting each Objective).

    std::cout << "\ngatherHerbsTimed state:   " << gatherHerbsTimed->getStateName() << "\n";
    std::cout << "defeatBanditsHard state:  " << defeatBanditsHard->getStateName() << "\n";
    std::cout << "forgeBladeRaw state:      " << forgeBladeRaw->getStateName() << "\n";

    // ---------------------------------------------------------------
    // 5. Iterator - two independent traversals of the same live structure.
    // ---------------------------------------------------------------
    printFullTraversal("Traversal A (full story order)", campaign);

    QuestIterator* travB = campaign->createIterator();
    travB->first();
    std::cout << "\n-- Traversal B (stepped independently, one node only) --\n";
    if (!travB->isDone() && travB->current() != 0) {
        std::cout << "  Traversal B is parked at: " << travB->current()->getName() << "\n";
    }
    printFullTraversal("Traversal A again (already ran to completion earlier - fresh run)", campaign);
    std::cout << "  Traversal B is STILL parked at: "
              << (travB->current() != 0 ? travB->current()->getName() : "(done)")
              << "  -- proving the two iterators are independent\n";
    delete travB;

    // ---------------------------------------------------------------
    // 6. Drive progress on the Objectives (the leaves of the Composite).
    // ---------------------------------------------------------------
    std::cout << "\n-- Making progress --\n";
    sunpetal->advance(5);
    moonleaf->advance(3);
    slayBandits->advance(2);   // not yet satisfied
    mineOre->advance(4);
    smithBlade->advance(1);

    // ---------------------------------------------------------------
    // 7. Decorator behaviour in normal play.
    // ---------------------------------------------------------------
    std::cout << "\n-- Timer runs out on Gather Herbs, but stealth protects it --\n";
    gatherHerbsTimed->tick(70);   // limit was 60s -> triggers an internal fail()
    std::cout << "  gatherHerbsTimed state after timeout (undetected): "
              << gatherHerbsTimed->getStateName() << "\n";

    std::cout << "\n-- Player gets spotted --\n";
    gatherHerbsStealth->setDetected(true);
    gatherHerbsTimed->fail();
    std::cout << "  gatherHerbsTimed state after being detected: "
              << gatherHerbsTimed->getStateName() << "\n";

    std::cout << "\n-- Defeat Bandits takes hits, protected by its hardcore buffer --\n";
    defeatBanditsHard->fail();  // lives 2 -> 1, absorbed
    std::cout << "  defeatBanditsHard state after 1st hit: "
              << defeatBanditsHard->getStateName() << "\n";
    defeatBanditsHard->fail();  // lives 1 -> 0, propagates
    std::cout << "  defeatBanditsHard state after 2nd hit: "
              << defeatBanditsHard->getStateName() << "\n";

    // ---------------------------------------------------------------
    // 8. Complete the quest that succeeded, showing the bonus reward.
    // ---------------------------------------------------------------
    std::cout << "\n-- Completing Forge Blade --\n";
    std::cout << "  reward before completion: " << forgeBladeRaw->getReward() << " xp\n";
    forgeBladeRaw->complete();
    std::cout << "  forgeBladeRaw state: " << forgeBladeRaw->getStateName() << "\n";

    // ---------------------------------------------------------------
    // 9. Structural change at runtime: reassign a quest between groups.
    // ---------------------------------------------------------------
    std::cout << "\n-- Structural change: Defeat Bandits is reassigned to Smith's Trials --\n";
    if (elderPath->remove(defeatBanditsHard)) {
        smithTrials->add(defeatBanditsHard);
        std::cout << "  moved (elderPath no longer owns it; smithTrials now does)\n";
    }

    // ---------------------------------------------------------------
    // 10. Final report.
    // ---------------------------------------------------------------
    journal.printTree();
    std::cout << "\nTotal XP available: " << journal.totalReward()
              << "   Total quests: " << journal.questCount() << "\n";

    // ---------------------------------------------------------------
    // 11. Cleanup. Deleting the Campaign recursively deletes every
    // Questline, Quest, Decorator and Objective it (transitively) owns.
    // ---------------------------------------------------------------
    delete campaign;

    return 0;
}