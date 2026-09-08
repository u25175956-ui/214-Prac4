#include <iostream>

#include "Campaign.h"
#include "Questline.h"
#include "Quest.h"
#include "Objective.h"
#include "QuestJournal.h"
#include "QuestComponent.h"
#include "QuestIterator.h"
#include "AvailableQuestIterator.h"
#include "ConcreteDecorators.h"

/*
 * ---------------------------------------------------------
 * Helper functions
 * ---------------------------------------------------------
 */

 // put near the top of main.cpp
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string LOCKED  = "\033[90m";  // grey
    const std::string AVAIL   = "\033[33m";  // yellow/gold
    const std::string ACTIVE  = "\033[36m";  // cyan
    const std::string DONE    = "\033[32m";  // green
    const std::string FAILED  = "\033[31m";  // red
}

static std::string colorFor(const std::string& stateName) {
    if (stateName.find("Locked") != std::string::npos)   return Color::LOCKED;
    if (stateName.find("Available") != std::string::npos) return Color::AVAIL;
    if (stateName.find("Active") != std::string::npos)    return Color::ACTIVE;
    if (stateName.find("Complete") != std::string::npos)  return Color::DONE;
    if (stateName.find("Failed") != std::string::npos)    return Color::FAILED;
    return Color::RESET;
}

static void showMenu() {

    std::cout << "\n";
    std::cout << "==========================================\n";
    std::cout << "        TASKFORGE - PLAYER MENU\n";
    std::cout << "==========================================\n";

    std::cout << "1. View quest journal\n";
    std::cout << "2. View available quests\n";
    std::cout << "3. Unlock Gather Herbs\n";
    std::cout << "4. Unlock Defeat Bandits\n";
    std::cout << "5. Unlock Forge Blade\n";
    std::cout << "6. Start adventure\n";
    std::cout << "7. Complete objectives\n";
    std::cout << "8. Take damage on Defeat Bandits\n";
    std::cout << "9. Wait for Gather Herbs timer\n";
    std::cout << "10. Player gets detected\n";
    std::cout << "11. Complete Forge Blade\n";
    std::cout << "12. Move Defeat Bandits\n";
    std::cout << "13. View story-order traversal\n";
    std::cout << "0. Exit\n";

    std::cout << "==========================================\n";
    std::cout << "Choose an action: ";
}


static void showAvailableQuests(QuestComponent* root) {

    if (root == 0) {
        return;
    }

    QuestIterator* iterator =
        new AvailableQuestIterator(root);

    std::cout << "\n===== Available Quests =====\n";

    bool found = false;

    for (iterator->first();
         !iterator->isDone();
         iterator->next()) {

        QuestComponent* quest =
            iterator->current();

        if (quest != 0) {

            found = true;

            std::cout << "  - "
                      << quest->getName()
                      << "\n";
        }
    }

    if (!found) {
        std::cout << "  No quests are currently available.\n";
    }

    delete iterator;
}

static void showStoryOrder(QuestComponent* root) {

    if (root == 0) {
        return;
    }

    QuestIterator* iterator =
        root->createIterator();

    std::cout << "\n===== Story Order =====\n";

    for (iterator->first();
         !iterator->isDone();
         iterator->next()) {

        QuestComponent* node =
            iterator->current();

        if (node != 0) {

            std::cout << "  - " << node->getName()
                      << " [" << colorFor(node->getStateName())
                      << node->getStateName() << Color::RESET << "]\n";
        }
    }

    delete iterator;
}

/*
 * ---------------------------------------------------------
 * MAIN
 * ---------------------------------------------------------
 */

