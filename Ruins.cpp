/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Ruins.cpp
-- File Description:
--		A file that defines a class representing the ruins location in the game. Coincides with the
--		"Ruins" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include "Ruins.h"
//#include "functions.cpp"

Ruins::Ruins() {}

//overloaded constructor for giving the location a Camelot name immediately
Ruins::Ruins(string name) {
	function.Action("CreatePlace(" + name + ", Ruins)", true);
}

//functions for enabling/disabling furniture
void Ruins::enableDirtPile(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(DirtPile." + name + ")", true);
	}
	else
		function.Action("HideFurniture(DirtPile." + name + ")", true);
	
}
void Ruins::enablePlant(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Plant." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Plant." + name + ")", true);
}
void Ruins::enableAltar(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Altar." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Altar." + name + ")", true);
}
void Ruins::enableThrone(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Throne." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Throne." + name + ")", true);
}
void Ruins::enableChest(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Chest." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Chest." + name + ")", true);
}