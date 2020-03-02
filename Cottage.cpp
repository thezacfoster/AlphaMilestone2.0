/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Ruins.cpp
-- File Description:
--		A file that defines a class representing the ruins location in the game. Coincides with the
--		"Ruins" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include "Cottage.h"
//#include "functions.cpp"

Cottage::Cottage() {}

//overloaded constructor for giving the location a Camelot name immediately
Cottage::Cottage(string name) {
	function.Action("CreatePlace(" + name + ", Cottage)", true);
}

//functions for enabling/disabling furniture
void Cottage::enableBed(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Bed." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Bed." + name + ")", true);

}
void Cottage::enableFireplace(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Fireplace." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Fireplace." + name + ")", true);
}
void Cottage::enableChair(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Chair." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Chair." + name + ")", true);
}
void Cottage::enableTable(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Table." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Table." + name + ")", true);
}
void Cottage::enableShelf(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Shelf." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Shelf." + name + ")", true);
}
void Cottage::enableBookshelf(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Bookshelf." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Bookshelf." + name + ")", true);
}
void Cottage::enableChest(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Chest." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Chest." + name + ")", true);
}