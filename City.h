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

class City {
public:
	City();
	City(string name); //overloaded constructor for giving the location a Camelot name immediately

	//functions for enabling/disabling furniture
	void enableBench(bool enabled);
	void enableFountain(bool enabled);
	void enablePlant(bool enabled);
	void enableBarrel(bool enabled);
	void enableHorse(bool enabled);



	// name of the ruins place for Camelot's use
	string name;

	// icons relevant to this location only
	vector<Icon> icons;

	// names of all of the furniture
	string Bench, Fountain, Plant, Barrel, Horse;

	// names of all the entrances
	string NorthEnd, EastEnd, WestEnd, GreenHouseDoor, BrownHouseDoor, RedHouseDoor, BlueHouseDoor;

	// inventories for furniture in this place
	vector<string> barrelInv;

	//accessing common function calls
	functions function;
};