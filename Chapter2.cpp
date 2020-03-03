/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Chapter2.cpp
-- File Description: The execution related to Chapter 2.
*/
#include "Chapter2.h"
//#include "functions.cpp"
#include <chrono>
#include <thread>
#include <vector>
#include <string>
using namespace std;

vector<string> playerInv;
vector<string> mariahInv;

bool inCurrentTown = true;
bool inCurrentForestPath = false;
bool inCurrentRuins = false;
bool inPastCottage = true;
bool inPastCity = false;
bool inPastForestPath = false;
bool inPastRuins = false;
bool item_taken = false;
bool item_placed = false;
bool sword_taken = false;
bool spellbook_taken = false;

Chapter2::Chapter2() {
	runSetup();
	run();
}

Chapter2::~Chapter2() {
}

bool Chapter2::runSetup() { // runs initial setup for chapter 2. returns true if setup was successful.
	//location setup calls
	setupCurrentTown("CurrentTown");
	setupCurrentForestPath("CurrentForestPath");
	setupCurrentRuins("CurrentRuins");
	setupPastCottage("PastCottage");
	setupPastForestPath("PastForestPath");
	setupPastCity("PastCity");
	setupPastRuins("PastRuins");

	return true;
}

void Chapter2::run() { // begins chapter 2's execution
	runPastCottage();
	//runCurrentTown();
	//runCurrentForestPath();
	//runCurrentRuins();
	//setupPastRuins("PastRuins");
	//runPastCottage();
	//setupPastForestPath("PastForestPath");
}

//Flashback execution function
void Chapter2::flashback1() {
	//flashback transistion
	function.Action("WalkTo(Arlan, CurrentRuins.Altar)", true);
	function.Action("SetCameraMode(Focus)", true);
	function.Action("SetNarration(The air around you feels wierd. Something pulls you to a slumber.)", true);
	function.Action("ShowNarration()", true);
	bool inNarration = true;
	while (inNarration) {
		string i;
		getline(cin, i);

		if (i == "input Close Narration") {
			function.Action("HideNarration()", true);
			inNarration = false;
		}
	}
	function.Action("HideNarration()", true);
	function.Action("SetExpression(Arlan, Surprised)", true);
	this_thread::sleep_for(chrono::milliseconds(500));
	function.Action("SetCameraMode(Follow)", true);
	function.Action("Die(Arlan)", true);
	function.Action("FadeOut()", true);

	//
}

// location setup functions. return true if setup was successful.
bool Chapter2::setupCurrentTown(string name) {
	currentCity = City(name);

	//character setup
	function.SetupCharacter("Arlan", "B", "LightArmour", "Long", "Brown", "CurrentTown.Fountain");

	//function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupCurrentForestPath(string name) {
	currentForestPath = ForestPath(name);

	//character setup
	function.SetupCharacter("Mariah", "G", "Beggar", "Straight", "Gray", "CurrentForestPath.Well");

	//items and their placement
	function.Action("CreateItem(MathiasSword, Sword)", true);
	function.Action("CreateItem(ArchieSpellbook, SpellBook)", true);
	mariahInv.push_back("MathiasSword");
	mariahInv.push_back("ArchieSpellbook");

	//icons
	currentForestPath.icons.push_back(Icon("Talk_To_Mariah", "Talk", "Mariah", "Talk To Mariah", "true"));
	currentForestPath.icons.push_back(Icon("Take_MathiasSword", "Hand", "MathiasSword", "Take the sword", "true"));
	currentForestPath.icons.push_back(Icon("Take_ArchieSpellbook", "Hand", "ArchieSpellbook", "Take the spellbook", "true"));
	function.SetupIcons(currentForestPath.icons);

	//function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupCurrentRuins(string name) {
	currentRuins = Ruins(name);

	//character setup
	//function.SetupCharacter("Arlan", "B", "LightArmour", "Long", "Brown", "CurrentRuins.Exit");

	//items and their placement
	function.Action("CreateItem(LeaderFlashPotion, GreenPotion)", true);//potion to activate flashback 1
	//function.Action("SetPosition(LeaderFlashPotion, CurrentRuins.Altar)", true);

	//icons
	currentRuins.icons.push_back(Icon("Take", "Hand", "LeaderFlashPotion", "Take the Potion", "true"));
	function.SetupIcons(currentRuins.icons);

	//function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupPastCottage(string name) {
	pastCottage = Cottage(name);

	function.Action("CreateItem(Letter, OpenScroll)", true);
	function.Action("SetPosition(Letter, PastCottage.Table)", true);

	//character setup
	function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "PastCottage.Bed");

	//icons
	pastCottage.icons.push_back(Icon("Open", "Exit", "PastCottage.Door", "Leave the Room", "true"));
	pastCottage.icons.push_back(Icon("Read", "Research", "Letter", "Read the Letter", "true"));
	function.SetupIcons(pastCottage.icons);

	function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupPastForestPath(string name) {
	pastForestPath = ForestPath(name);

	//character setup
	//function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "PastForestPath.EastEnd");

	//icons

	//function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupPastCity(string name) {
	pastCity = City(name);

	//character setup
	//function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "PastCity.WestEnd");

	//icons
	pastCottage.icons.push_back(Icon("Open", "Exit", "PastCity.GreenHouseDoor", "Go Inside", "true"));
	function.SetupIcons(pastCity.icons);
	//function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupPastRuins(string name) {
	pastRuins = Ruins(name);

	//character setup
	//function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "PastCity.WestEnd");
	function.SetupCharacter("Archie", "D", "Priest", "Mage_Full", "Black", name + ".Altar");

	//icons
	pastRuins.icons.push_back(Icon("Talk to Archie", "Talk", "Archie", "Talk to Archie", "true"));
	function.SetupIcons(pastRuins.icons);

	function.Action("CreateItem(MysteriousSkull, Skull)", true);
	function.Action("SetPosition(MysteriousSkull, " + name + ".Altar)", true);
	function.Action("Face(Archie, MysteriousSkull)", true);
	function.Action("Kneel(Archie)", true);
	//function.Action("ShowMenu()", true);

	return true;
}

