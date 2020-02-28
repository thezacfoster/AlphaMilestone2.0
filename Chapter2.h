/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: em.cpp
-- File Description: The primary execution location of the experience manager.
*/
#pragma once
#include <vector>
#include "icon.h"

using namespace std;

class Chapter2 {
public:
	Chapter2();
	~Chapter2();
	bool runSetup(); // runs setup for chapter 1. returns true if setup was successful.
	void run(); // runs the chapter

	vector<Icon> icons;

	vector<string> playerInv;
	vector<string> grandmotherInv;
	vector<string> sellerInv;

	bool has_coin;
	bool has_apple;
	bool has_sword;
	vector<bool> checks;
	string modified_I;
};