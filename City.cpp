/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Ruins.cpp
-- File Description:
--		A file that defines a class representing the ruins location in the game. Coincides with the
--		"Ruins" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include "City.h"
//#include "functions.cpp"

City::City() {}

//overloaded constructor for giving the location a Camelot name immediately
City::City(string name) {
	function.Action("CreatePlace(" + name + ", City)", true);
}

//functions for enabling/disabling furniture
void City::enableBench(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Bench." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Bench." + name + ")", true);

}
void City::enableFountain(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Fountain." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Fountain." + name + ")", true);
}
void City::enablePlant(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Plant." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Plant." + name + ")", true);
}
void City::enableBarrel(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Barrel." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Barrel." + name + ")", true);
}
void City::enableHorse(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Horse." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Horse." + name + ")", true);
}