// location execution functions.
void Chapter2::runCurrentTown() {
	while (inCurrentTown) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", arlanInv);

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}
		}

		if (i == "input arrived Arlan position CurrentTown.EastEnd") {
			function.Transition("Arlan", "CurrentTown.EastEnd", "CurrentForestPath.WestEnd");
			inCurrentTown = false;
			inCurrentForestPath = true;
			runCurrentForestPath();
		}

		else if (i == "input Key Inventory") {
			function.Action("ClearList()", true);
			for (string item : playerInv) {
				function.Action("AddToList(" + item + ")", true);
			}
			function.Action("ShowList(Arlan)", true);
		}

		else if (i == "input Close List") {
			function.Action("HideList()", true);
			function.Action("EnableInput()", true);
		}
	}
}

void Chapter2::runCurrentForestPath() {
	while (inCurrentForestPath) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", arlanInv);

		/*if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}
		}*/

		if (i == "input arrived Arlan position CurrentForestPath.WestEnd") {
			function.Transition("Arlan", "CurrentForestPath.WestEnd", "CurrentTown.EastEnd");
			inCurrentTown = true;
			inCurrentForestPath = false;
			runCurrentTown();
		}

		else if (i == "input arrived Arlan position CurrentForestPath.EastEnd") {
			function.Transition("Arlan", "CurrentForestPath.EastEnd", "CurrentRuins.Exit");
			inCurrentForestPath = false;
			inCurrentRuins = true;
			runCurrentRuins();
		}

		else if (i == "input Take_MathiasSword MathiasSword") {
			function.Action("RemoveFromList(MathiasSword)", true);
			for (int i = 0; i < mariahInv.size(); i++) {
				if (mariahInv[i] == "MathiasSword") {
					mariahInv.erase(mariahInv.begin() + i);
				}
			}
			function.Action("DisableIcon(Take_MathiasSword, MathiasSword)", true);
			playerInv.push_back("MathiasSword");
			function.Action("HideList()", true);
			item_taken = true;
			sword_taken = true;
			function.Action("CreateEffect(Mariah, Brew)", true);
			function.Action("EnableEffect(Mariah, Brew)", true);
			this_thread::sleep_for(chrono::milliseconds(2000));
			function.Action("DisableEffect(Mariah)", true);
			function.Action("SetPosition(Mariah)", true);
		}

		else if (i == "input Take_ArchieSpellbook ArchieSpellbook") {
			function.Action("RemoveFromList(ArchieSpellbook)", true);
			for (int i = 0; i < mariahInv.size(); i++) {
				if (mariahInv[i] == "ArchieSpellbook") {
					mariahInv.erase(mariahInv.begin() + i);
				}
			}
			function.Action("DisableIcon(Take_ArchieSpellbook, ArchieSpellbook)", true);
			playerInv.push_back("ArchieSpellbook");
			function.Action("HideList()", true);
			item_taken = true;
			spellbook_taken = true;
			function.Action("CreateEffect(Mariah, Brew)", true);
			function.Action("EnableEffect(Mariah, Brew)", true);
			this_thread::sleep_for(chrono::milliseconds(2000));
			function.Action("DisableEffect(Mariah)", true);
			function.Action("SetPosition(Mariah)", true);
		}

		else if (i == "input Talk_To_Mariah Mariah") {
			function.Action("DisableInput()", true);
			function.Action("WalkTo(Arlan, Mariah)", true);
			function.Action("ShowDialog()", true);
			function.Action("ClearDialog()", true);
			function.Action("SetLeft(Arlan)", true);
			function.Action("SetRight(Mariah)", true);
			function.Action("EnableInput()", true);
			if (item_taken)
				function.Action("SetDialog(Have a good day! [end|Thanks you too.])", true);
			else
				function.Action("SetDialog(The ruins are a mysterious place. May I offer you a gift for your journey? [takeFromMariah|Yes please] [end|No Thanks])", true);
		}

		else if (i == "input Selected takeFromMariah") {
			function.Action("HideDialog()", true);
			for (string item : mariahInv) {
				function.Action("AddToList(" + item + ")", true);
			}
			function.Action("ShowList(Mariah)", true);
		}

		else if (i == "input Selected end") {
			function.Action("HideDialog()", true);
		}

		else if (i == "input Key Inventory") {
			function.Action("ClearList()", true);
			for (string item : playerInv) {
				function.Action("AddToList(" + item + ")", true);
			}
			function.Action("ShowList(Arlan)", true);
		}

		else if (i == "input Close List") {
			function.Action("HideList()", true);
			function.Action("EnableInput()", true);
		}
	}
}

