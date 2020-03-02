/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: em.cpp
-- File Description: The primary execution location of the experience manager.
*/
#include "Chapter2.h"
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
	setupRuins("CurrentRuins");
	
	//character setup
	function.SetupCharacter("Arlan", "B", "Peasant", "Spiky", "Brown", "CurrentRuins.Exit");

	//icons
	icons.push_back(Icon("Examine", "Hand", "CurrentRuins.Altar", "Examine the Altar", "true"));
	function.SetupIcons(icons);
	
	
	
	function.Action("ShowMenu()", true);
	return true;
}
void Chapter2::run() { // begins chapter 2's execution
	while (true) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = function.splitInput(i, 6, false);

		//If it's under the "Selected" keyword
		if (modified_I == "Selected") {

			modified_I = function.splitInput(i, 0, true);

			if (modified_I == "Start") {
				function.StartOption("Arlan");

			}
			else if (modified_I == "Resume") {
				function.Action("HideMenu()", true);
				function.Action("EnableInput()", true);
				function.Action("EnableInput()", true);
			}
			else if (modified_I == "Quit") {
				function.Action("Quit()", true);
			}
		}
		//If it's under the "Key" keyword
		else if (modified_I == "Key") {

			modified_I = function.splitInput(i, 0, true);
			if (modified_I == "Inventory") {
				function.Action("ClearList()", true);
				for (string item : playerInv) {
					function.Action("AddToList(" + item + ")", true);
				}
				function.Action("ShowList(Arlan)", true);
			}
			else if (modified_I == "Pause") {
				function.Action("DisableInput()", true);
				function.Action("ShowMenu()", true);
			}
		}

		//If it's under the "Close" keyword
		else if (modified_I == "Close") {
			function.CloseList();
		}

		//If it's under the "Talk" keyword
		else if (modified_I == "Talk") {
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
	function.Action("Die(Arlan)", false);
	function.Action("SetCameraMode(Follow)", true);
	function.Action("FadeOut()", true);
	
	//
}

// location setup functions. return true if setup was successful.
bool Chapter2::setupRuins(string name) {
	Ruins CurrentRuin(name);

	return true;
}

// location execution functions.
void Chapter2::runRuins() {

}
