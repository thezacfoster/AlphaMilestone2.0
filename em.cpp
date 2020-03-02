/* Project: CS395 Alpha Milestone
-- Project Description: An experimental experience manager for the Camelot Virtual Environment.
-- Authors: Jake Hayden, John Colfer, Mac McNerney, Zac Foster
-- File: em.cpp
-- File Description: The primary execution location of the experience manager.
*/

#include <iostream>
#include <string>
#include "Chapter2.h"


using namespace std;

int main() {
	Chapter2();

	//----------Pre architecture modification, mac part 1----------
		//Place Creations
		Action("CreatePlace(CurrentTown, City)", true);
		Action("CreatePlace(CurrentForestPath, ForestPath)", true);
		Action("CreatePlace(CurrentRuins, Ruins)", true);

		//Arlon Character
		Action("CreateCharacter(Arlon, B)", true);
		Action("SetClothing(Arlon, LightArmour)", true);
		Action("SetHairStyle(Arlon, Long)", true);
		Action("SetPosition(Arlon, CurrentTown.Fountain)", true);
		//Mariah Character
		Action("CreateCharacter(Mariah, G)", true);
		Action("SetClothing(Mariah, Beggar)", true);
		Action("SetHairStyle(Mariah, Straight)", true);
		Action("SetHairColor(Mariah, Gray)", true);
		Action("SetPosition(Mariah, CurrentForestPath.Well)", true);

		//Items
		Action("CreateItem(MathiasSword, Sword)", true);
		Action("CreateItem(ArchieSpellbook, SpellBook)", true);
		Action("CreateItem(FlashbackPotion1, GreenPotion)", true);

		//Icons
		Action("EnableIcon(Talk_To_Mariah, Talk, Mariah, Talk To Mariah, true)", true);
		Action("EnableIcon(Take_MathiasSword, Coins, MathiasSword, Take the sword, true)", true);
		Action("EnableIcon(Take_ArchieSpellbook, Coins, ArchieSpellbook, Take the spellbook, true)", true);

		//Menu
		Action("ShowMenu()", true);

		Action("EnableEffect(CurrentRuins.Altar, Resurrection)", true);

		//Inventories
		vector<string> playerInv;
		vector<string> mariahInv;
		mariahInv.push_back("MathiasSword");
		mariahInv.push_back("ArchieSpellbook");

		bool item_taken = false;
		bool item_placed = false;
		bool sword_taken = false;
		bool spellbook_taken = false;

		while (true) {
			string i;
			getline(cin, i);
			if (i == "input Selected Start") {
				Action("SetCameraFocus(Arlon)", true);
				Action("HideMenu()", true);
				Action("EnableInput()", true);
			}

			//----------dialogue----------
			else if (i == "input Talk_To_Seller Seller") {
				Action("DisableInput()", true);
				Action("WalkTo(Arlan, Mariah)", true);
				Action("ShowDialog()", true);
				Action("ClearDialog()", true);
				Action("SetLeft(Arlan)", true);
				Action("SetRight(Mariah)", true);
				Action("EnableInput()", true);
				if (item_taken)
					Action("SetDialog(Have a good day! [end|Thanks, you too.])", true);
				else
					Action("SetDialog(The ruins is a mysterious place. May I offer you a gift for your journey? [takeFromMariah|Yes please!] [end|No Thanks.])", true);
			}

			else if (i == "input Selected takeFromMariah") {
				Action("HideDialog()", true);
				for (string item : mariahInv) {
					Action("AddToList(" + item + ")", true);
				}
				Action("ShowList(Mariah)", true);
			}

			else if (i == "input Selected end") {
				Action("HideDialog()", true);
			}
			//----------dialogue----------

			//----------item interactions----------
			else if (i == "input Take_MathiasSword MathiasSword") {
				Action("RemoveFromList(MathiasSword)", true);
				for (int i = 0; i < mariahInv.size(); i++) {
					if (mariahInv[i] == "MathiasSword") {
						mariahInv.erase(mariahInv.begin() + i);
					}
				}
				Action("DisableIcon(Take_MathiasSword, MathiasSword)", true);
				playerInv.erase(playerInv.begin());
				playerInv.push_back("MathiasSword");
				Action("HideList()", true);
				item_taken = true;
				sword_taken = true;
			}

			else if (i == "input Take_ArchieSpellbook ArchieSpellbook") {
				Action("RemoveFromList(ArchieSpellbook)", true);
				for (int i = 0; i < mariahInv.size(); i++) {
					if (mariahInv[i] == "ArchieSpellbook") {
						mariahInv.erase(mariahInv.begin() + i);
					}
				}
				Action("DisableIcon(Take_ArchieSpellbook, ArchieSpellbook)", true);
				playerInv.erase(playerInv.begin());
				playerInv.push_back("ArchieSpellbook");
				Action("HideList()", true);
				item_taken = true;
				spellbook_taken = true;
			}

			else if (i == "input arrived Arlon position CurrentRuins.Altar") {
				if (!item_placed) {
					Action("DisableInput()", true);
					Action("ShowDialog()", true);
					Action("ClearDialog()", true);
					Action("EnableInput()", true);
					Action("SetDialog(You hear a whisper. \"Place the tribute to see the past.\" Place your item? [placeSwordSpellbook|(Yes)] [end|(No)])", true);
				}
			}

			else if (i == "input Selected placeSwordSpellbook") {
				if (sword_taken) {
					for (int i = 0; i < playerInv.size(); i++) {
						if (playerInv[i] == "MathiasSword") {
							playerInv.erase(playerInv.begin() + i);
						}
					}
					Action("SetPosition(MathiasSword, CurrentRuins.Altar.Top)", true);
				}
				else if (spellbook_taken) {
					for (int i = 0; i < playerInv.size(); i++) {
						if (playerInv[i] == "ArchieSpellbook") {
							playerInv.erase(playerInv.begin() + i);
						}
					}
					Action("SetPosition(ArchieSpellbook, CurrentRuins.Altar.Top)", true);
				}
				Action("EnableEffect(CurrentRuins.Altar, Resurrection)", true);
				item_placed = true;
				Action("SetPosition(MathiasSword)", true);
				Action("SetPosition(ArchieSpellbook)", true);
				Action("SetPosition(FlashbackPotion1, CurrentRuins.Altar.Top)", true);
			}
			//----------item interactions----------

			//----------transitions----------
			else if (i == "input arrived Arlon position CurrentTown.EastEnd") {
				Action("Exit(Arlon, CurrentTown.EastEnd, true)", true);
				Action("Enter(Arlon, CurrentForestPath.WestEnd, true)", true);
			}

			else if (i == "input arrived Arlon position CurrentForestPath.EastEnd") {
				Action("Exit(Arlon, CurrentForestPath.EastEnd, true)", true);
				Action("Enter(Arlon, CurrentRuins.Exit, true)", true);
			}
			//----------transitions----------

			//----------inventory----------
			else if (i == "input Key Inventory") {
				Action("ClearList()", true);
				for (string item : playerInv) {
					Action("AddToList(" + item + ")", true);
				}
				Action("ShowList(Arlon)", true);
			}

			else if (i == "input Close List") {
				Action("HideList()", true);
				Action("EnableInput()", true);
			}
			//----------inventory----------
			//----------Pre architecture modification, mac part 1----------
}