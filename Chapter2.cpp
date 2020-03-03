/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Chapter2.cpp
-- File Description: The execution related to Chapter 2.
*/
#include "Chapter2.h"
#include <chrono>
#include <thread>
//#include "functions.cpp"
using namespace std;

Chapter2::Chapter2() {
	runSetup();
	run();
}

Chapter2::~Chapter2() {
}

bool Chapter2::runSetup() { // runs initial setup for chapter 2. returns true if setup was successful.
	//location setup calls
	setupCurrentRuins("CurrentRuins");

	return true;
}

void Chapter2::run() { // begins chapter 2's execution
	runCurrentRuins();
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
bool Chapter2::setupCurrentRuins(string name) {
	currentRuins = Ruins(name);

	//character setup
	function.SetupCharacter("Arlan", "B", "Peasant", "Spiky", "Brown", "CurrentRuins.Exit");

	//icons
	currentRuins.icons.push_back(Icon("Examine", "Hand", "CurrentRuins.Altar", "Examine the Altar", "true"));
	function.SetupIcons(currentRuins.icons);

	function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupCottage(string name) {
	currentCottage = Cottage(name);

	function.Action("CreateItem(Letter, OpenScroll)", true);
	function.Action("SetPosition(Letter, CurrentCottage.Table)", true);

	//character setup
	function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "CurrentCottage.Bed");

	//icons
	currentCottage.icons.push_back(Icon("Open", "Exit", "CurrentCottage.Door", "Leave the Room", "true"));
	currentCottage.icons.push_back(Icon("Read", "Research", "Letter", "Read the Letter", "true"));
	function.SetupIcons(currentCottage.icons);

	function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupForestPath(string name) {
	currentForestPath = ForestPath(name);

	//character setup
	function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "CurrentForestPath.EastEnd");

	//icons

	function.Action("ShowMenu()", true);

	return true;
}

bool Chapter2::setupCity(string name) {
	currentCity = City(name);

	//character setup
	function.SetupCharacter("Mathias", "F", "LightArmour", "Long", "Brown", "CurrentCity.WestEnd");

	//icons

	function.Action("ShowMenu()", true);

	return true;
}




// location execution functions.
void Chapter2::runCurrentRuins() {
	while (true) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		//If it's under the "Selected" keyword
		bool inputWasCommon = function.checkCommonKeywords(i, modified_I, "Arlan", arlanInv);

		if (!inputWasCommon) {
			//If it's under the "Talk" keyword
			if (modified_I == "Talk") {
				modified_I = function.splitInput(i, 0, true);
			}
			//if the player is in the CurrentRuins
			else if (inCurrentRuins) {
				if (modified_I == "Examine") {
					flashback1();
				}
			}
		}
	}
}

void Chapter2::runCottage() {
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
			}
		}
		
	}
}

void Chapter2::runForestPath() {
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
			}
		}
	}
}

void Chapter2::runCity() {
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
			}
		}
	}
}