void Chapter2::runCurrentRuins() {
	while (inCurrentRuins) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", arlanInv);

		/*if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}
			//if the player is in the CurrentRuins
			else if (inCurrentRuins) {
				if (modified_I == "Take") {
					function.Action("Take(Arlan, LeaderFlashPotion)", true);
					flashback1();
				}
			}
		}*/

		if (i == "input arrived Arlan position CurrentRuins.Exit") {
			function.Transition("Arlan", "CurrentRuins.Exit", "CurrentForestPath.EastEnd");
			inCurrentForestPath = true;
			inCurrentRuins = false;
			runCurrentForestPath();
		}

		else if (i == "input arrived Arlan position CurrentRuins.Altar") {
			if (!item_placed && item_taken) {
				function.Action("DisableInput()", true);
				function.Action("ShowDialog()", true);
				function.Action("ClearDialog()", true);
				function.Action("SetLeft(Arlan)", true);
				function.Action("EnableInput()", true);
				function.Action("SetDialog(You hear a whisper. \"Place the tribute to see the past.\" Place your item? [placeSwordSpellbook|Yes] [end|No])", true);
			}
		}

		else if (i == "input Selected placeSwordSpellbook") {
			function.Action("HideDialog()", true);
			if (sword_taken) {
				for (int i = 0; i < playerInv.size(); i++) {
					if (playerInv[i] == "MathiasSword") {
						playerInv.erase(playerInv.begin() + i);
					}
				}
				function.Action("SetPosition(MathiasSword, CurrentRuins.Altar.Top)", true);
			}
			else if (spellbook_taken) {
				for (int i = 0; i < playerInv.size(); i++) {
					if (playerInv[i] == "ArchieSpellbook") {
						playerInv.erase(playerInv.begin() + i);
					}
				}
				function.Action("SetPosition(ArchieSpellbook, CurrentRuins.Altar.Top)", true);
			}
			item_placed = true;
			function.Action("CreateEffect(CurrentRuins.Altar, Resurrection)", true);
			function.Action("EnableEffect(CurrentRuins.Altar, Resurrection)", true);
			this_thread::sleep_for(chrono::milliseconds(2000));
			function.Action("SetPosition(MathiasSword)", true);
			function.Action("SetPosition(ArchieSpellbook)", true);
			this_thread::sleep_for(chrono::milliseconds(2000));
			function.Action("SetPosition(LeaderFlashPotion, CurrentRuins.Altar.Top)", true);
			this_thread::sleep_for(chrono::milliseconds(2000));
			function.Action("DisableEffect(CurrentRuins.Altar)", true);
		}

		else if (i == "input Selected end") {
			function.Action("HideDialog()", true);
		}

		else if (i == "input Key Inventory") {
			function.Action("ClearList()", true);
			for (string item : playerInv) {
				function.Action("AddToList(" + item + ")", true);
			}
			function.Action("ShowList(Arlan)", true);
		}

		else if (i == "input Close List") {
			function.Action("HideList()", true);
			function.Action("EnableInput()", true);
		}
	}
}

