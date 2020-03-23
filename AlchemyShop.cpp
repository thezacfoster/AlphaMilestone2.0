/* Project: CS395
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: AlchemyShop
-- File Description:
--		A file that defines a class representing the ruins location in the game. Coincides with the
--		"AlchemyShop" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include "AlchemyShop.h"

AlchemyShop::AlchemyShop() {}

//overloaded constructor for giving the location a Camelot name immediately
AlchemyShop::AlchemyShop(string name) {
	function.Action("CreatePlace(" + name + ", AlchemyShop)", true);
}

//functions for enabling/disabling furniture
void AlchemyShop::enableChest(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Chest." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Chest." + name + ")", true);
}
void AlchemyShop::enableBar(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Bar." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Bar." + name + ")", true);
}
void AlchemyShop::enableRightBookcase(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(RightBookcase." + name + ")", true);
	}
	else
		function.Action("HideFurniture(RightBookcase." + name + ")", true);
}
void AlchemyShop::enableLeftBookcase(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(LeftBookcase." + name + ")", true);
	}
	else
		function.Action("HideFurniture(LeftBookcase." + name + ")", true);
}
void AlchemyShop::enableBookshelf(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Bookshelf." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Bookshelf." + name + ")", true);
}
void AlchemyShop::enableTable(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Table." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Table." + name + ")", true);
}
void AlchemyShop::enableAlchemistTable(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(AlchemistTable." + name + ")", true);
	}
	else
		function.Action("HideFurniture(AlchemistTable." + name + ")", true);
}
void AlchemyShop::enableCauldron(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Cauldron." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Cauldron." + name + ")", true);
}
void AlchemyShop::enableFireplace(bool enabled) {
	if (enabled) {
		function.Action("ShowFurniture(Fireplace." + name + ")", true);
	}
	else
		function.Action("HideFurniture(Fireplace." + name + ")", true);
}