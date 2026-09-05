#include "Campaign.h"
#include "Questline.h"
#include "Quest.h"
#include "Objective.h"
#include "QuestJournal.h"

// Composite-milestone demo only: exercises Campaign/Questline/Quest/Objective
// through QuestComponent and QuestJournal. State, Decorator and Iterator are
// not implemented yet, so nothing here touches them.
int main() {
    Campaign* campaign = new Campaign("The Shattered Coast", 1);

    Questline* harborLine = new Questline("Trouble at the Harbor", "Dockmaster Reyes");

    Quest* clearDocks = new Quest("Clear the Docks", 101);
    clearDocks->add(new Objective("Defeat bilge rats", 10, 5));
    clearDocks->add(new Objective("Repair the crane", 15, 1));

    Quest* findCargo = new Quest("Find the Missing Cargo", 102);
    findCargo->add(new Objective("Search warehouse", 5, 3));
    findCargo->add(new Objective("Question witnesses", 5, 2));

    harborLine->add(clearDocks);
    harborLine->add(findCargo);

    Questline* signalLine = new Questline("Smoke on the Water", "Lighthouse Keeper Vale");
    Quest* lightTheBeacon = new Quest("Light the Beacon", 201);
    lightTheBeacon->add(new Objective("Collect oil", 20, 4));
    signalLine->add(lightTheBeacon);

    campaign->add(harborLine);
    campaign->add(signalLine);

    QuestJournal journal("The Shattered Coast - Journal");
    journal.setRoot(campaign);

    journal.beginAdventure();
    journal.printTree();

    clearDocks->complete();
    findCargo->complete();
    lightTheBeacon->complete();

    journal.printTree();

    delete campaign;
    return 0;
}
