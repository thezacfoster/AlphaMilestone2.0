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
vector<string> mariahInv;
vector<string> dadInv;

bool inCurrentTown = false;
bool inCurrentForestPath = false;
bool inCurrentRuins = false;
bool inPastCottage = false;
bool inPastCity = false;
bool inPastForestPath = false;
bool inPastRuins = false;
bool inAlchemyShop = false;
bool inArlanCottage = false;

bool item_taken = false;
bool item_placed = false;
bool sword_taken = false;
bool spellbook_taken = false;
bool hasStoryBook = false;
bool fortuneTold = false;

Chapter2::Chapter2() {
	runSetup();
	run();
}

Chapter2::~Chapter2() {
}

bool Chapter2::runSetup() { // runs initial setup for chapter 2. returns true if setup was successful.
	//location setup calls
	setupCurrentCottage("ArlanCottage");
	setupCurrentTown("CurrentTown");
	setupCurrentForestPath("CurrentForestPath");
	setupCurrentRuins("CurrentRuins");
	setupPastCottage("PastCottage");
	setupPastForestPath("PastForestPath");
	setupPastCity("PastCity");
	setupPastRuins("PastRuins");
	setupAlchemyShop("AlchemyShop");
	inArlanCottage = true;
	function.Action("ShowMenu()", true);

	return true;
}

void Chapter2::run() { // begins chapter 2's execution
	while (true) {
		if (inCurrentTown) {
			function.Action("SetNarration(inArlanCottagenotloop1)", true);
			runCurrentTown();
		}
		else if (inCurrentForestPath) {
			function.Action("SetNarration(inArlanCottagenotloop2)", true);
			runCurrentForestPath();
		}
		else if (inCurrentRuins) {
			function.Action("SetNarration(inArlanCottagenotloop3)", true);
			runCurrentRuins();
		}
		else if (inPastRuins) {
			function.Action("SetNarration(inArlanCottagenotloop4)", true);
			runPastRuins();
		}
		else if (inPastForestPath) {
			function.Action("SetNarration(inArlanCottagenotloop5)", true);
			runPastForestPath();
		}
		else if (inPastCottage) {
			function.Action("SetNarration(inArlanCottagenotloop6)", true);
			runPastCottage();
		}
		else if (inPastCity) {
			function.Action("SetNarration(inArlanCottagenotloop7)", true);
			runPastCity();
		}
		else if (inAlchemyShop) {
			function.Action("SetNarration(inArlanCottagenotloop8)", true);
			runAlchemyShop();
		}
		else if (inArlanCottage) {
			function.Action("SetNarration(inArlanCottageloop)", true);
			runCurrentCottage();
		}
	}
	
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
	//runPastCottage();
	//
}

// location setup functions. return true if setup was successful.
bool Chapter2::setupCurrentTown(string name) {
	currentCity = City(name);

	//character setup

	//icon setup
	currentCity.icons.push_back(Icon("Open_AlchemyShop", "Open", "CurrentTown.BrownHouseDoor", "Enter Alchemy Shop", "true"));
	function.SetupIcons(currentCity.icons);
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

	return true;
}

bool Chapter2::setupCurrentRuins(string name) {
	currentRuins = Ruins(name);

	//items and their placement
	function.Action("CreateItem(LeaderFlashPotion, GreenPotion)", true);//potion to activate flashback 1

	//icons
	currentRuins.icons.push_back(Icon("Take", "Hand", "LeaderFlashPotion", "Take the Potion", "true"));
	function.SetupIcons(currentRuins.icons);

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


	return true;
}

bool Chapter2::setupPastForestPath(string name) {
	pastForestPath = ForestPath(name);

	//character setup
	//function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "PastForestPath.EastEnd");

	//icons


	return true;
}

bool Chapter2::setupPastCity(string name) {
	pastCity = City(name);

	//character setup
	//function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "PastCity.WestEnd");

	//icons
	pastCottage.icons.push_back(Icon("Open", "Exit", "PastCity.GreenHouseDoor", "Go Inside", "true"));
	function.SetupIcons(pastCity.icons);

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

	return true;
}

