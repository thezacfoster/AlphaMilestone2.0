/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Chapter2.cpp
-- File Description: The execution related to Chapter 2.
*/
#include "Chapter2.h"
#include <chrono>
#include <thread>
#include <vector>
#include <string>
using namespace std;

vector<string> playerInv;

bool inCurrentTown = true;
bool inCurrentForestPath = false;
bool inCurrentRuins = false;
bool inPastCottage = true;
bool inPastCity = false;
bool inPastForestPath = false;
bool inPastRuins = false;
bool inBlacksmithFoundry = true;
bool item_taken = false;
bool item_placed = false;
bool sword_taken = false;
bool spellbook_taken = false;
bool hasStorybook = true;
bool hasBrokenLock = false;
bool hasFixedLock = false;
bool hasAppleMoney = false;
bool hasElderApple = false;
bool visitedFortuneteller = false;
bool visitedTownElder = false;

Chapter2::Chapter2() {
	runSetup();
	run();
}

Chapter2::~Chapter2() {
}

bool Chapter2::runSetup() { // runs initial setup for chapter 2. returns true if setup was successful.
	//location setup calls
	setupCurrentTown("CurrentTown");
	setupBlacksmithFoundry("BlacksmithFoundry");
	setupCurrentForestPath("CurrentForestPath");
	setupCurrentRuins("CurrentRuins");
	setupPastCottage("PastCottage");
	setupPastForestPath("PastForestPath");
	setupPastCity("PastCity");
	setupPastRuins("PastRuins");

	return true;
}

void Chapter2::run() { // begins chapter 2's execution
	//runPastCottage();
	runCurrentTown();
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
	runPastCottage();
	//
}

// location setup functions. return true if setup was successful.
bool Chapter2::setupCurrentTown(string name) {
	currentCity = City(name);

	//character setup
	function.SetupCharacter("Arlan", "B", "LightArmour", "Long", "Black", "CurrentTown.Fountain");
	function.SetupCharacter("Apple Merchant", "C", "Merchant", "Long", "Blonde", "CurrentTown.Horse");
	function.SetupCharacter("Town Elder", "H", "Noble", "Musketeer_Full", "Gray", "CurrentTown.Plant");

	//items
	function.Action("CreateItem(MathiasSword, Sword)", true);
	function.Action("CreateItem(Apple Money, Coin)", true);
	function.Action("CreateItem(Elder Apple, Apple)", true);
	function.Action("CreateItem(Broken Lock, Lock)", true);
	function.Action("CreateItem(Storybook, BlueBook)", true);
	playerInv.push_back("Storybook");

	//icons
	//Talk To Town Elder
	currentCity.icons.push_back(Icon("Talk To Town Elder", "Talk", "Town Elder", "Talk To Town Elder", "true"));
	//Talk To Apple Merchant
	currentCity.icons.push_back(Icon("Talk To Apple Merchant", "Talk", "Apple Merchant", "Talk To Apple Merchant", "true"));
	//Buy Apple
	currentCity.icons.push_back(Icon("Buy Apple", "Coin", "Elder Apple", "Buy Elder Apple", "true"));
	//Pick Up MathiasSword
	currentCity.icons.push_back(Icon("Take_MathiasSword", "Hand", "MathiasSword", "Take the sword", "true"));
	//Enter BlacksmithFoundry
	currentCity.icons.push_back(Icon("Enter Blacksmith Foundry", "Hand", "CurrentTown.RedHouseDoor", "Enter Blacksmith Foundry", "true"));
	function.SetupIcons(currentCity.icons);

	return true;
}

bool Chapter2::setupBlacksmithFoundry(string name) {
	BlacksmithFoundry = Blacksmith(name);

	//character setup
	function.SetupCharacter("Blacksmith", "B", "HeavyArmour", "Musketeer_Beard", "Blonde", "BlacksmithFoundry.Anvil");

	//items
	function.Action("CreateItem(Fixed Lock, Lock)", true);

	//icons
	//Talk To Blacksmith
	BlacksmithFoundry.icons.push_back(Icon("Talk To Blacksmith", "Talk", "Blacksmith", "Talk To Blacksmith", "true"));
	//Exit Blacksmith Foundry
	BlacksmithFoundry.icons.push_back(Icon("Exit Blacksmith Foundry", "Hand", "BlacksmithFoundry.Door", "Exit Blacksmith Foundry", "true"));
	function.SetupIcons(BlacksmithFoundry.icons);

	return true;
}

