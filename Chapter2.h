/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: Chapter2.h
-- File Description: A file that describes the data and code that is relevant to chapter 2.
*/
#pragma once
#include <vector>
#include "icon.h"

using namespace std;

class Chapter2 {
public:
	Chapter2();
	~Chapter2();
	bool runSetup(); // runs initial setup for chapter 2. returns true if setup was successful.
	void run(); // begins chapter 2's execution
	
	// location setup functions. return true if setup was successful.
	bool setupRuins();

	// location execution functions.
	void runRuins();

	// interactions relevant to this chapter.
	vector<Icon> icons;

	// character inventories for this chapter (to be moved to a universal story class)
	vector<string> playerInv;
	vector<string> grandmotherInv;
	vector<string> sellerInv;

	// conditionals relevant to this chapter.
	bool has_coin;
	bool has_apple;
	bool has_sword;
	vector<bool> checks;

	// parser string for this chapter.
	string modified_I;
};