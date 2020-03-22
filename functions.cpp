/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: functions.cpp
-- File Description:
--		A number of functions that simplify important and commonly-used processes in Camelot.
*/

#include <iostream>
#include <string>
#include <vector>
#include "icon.h"
#include "functions.h"

using namespace std;

// Wait for given input before continueing
void functions::WaitFor(string message) {
	while (true) {
		string i;
		getline(cin, i);
		if (i == message) {
			break;
		}
	}
}

// Send a command to Camelot.
void functions::Action(string command, bool waitUntilSuccess) {
	cout << ("start " + command) << endl;
	if (waitUntilSuccess) {
		WaitFor("succeeded " + command);
	}
}

//Character Creation Function
void functions::SetupCharacter(string name, string bodyType, string clothing, string hairStyle, string hairColor, string position) {

	Action("CreateCharacter(" + name + ", " + bodyType + ")", true);

	if (clothing != "") {
		Action("SetClothing(" + name + ", " + clothing + ")", true);
	}
	if (hairStyle != "") {
		Action("SetHairStyle(" + name + ", " + hairStyle + ")", true);
	}
	if (hairColor != "") {
		Action("SetHairColor(" + name + ", " + hairColor + ")", true);
	}
	if (position != "") {
		Action("SetPosition(" + name + ", " + position + ")", true);
	}
}

//Icon Setup
void functions::SetupIcons(vector<Icon> icons) {

	for (int i = 0; i != icons.size(); i++) {
		Action("EnableIcon(" + icons[i].getTitle() + ", " + icons[i].getImage() + ", " + icons[i].getObject() + ", " + icons[i].getDescription() + ", " + icons[i].getIsDefault() + ")", true);
	}

}

//Does the inital setup for Dialog
void functions::SetupDialog(string mainChar, string talkingTo, bool walk) {
	string actionString = "";

	Action("DisableInput()", true);

	if (walk == true) {
		Action("WalkTo(" + mainChar + ", " + talkingTo + ")", true);
	}
	Action("ShowDialog()", true);
	Action("ClearDialog()", true);

	Action("SetLeft(" + mainChar + ")", true);

	Action("SetRight(" + talkingTo + ")", true);
	Action("EnableInput()", true);
}

void functions::ShowInv(string person, vector<string> inventory) {
	Action("HideDialog()", true);
	for (string item : inventory) {
		Action("AddToList(" + item + ")", true);
	}
	Action("ShowList(" + person + ")", true);
}

//Handles all of purchasing something for a coin
void functions::Grab(string purchase, string input, vector<string>& storeInv, vector<string>& inventory, bool& coin, bool& itemCheck, bool purchaseCheck) {

	Action("RemoveFromList(" + purchase + ")", true);
	for (int i = 0; i < (signed)storeInv.size(); i++) {
		if (storeInv[i] == purchase) {
			storeInv.erase(storeInv.begin() + i);
		}
	}
	Action("DisableIcon(" + input + ", " + purchase + ")", true);
	if (purchaseCheck) {
		inventory.erase(inventory.begin());
	}
	inventory.push_back(purchase);
	Action("HideList()", true);

	if (purchaseCheck) {
		coin = false;
		itemCheck = true;
	}

}

//Splits the input into one of its words. NumToSkip is to skip to the start of the word you want, Reverse is to start 
//at the end of the string
string functions::splitInput(string input, int numToSkip, bool reverse) {
	string output = "";

	//For going forwards
	if (!reverse) {
		for (int i = 0 + numToSkip; i < input.size(); i++) {
			if (input[i] == ' ') {
				i = input.size();
			}
			if (i != input.size()) {
				output = output + input[i];
			}
		}
	}

	//For going backwards
	else {
		for (int i = input.size() - 1; i > 0; i--) {
			if (input[i] == ' ') {
				i = 0;
			}
			if (i != 0) {
				output = input[i] + output;
			}
		}
	}

	return output;
}

// performs actions for the most common keywords received from Camelot
bool functions::checkCommonKeywords(string input, string modifiedInput, string playerName, vector<string> playerInv) {
	bool keywordFound = true;
	//If it's under the "Selected" keyword
	if (modifiedInput == "Selected") {

		modifiedInput = splitInput(input, 0, true);

		if (modifiedInput == "Start") {
			StartOption(playerName);
			Action("EnableInput()", true);
		}
		else if (modifiedInput == "Resume") {
			Action("HideMenu()", true);
			Action("EnableInput()", true);
			Action("EnableInput()", true);
		}
		else if (modifiedInput == "Quit") {
			Action("Quit()", true);
		}
		else if (modifiedInput == "end") {
			Action("HideDialog()", true);
		}
		else keywordFound = false;
	}
	//If it's under the "Key" keyword
	else if (modifiedInput == "Key") {

		modifiedInput = splitInput(input, 0, true);
		if (modifiedInput == "Inventory") {
			Action("ClearList()", true);
			for (string item : playerInv) {
				Action("AddToList(" + item + ")", true);
			}
			Action("ShowList(" + playerName + ")", true);
		}
		else if (modifiedInput == "Pause") {
			Action("DisableInput()", true);
			Action("ShowMenu()", true);
		}
		else keywordFound = false;
	}

	//If it's under the "Close" keyword
	else if (modifiedInput == "Close") {
		modifiedInput = splitInput(input, 0, true);
		if (modifiedInput == "Narration") {
			Action("HideNarration()", true);
		}
		else {
			CloseList();
		}
	}
	else keywordFound = false;

	return keywordFound;
}

//Closing narration box
void functions::CloseList() {
	Action("HideList()", true);
	Action("ClearList()", true);
	Action("EnableInput()", true);
}

//Transition to other areas
void functions::Transition(string character, string exit, string entrance) {
	Action("Exit(" + character + ", " + exit + ", true)", true);
	Action("Enter(" + character + ", " + entrance + ", true)", true);
}

//Start option
void functions::StartOption(string mainChar) {
	Action("SetCameraFocus(" + mainChar + ")", true);
	Action("HideMenu()", true);
	Action("EnableInput()", true);
}

//inventory interaction
void functions::AccessInventory(vector<string> inventory, string charName) {
	Action("HideDialog()", true);
	for (string item : inventory) {
		Action("AddToList(" + item + ")", true);
	}
	Action("ShowList(" + charName + ")", true);
}

void functions::WalkToPlace(string character, string location) {
	Action("DisableInput()", true);
	Action("WalkTo(" + character + ", " + location + ")", true);
	Action("EnableInput()", true);
}

void functions::SetupDialogText(string message, string responseKey1, string response1, string responseKey2, string response2, string responseKey3, string response3) {
	Action("ClearDialog()", true);
	if ((responseKey3 != "nothing") && (response3 != "nothing")) {
		Action("SetDialog(" + message + " [" + responseKey1 + " | " + response1 + "] [" + responseKey2 + " | " + response2 + "] [" + responseKey3 + " | " + response3 + "])", true);
	}
	else if ((responseKey2 != "nothing") && (response2 != "nothing") && (responseKey3 == "nothing") && (response3 == "nothing")) {
		Action("SetDialog(" + message + " [" + responseKey1 + " | " + response1 + "] [" + responseKey2 + " | " + response2 + "])", true);
	}
	else {
		Action("SetDialog(" + message + " [" + responseKey1 + " | " + response1 + "])", true);
	}
}