int main() {

    /*
     * =====================================================
     * 1. CREATE THE COMPOSITE HIERARCHY
     * =====================================================
     */

    Campaign* campaign =
        new Campaign("The Shattered Realm", 1);

    Questline* elderPath =
        new Questline(
            "Elder's Path",
            "Elder Rowan"
        );

    Questline* smithTrials =
        new Questline(
            "Smith's Trials",
            "Blacksmith Dorn"
        );

    campaign->add(elderPath);
    campaign->add(smithTrials);


    /*
     * =====================================================
     * 2. CREATE QUESTS
     * =====================================================
     */

    Quest* gatherHerbsRaw =
        new Quest(
            "Gather Herbs",
            101
        );

    Quest* defeatBanditsRaw =
        new Quest(
            "Defeat Bandits",
            102
        );

    Quest* forgeBladeRaw =
        new Quest(
            "Forge Blade",
            201
        );


    /*
     * =====================================================
     * 3. CREATE OBJECTIVES
     * =====================================================
     */

    Objective* sunpetal =
        new Objective(
            "Collect Sunpetal",
            20,
            5
        );

    Objective* moonleaf =
        new Objective(
            "Collect Moonleaf",
            20,
            3
        );

    gatherHerbsRaw->add(sunpetal);
    gatherHerbsRaw->add(moonleaf);


    Objective* slayBandits =
        new Objective(
            "Slay bandits",
            50,
            3
        );

    defeatBanditsRaw->add(slayBandits);


    Objective* mineOre =
        new Objective(
            "Mine ore",
            15,
            4
        );

    Objective* smithBlade =
        new Objective(
            "Smith the blade",
            60,
            1
        );

    forgeBladeRaw->add(mineOre);
    forgeBladeRaw->add(smithBlade);


    /*
     * =====================================================
     * 4. DECORATORS
     * =====================================================
     */

    StealthQuest* gatherHerbsStealth =
        new StealthQuest(
            gatherHerbsRaw
        );

    TimedQuest* gatherHerbsTimed =
        new TimedQuest(
            gatherHerbsStealth,
            60
        );


    BonusRewardQuest* defeatBanditsBonus =
        new BonusRewardQuest(
            defeatBanditsRaw,
            1.5
        );

    HardcoreQuest* defeatBanditsHard =
        new HardcoreQuest(
            defeatBanditsBonus,
            2
        );


    /*
     * Forge Blade remains undecorated.
     */

    elderPath->add(gatherHerbsTimed);
    elderPath->add(defeatBanditsHard);

    smithTrials->add(forgeBladeRaw);


    /*
     * =====================================================
     * 5. JOURNAL
     * =====================================================
     */

    QuestJournal journal(
        "Shattered Realm Quest Journal"
    );

    journal.setRoot(campaign);


    /*
     * =====================================================
     * 6. INTERACTIVE LOOP
     * =====================================================
     */

    bool running = true;

    while (running) {

        showMenu();

        int choice;

        std::cin >> choice;

        std::cout << "\n";


        switch (choice) {

        /*
         * -------------------------------------------------
         * VIEW JOURNAL
         * -------------------------------------------------
         */

        case 1:

            journal.printTree();

            break;


        /*
         * -------------------------------------------------
         * AVAILABLE QUEST ITERATOR
         * -------------------------------------------------
         */

        case 2:

            journal.listAvailable();

            break;


        /*
         * -------------------------------------------------
         * UNLOCK QUESTS
         * -------------------------------------------------
         */

        case 3:

            gatherHerbsRaw->unlock();

            std::cout
                << "Gather Herbs unlocked.\n";

            break;


        case 4:

            defeatBanditsRaw->unlock();

            std::cout
                << "Defeat Bandits unlocked.\n";

            break;


        case 5:

            forgeBladeRaw->unlock();

            std::cout
                << "Forge Blade unlocked.\n";

            break;


        /*
         * -------------------------------------------------
         * START
         * -------------------------------------------------
         */

        case 6:

            journal.beginAdventure();

            std::cout
                << "Adventure started.\n";

            break;


        /*
         * -------------------------------------------------
         * OBJECTIVE PROGRESS
         * -------------------------------------------------
         */

        case 7:

            std::cout
                << "Completing objectives...\n";

            sunpetal->advance(5);

            moonleaf->advance(3);

            slayBandits->advance(3);

            mineOre->advance(4);

            smithBlade->advance(1);

            break;


        /*
         * -------------------------------------------------
         * HARDCORE DECORATOR
         * -------------------------------------------------
         */

        case 8:

            std::cout
                << "Defeat Bandits takes damage.\n";

            defeatBanditsHard->fail();

            break;


        /*
         * -------------------------------------------------
         * TIMED DECORATOR
         * -------------------------------------------------
         */

        case 9:

            std::cout
                << "Waiting 70 seconds...\n";

            gatherHerbsTimed->tick(70);

            break;


        /*
         * -------------------------------------------------
         * STEALTH DECORATOR
         * -------------------------------------------------
         */

        case 10:

            std::cout
                << "Player has been detected.\n";

            gatherHerbsStealth->setDetected(true);

            gatherHerbsTimed->fail();

            break;


        /*
         * -------------------------------------------------
         * COMPLETE QUEST
         * -------------------------------------------------
         */

        case 11:

            forgeBladeRaw->complete();

            break;


        /*
         * -------------------------------------------------
         * STRUCTURAL CHANGE
         * -------------------------------------------------
         */

        case 12:

            if (elderPath->remove(defeatBanditsHard)) {

                smithTrials->add(
                    defeatBanditsHard
                );

                std::cout
                    << "Defeat Bandits moved to "
                    << "Smith's Trials.\n";
            }
            else {

                std::cout
                    << "Defeat Bandits is already "
                    << "in Smith's Trials.\n";
            }

            break;


        /*
         * -------------------------------------------------
         * STORY ORDER ITERATOR
         * -------------------------------------------------
         */

        case 13:

            journal.listStoryOrder();

            break;

            case 14: {
    std::cout << "Starting a story-order iterator (Iterator A)...\n";
    QuestIterator* iterA = campaign->createIterator();
    iterA->first();

    std::cout << "First 2 nodes from Iterator A:\n";
    for (int i = 0; i < 2 && !iterA->isDone(); i++) {
        std::cout << "  - " << iterA->current()->getName() << "\n";
        iterA->next();
    }

    std::cout << "\n--- Structural change happens now (moving Defeat Bandits) ---\n";
    if (elderPath->remove(defeatBanditsHard)) {
        smithTrials->add(defeatBanditsHard);
    }

    std::cout << "\nIterator A continues on its ORIGINAL snapshot:\n";
    for (; !iterA->isDone(); iterA->next()) {
        std::cout << "  - " << iterA->current()->getName() << "\n";
    }
    delete iterA;

    std::cout << "\nA brand-new Iterator B sees the UPDATED structure:\n";
    QuestIterator* iterB = campaign->createIterator();
    for (iterB->first(); !iterB->isDone(); iterB->next()) {
        std::cout << "  - " << iterB->current()->getName() << "\n";
    }
    delete iterB;
    break;
}

        /*
         * -------------------------------------------------
         * EXIT
         * -------------------------------------------------
         */

        case 0:

            running = false;

            break;


        default:

            std::cout
                << "Invalid option.\n";

            break;
        }
    }


    /*
     * =====================================================
     * CLEANUP
     * =====================================================
     */

    delete campaign;

    return 0;
}