void Chapter2::runPastCottage() {
	while (inPastCottage) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Mathias", mathiasInv);

		if (!inputWasCommon) {

			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}

			if (modified_I == "Open") {
				function.Transition("Mathias", "PastCottage.Door", "PastCity.GreenHouseDoor");
				inPastCottage = false;
				inPastCity = true;
				runPastCity();
			}
		}

	}
}
void Chapter2::runPastForestPath() {
	//function.Action("Enter(" + character + ", " + entrance + ", true)", true);
	while (inPastForestPath) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Mathias", mathiasInv);

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}
		}

		if (i == "input arrived Mathias position PastForestPath.WestEnd") {
			function.Transition("Mathias", "PastForestPath.WestEnd", "PastCity.EastEnd");
			inPastCity = true;
			inPastForestPath = false;
			runPastCity();
		}

		else if (i == "input arrived Mathias position PastForestPath.EastEnd") {
			function.Transition("Mathias", "PastForestPath.EastEnd", "PastRuins.Exit");
			inPastForestPath = false;
			inPastRuins = true;
			runPastRuins();
		}
	}
}

void Chapter2::runPastCity() {
	while (inPastCity) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Mathias", mathiasInv);

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}
		}

		if (i == "input arrived Mathias position PastCity.EastEnd") {
			function.Transition("Mathias", "PastCity.EastEnd", "PastForestPath.WestEnd");
			inPastCity = false;
			inPastForestPath = true;
			runPastForestPath();
		}

		if (modified_I == "Open") {
			function.Transition("Mathias", "PastCity.GreenHouseDoor", "PastCottage.Door");
			inPastCottage = true;
			inPastCity = false;
			runPastCity();
		}

	}
}

void Chapter2::runPastRuins() {
	//function.Action("Enter(" + character + ", " + entrance + ", true)", true);
	while (true) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Mathias", mathiasInv);

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "Archie") {
					function.SetupDialog("Mathias", "Archie", false);
					function.Action("SetDialog(\"(He appears to be mumbling to himself) [getAttention|(Get his attention)]\")", false);
				}
			}

			else if (modified_I == "Selected") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "getAttention") {
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(\"Ah, Mathias... you've arrived. I suppose this is inevitable. [question|What are you talking about?]\")", false);
				}

				if (modified_I == "question") {
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(\"I'm afraid this relic is more powerful than either of us could ever have imagined. I cannot let it fall into another's hands. I am sorry, old friend. [wait|Archie, wait-]\")", false);
				}

				if (modified_I == "wait") {
					function.Action("ClearDialog()", true);
					function.Action("HideDialog()", true);
					function.Action("DisableInput()", true);
					function.Action("WalkTo(Archie, PastRuins.Altar)", true);
					function.Action("Face(Archie, Mathias)", true);
					function.Action("Cast(Archie, Mathias)", true);
					function.Action("Kneel(Mathias)", false);
					//function.Action("Take(Archie, MysteriousSkull, PastRuins.Altar)", true);
					function.Action("Face(Archie, MysteriousSkull)", true);
					function.Action("SetPosition(MysteriousSkull)", true);
					function.Action("Unpocket(Archie, MysteriousSkull)", true);
					function.Action("WalkTo(Archie, PastRuins.Exit)", true);
					function.Action("SetPosition(Archie)", true);
					function.Action("WalkTo(Mathias, PastRuins.Altar)", true);
					function.Action("FadeOut()", true);

					function.Action("SetPosition(Arlan, CurrentRuins.Altar)", true);
					function.Action("Kneel(Arlan)", true);
					function.Action("SetCameraFocus(Arlan)", true);
					function.Action("FadeIn()", false);
					function.Action("WalkTo(Arlan, CurrentRuins.Altar)", false);
					function.Action("SetNarration(What an odd vision...)", true);
				}
			}

		}
	}
}