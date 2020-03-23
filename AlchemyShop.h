#pragma once
/* Project: CS395
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: AlchemyShop.h
-- File Description:
--		A file that describes a class representing the ruins location in the game. Coincides with the
--		"AlchemyShop" Place in Camelot, and contains data and code for what can occur in this location.
*/
#include <vector>
#include <string>
#include "functions.h"

using namespace std;

class AlchemyShop {
public:
	AlchemyShop();
	AlchemyShop(string name); //overloaded constructor for giving the location a Camelot name immediately

	//functions for enabling/disabling furniture
	void enableChest(bool enabled);
	void enableBar(bool enabled);
	void enableRightBookcase(bool enabled);
	void enableLeftBookcase(bool enabled);
	void enableBookshelf(bool enabled);
	void enableTable(bool enabled);
	void enableAlchemistTable(bool enabled);
	void enableCauldron(bool enabled);
	void enableFireplace(bool enabled);



	// name of the ruins place for Camelot's use
	string name;

	// icons relevant to this location only
	vector<Icon> icons;

	// names of all of the furniture
	string Chest, Bar, RightBookcase, LeftBookcase, Bookshelf, Table, AlchemistTable, Cauldron, Fireplace;

	// names of all the entrances
	string Door, BackDoor;

	// inventories for furniture in this place
	vector<string> chestInv;

	//accessing common function calls
	functions function;
};