bool Chapter2::setupCurrentForestPath(string name) {
	currentForestPath = ForestPath(name);

	//character setup

	//items and their placement
	function.Action("CreateItem(ArchieSpellbook, SpellBook)", true);

	//icons
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
	function.Action("SetPosition(Letter, PastCottage.Shelf)", true);

	//character setup
	function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Black", "PastCottage.Bed");

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

				//splitInput needs modifications to allow for spaces
				if (modified_I == "Elder") {
					function.SetupDialog("Arlan", "Town Elder", true);
					if (hasStorybook && !hasBrokenLock && !hasFixedLock && !hasAppleMoney && !hasElderApple) {
						function.SetupDialogText("Thats a cool book Arlan! Can you please help me run some errands and ill tell you about one of the stories?", "helpElder", "Sounds like a deal.");
					}
					else if (hasAppleMoney) {
						function.SetupDialogText("Please go buy me an apple from the Apple Merchant!", "end", "ok.");
					}
					else if (hasBrokenLock) {
						function.SetupDialogText("Please go repair my lock at the Blacksmith Foundry!", "end", "ok.");
					}
					else if (hasElderApple || hasFixedLock) {
						if (visitedFortuneteller) {
							if (hasElderApple) {
								for (int i = 0; i < playerInv.size(); i++) {
									if (playerInv[i] == "Storybook") {
										playerInv.erase(playerInv.begin() + i);
									}
								}
								hasStorybook = false;
								for (int i = 0; i < playerInv.size(); i++) {
									if (playerInv[i] == "Elder Apple") {
										playerInv.erase(playerInv.begin() + i);
									}
								}
								hasElderApple = false;
							}
							else if (hasFixedLock) {
								for (int i = 0; i < playerInv.size(); i++) {
									if (playerInv[i] == "Storybook") {
										playerInv.erase(playerInv.begin() + i);
									}
								}
								hasStorybook = false;
								for (int i = 0; i < playerInv.size(); i++) {
									if (playerInv[i] == "Fixed Lock") {
										playerInv.erase(playerInv.begin() + i);
									}
								}
								hasFixedLock = false;
							}
						}
						else {
							function.SetupDialogText("Go get your fortune from the fortuneteller!", "end", "ok.");
						}
					}
				}

				else if (modified_I == "Merchant") {
					function.SetupDialog("Arlan", "Apple Merchant", true);
					if (!visitedTownElder) {
						function.SetupDialogText("I am not open quite yet. Come back later!", "end", "ok");
					}
					else if (hasAppleMoney) {
						function.SetupDialogText("Ah! Take this apple for the coin!", "takeApple", "ok!");
					}
					else {
						function.SetupDialogText("Beautiful day isn't it?!", "end", "It is!");
					}
				}
			}

			else if (modified_I == "Selected") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "helpElder") {
					function.SetupDialogText("Great! Would you like to buy my apples or repair my lock?", "selectAppleErrand", "I can buy the apples.", "selectLockErrand", "I would rather fix the lock.");
					visitedTownElder = true;
				}

				else if (modified_I == "selectAppleErrand") {
					function.Action("SetNarration(Apple Money Added To Inventory)", true);
					function.Action("ShowNarration()", true);
					playerInv.push_back("Apple Money");
					hasAppleMoney = true;
					function.SetupDialogText("I would recommend getting your fortune told by the new fortune teller as well! Meet me back here after your errands are done!", "end", "ok!");
				}

				else if (modified_I == "selectLockErrand") {
					function.Action("SetNarration(Broken Lock Added To Inventory)", true);
					function.Action("ShowNarration()", true);
					playerInv.push_back("Broken Lock");
					hasBrokenLock = true;
					function.SetupDialogText("I would recommend getting your fortune told by the new fortune teller as well! Meet me back here after your errands are done!", "end", "ok!");
				}

				else if (modified_I == "takeApple") {
					function.Action("SetNarration(Apple Money Removed From Inventory)", true);
					function.Action("ShowNarration()", true);
					for (int i = 0; i < playerInv.size(); i++) {
						if (playerInv[i] == "Apple Money") {
							playerInv.erase(playerInv.begin() + i);
						}
					}
					hasAppleMoney = false;
					function.SetupDialogText("Here you go!", "receiveApple", "Thanks!");
				}

				else if (modified_I == "receiveApple") {
					function.Action("HideDialog()", true);
					playerInv.push_back("Elder Apple");
					hasElderApple = true;
					function.Action("SetNarration(Elder Apple Added To Inventory)", true);
					function.Action("ShowNarration()", true);
				}
			}
		}

		if (i == "input Enter Blacksmith Foundry CurrentTown.RedHouseDoor") {
			function.WalkToPlace("Arlan", "CurrentTown.RedHouseDoor");
			if (visitedTownElder) {
				function.Transition("Arlan", "CurrentTown.RedHouseDoor", "BlacksmithFoundry.Door");
				inCurrentTown = false;
				inBlacksmithFoundry = true;
				runBlacksmithFoundry();
			}
			else {
				function.Action("SetNarration(The door is locked. This store must be closed.)", true);
				function.Action("ShowNarration()", true);
			}
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

void Chapter2::runBlacksmithFoundry() {
	while (inBlacksmithFoundry) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", arlanInv);

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "Blacksmith") {
					function.SetupDialog("Arlan", "Blacksmith", true);
					if (hasBrokenLock) {
						function.SetupDialogText("Oh! The Town Elder needs his broken lock fixed? No problem! Give me the lock.", "fixTheLock", "Here you go!");
					}
					else if (hasFixedLock) {
						function.SetupDialogText("Return that lock to the Town Elder", "end", "ok.");
					}
					else {
						function.SetupDialogText("Hello. Hope you are having a good day!", "end", "Thank you!");
					}
				}
			}

			else if (modified_I == "Selected") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "fixTheLock") {
					function.Action("SetNarration(Broken Lock Removed From Inventory)", true);
					function.Action("ShowNarration()", true);
					for (int i = 0; i < playerInv.size(); i++) {
						if (playerInv[i] == "Broken Lock") {
							playerInv.erase(playerInv.begin() + i);
						}
					}
					hasBrokenLock = false;
					function.SetupDialogText("Here you go!", "receiveFixedLock", "Thanks!");
				}

				else if (modified_I == "receiveFixedLock") {
					function.Action("HideDialog()", true);
					playerInv.push_back("Fixed Lock");
					hasFixedLock = true;
					function.Action("SetNarration(Fixed Lock Added To Inventory)", true);
					function.Action("ShowNarration()", true);
				}
			}
		}

		if (i == "input Exit Blacksmith Foundry BlacksmithFoundry.Door") {
			function.Transition("Arlan", "BlacksmithFoundry.Door", "CurrentTown.RedHouseDoor");
			inBlacksmithFoundry = false;
			inCurrentTown = true;
			runCurrentTown();
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

		if (!inputWasCommon) {
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
		}

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
	bool LetterCheck = false;

	function.Action("SetCameraFocus(Mathias)", true);
	function.Action("FadeIn()", true);
	function.Action("EnableInput()", true);
	while (inPastCottage) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Mathias", mathiasInv);

		if (modified_I == "Read") {
			function.Action("WalkTo(Mathias, Letter)", true);
			function.Action("SetNarration(Mathias we need to discuss what to do about that artifact we found. Meet me by the ruins so we can discuss)", true);
			function.Action("ShowNarration()", true);
			LetterCheck = true;

		}

		if (modified_I == "Close") {
			function.Action("HideNarration()", true);
		}

		if (!inputWasCommon) {

			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}

			if (modified_I == "Open") {
				if (LetterCheck) {
					function.Transition("Mathias", "PastCottage.Door", "PastCity.GreenHouseDoor");
					inPastCottage = false;
					inPastCity = true;
					runPastCity();
				}
				else {
					function.Action("SetNarration(I should read that letter I left on the shelf)", true);
					function.Action("ShowNarration()", true);
				}
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