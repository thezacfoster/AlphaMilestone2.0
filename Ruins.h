/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Ruins.h
-- File Description:
--		A file that describes a class representing the ruins location in the game. Coincides with the 
--		"Ruins" Place in Camelot, and contains data and code for what can occur in this location.
*/
#pragma once
#include <vector>
#include <string>
#include "functions.h"

using namespace std;

class Ruins {
public:
	Ruins();
	Ruins(string name); //overloaded constructor for giving the location a Camelot name immediately

	//functions for enabling/disabling furniture
	void enableDirtPile(bool enabled);
	void enablePlant(bool enabled);
	void enableAltar(bool enabled);
	void enableThrone(bool enabled);
	void enableChest(bool enabled);

	

	// name of the ruins place for Camelot's use
	string name;

	// names of all of the furniture
	string DirtPile, Plant, Altar, Throne, Chest;
	
	// names of all the entrances
	string Exit;

	// inventories for furniture in this place
	vector<string> dirtPileInv, chestInv;

	//accessing common function calls
	functions function;
};
