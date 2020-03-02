/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Ruins.cpp
-- File Description:
--		A file that defines a class representing the ruins location in the game. Coincides with the
--		"Ruins" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include "ForestPath.h"
//#include "functions.cpp"

ForestPath::ForestPath() {}

//overloaded constructor for giving the location a Camelot name immediately
ForestPath::ForestPath(string name) {
	function.Action("CreatePlace(" + name + ", ForestPath)", true);
}

//functions for enabling/disabling furniture
void ForestPath::enableWell(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Well." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Well." + name + ")", true);

}
void ForestPath::enablePlant(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Plant." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Plant." + name + ")", true);
}
void ForestPath::enableDirtPile(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(DirtPile." + name + ")", true);
	}
	else
		function.Action("HideFurniture(DirtPile." + name + ")", true);
}