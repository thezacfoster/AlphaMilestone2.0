/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Ruins.cpp
-- File Description:
--		A file that defines a class representing the ruins location in the game. Coincides with the
--		"Ruins" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include "Blacksmith.h"
//#include "functions.cpp"

Blacksmith::Blacksmith() {}

//overloaded constructor for giving the location a Camelot name immediately
Blacksmith::Blacksmith(string name) {
	function.Action("CreatePlace(" + name + ", Blacksmith)", true);
}

//functions for enabling/disabling furniture
void Blacksmith::enableTarget(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Target." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Target." + name + ")", true);

}
void Blacksmith::enableTable(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Table." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Table." + name + ")", true);
}
void Blacksmith::enableAnvil(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Anvil." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Anvil." + name + ")", true);
}
void Blacksmith::enableChest(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Chest." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Chest." + name + ")", true);
}