bool Chapter2::setupAlchemyShop(string name) {
	Alchemy = AlchemyShop(name);

	//character setup
	function.SetupCharacter("Fortuneteller", "G", "Witch", "Ponytail", "Gray", "AlchemyShop.AlchemistTable");
	
	//icon setup
	Alchemy.icons.push_back(Icon("Talk_To_FortuneTeller", "Talk", "Fortuneteller", "Talk to Fortune Teller", "true"));
	Alchemy.icons.push_back(Icon("Exit_Shop", "Open", "AlchemyShop.Door", "Exit Alchemy Shop", "true"));
	function.SetupIcons(Alchemy.icons);

	return true;
}

bool Chapter2::setupCurrentCottage(string name) {
	currentCottage = Cottage(name);

	//character setup
	function.SetupCharacter("Arlan", "B", "LightArmour", "Long", "Brown", "ArlanCottage.Bed");
	function.SetupCharacter("Dad", "B", "Peasant", "Spiky", "Black", "ArlanCottage.Bookshelf");

	//item and placement
	function.Action("CreateItem(StoryBook, BlueBook)", true);
	dadInv.push_back("StoryBook");

	//icon setup
	currentCottage.icons.push_back(Icon("Talk_To_Dad", "Talk", "Dad", "Talk to Dad", "true"));
	currentCottage.icons.push_back(Icon("Open_Door", "Open", "ArlanCottage.Door", "Exit the Cottage", "true"));
	currentCottage.icons.push_back(Icon("Take_StoryBook", "Hand", "StoryBook", "Take the storybook", "true"));
	function.SetupIcons(currentCottage.icons);
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
			else if (modified_I == "arrived") {
				modified_I = function.splitInput(i, 0, true);
				if (modified_I == "CurrentTown.EastEnd") {
					function.Transition("Arlan", "CurrentTown.EastEnd", "CurrentForestPath.WestEnd");
					inCurrentTown = false;
					inCurrentForestPath = true;
					//runCurrentForestPath();
				}

			}
			else if (modified_I == "Open_AlchemyShop") {
				if (!hasStoryBook) {
					function.Transition("Arlan", "CurrentTown.BrownHouseDoor", "AlchemyShop.Door");
					inCurrentTown = false;
					inAlchemyShop = true;
					//runAlchemyShop();
				}
				else{
					function.Action("SetNarration(It's to early for the shop to be open. I should come back later)", true);
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
				}

			}
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

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			//if (modified_I == "Talk") {
			//	modified_I = function.splitInput(i, 0, true);
			//}


			if (modified_I == "arrived") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "CurrentForestPath.WestEnd") {
					function.Transition("Arlan", "CurrentForestPath.WestEnd", "CurrentTown.EastEnd");
					inCurrentTown = true;
					inCurrentForestPath = false;
					//runCurrentTown();
				}
				else if (modified_I == "CurrentForestPath.EastEnd") {
					function.Transition("Arlan", "CurrentForestPath.EastEnd", "CurrentRuins.Exit");
					inCurrentForestPath = false;
					inCurrentRuins = true;
					//runCurrentRuins();
				}
			}

			else if (modified_I == "Take_MathiasSword") {
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

			else if (modified_I == "Take_ArchieSpellbook") {
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

			else if (modified_I == "Talk_To_Mariah") {
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

			else if (modified_I == "Selected") {
				modified_I = function.splitInput(i, 0, true);
				if (modified_I == "takeFromMariah") {
					function.Action("HideDialog()", true);
					for (string item : mariahInv) {
						function.Action("AddToList(" + item + ")", true);
					}
					function.Action("ShowList(Mariah)", true);
				}
				else if (modified_I == "end") {
					function.Action("HideDialog()", true);
				}
			}



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
					inPastCottage = true;
					inCurrentRuins = false;
				}
			}
		}

		if (i == "input arrived Arlan position CurrentRuins.Exit") {
			function.Transition("Arlan", "CurrentRuins.Exit", "CurrentForestPath.EastEnd");
			inCurrentForestPath = true;
			inCurrentRuins = false;
			//runCurrentForestPath();
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

		else if (i == "Selected end") {
			function.Action("HideDialog()", true);
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
					//runPastCity();
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
			//runPastCity();
		}

		else if (i == "input arrived Mathias position PastForestPath.EastEnd") {
			function.Transition("Mathias", "PastForestPath.EastEnd", "PastRuins.Exit");
			inPastForestPath = false;
			inPastRuins = true;
			//runPastRuins();
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
			//runPastForestPath();
		}

		if (modified_I == "Open") {
			function.Transition("Mathias", "PastCity.GreenHouseDoor", "PastCottage.Door");
			inPastCottage = true;
			inPastCity = false;
			//runPastCity();
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

void Chapter2::runAlchemyShop() {
	while (inAlchemyShop) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", playerInv);

		if (!inputWasCommon) {
			if (modified_I == "Talk_To_FortuneTeller") {
				function.SetupDialog("Arlan", "Fortuneteller", false);
				function.Action("SetDialog(Oooh a customer... Arlan is it? [Answer|Yes I am Arlan. I have come for a fortune telling.] [Questioning|I have never met you. How do you know who I am?])", true);
			}
			else if (modified_I == "Selected") {
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "Answer") {
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(Give me your hand and I will give you your fortune free of charge. [Accept|**Put out your hand**] [Deny|I don't feel like it.])", true);
				}
				if (modified_I == "Questioning") {
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(I am a fortune teller. I know many things. Would like your fortune read? [Answer|Yes I am Arlan and I would like a fortune telling.] [Deny|I do not want a fortune telling])", true);
				}
				if (modified_I == "Deny") {
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(Come back when you want your fortune read. [end|leave.])", true);
				}
				if (modified_I == "Accept") {
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(**She takes your hand and begins to read your palm** You carry the burden of responsibility and hold a promising future. [end|Vauge and interesting. I'll be leaving now])", true);
					fortuneTold = true;
				}
				if (modified_I == "end") {
					function.Action("ClearDialog()", true);
					function.Action("HideDialog()", true);
				}
			}
			else if (modified_I == "Exit_Shop") {
				function.Transition("Arlan", "AlchemyShop.Door", "CurrentTown.BrownHouseDoor");
				inCurrentTown = true;
				inAlchemyShop = false;
				//runCurrentTown();
			}
		}
	}
}

void Chapter2::runCurrentCottage() {
	while (inArlanCottage) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", playerInv);

		if (!inputWasCommon) {
			if (modified_I == "Talk_To_Dad") {
				function.SetupDialog("Arlan", "Dad", true);
				function.Action("ClearDialog()", true);
				if (!hasStoryBook) {
					function.Action("SetDialog(Arlan! Take this book of stories and ask the Town Elder to tell you about them [takeBook | Sure thing Dad!])", true);
				}
				else {
					function.Action("SetDialog(Go talk to the Town Elder about the stroybook.[end | Will do!])", true);
				}
			}
			else if (modified_I == "Selected"){
				modified_I = function.splitInput(i, 0, true);

				if (modified_I == "takeBook") {
					function.Action("HideDialog()", true);
					for (string item : dadInv) {
						function.Action("AddToList(" + item + ")", true);
					}
					function.Action("ShowList(Dad)", true);
				}
				if (modified_I == "end") {
					function.Action("HideDialog()", true);
				}
			}
			else if (modified_I == "Take_StoryBook") {
				function.Action("RemoveFromList(StoryBook)", true);
				for (int i = 0; i < dadInv.size(); i++) {
					if (dadInv[i] == "StoryBook") {
						dadInv.erase(dadInv.begin() + i);
					}
				}
				function.Action("DisableIcon(Take_StoryBook, StoryBook)", true);
				playerInv.push_back("StoryBook");
				function.Action("HideList()", true);
				hasStoryBook = true;
			}
			else if(modified_I == "Open_Door"){
				if (hasStoryBook) {
					function.Transition("Arlan", "ArlanCottage.Door", "CurrentTown.BlueHouseDoor");
					inCurrentTown = true;
					inArlanCottage = false;
					//runCurrentTown();
				}
				else {
					function.SetupDialog("Arlan", "Dad", true);
					function.Action("ClearDialog()", true);
					function.Action("SetDialog(Arlan! Come over here.I have something for you.[end| Ok])", true);
				}
			}
		}

	}


}