/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Chapter2.h
-- File Description: A file that describes the data and code that is relevant to chapter 2.
*/
#pragma once
#include <vector>
#include "icon.h"
#include "Ruins.h"
#include "Cottage.h"
#include "functions.h"

using namespace std;

class Chapter2 {
public:
	Chapter2();
	~Chapter2();
	bool runSetup(); // runs initial setup for chapter 2. returns true if setup was successful.
	void run(); // begins chapter 2's execution
	
	// location setup functions. return true if setup was successful.
	bool setupRuins(string name);
	bool setupCottage(string name);

	// location execution functions.
	void runRuins();
	void runCottage();

	void flashback1();

	

	// interactions relevant to this chapter.
	vector<Icon> icons;

	Ruins currentRuins;
	Cottage currentCottage;
	

	// character inventories for this chapter (to be moved to a universal story class)
	vector<string> arlanInv;
	vector<string> mathiasInv;

	// conditionals relevant to this chapter.
	bool inCurrentRuins;
	vector<bool> checks;

	// parser string for this chapter.
	string modified_I;

	//accessing common functions
	functions function;
};