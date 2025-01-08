#pragma once
#include <iostream>
#include <string>

#include "../db/pony-loader.h"
#include "../db/pony-saver.h"
#include "../breeding.h"

class Menu {
public:
	enum MenuState {
		MAIN,
		BREEDING,
		FIGHT,
		SEARCH
	} state;

	Menu() {
		state = MenuState::MAIN;
	}

	void show_state() {
		switch(state) {
		case MenuState::MAIN:
			std::cout << "Menu glowne" << std::endl;
			std::cout << "1. Rozmnazanie" << std::endl;
			std::cout << "2. Walka" << std::endl;
			std::cout << "3. Wyszukiwanie" << std::endl;
			break;
		case MenuState::BREEDING:
			std::cout << "Rozmnazanie" << std::endl;
			std::cout << "Wybierz dwa kucyki do rozmnozenia (oddzielone enterem)" << std::endl;
			std::cout << "Nastepnie podaj nowe imie dla dziecka" << std::endl;
			break;
		case MenuState::FIGHT:
			std::cout << "Walka" << std::endl;
			std::cout << "Wybierz dwa kucyki do walki (oddzielone enterem)" << std::endl;
			break;
		case MenuState::SEARCH:
			std::cout << "Wyszukiwanie\n";
			std::cout << "1. Wypisz wszystkie kucyki\n";
			std::cout << "2. Wyszukaj kucyka po imieniu\n";
			std::cout << "3. Wyszkkaj kucyka po id\n";
			std::cout << "4. Wyszukaj kucyka statystykach (WIP)\n";
			std::cout << "5. Wyszukaj losowego kucyka\n";
			std::cout << "6. Powrot do menu glownego\n";
			break;
		}
	}

	void change_state(DbConnection db) {
		switch(state) {
		case MenuState::MAIN:
			{
				std::string input;
				std::getline(std::cin, input);
				if (input == "1") {
					state = MenuState::BREEDING;
				} else if (input == "2") {
					state = MenuState::FIGHT;
				} else if (input == "3") {
					state = MenuState::SEARCH;
				} else if (input == "2137") {
					std::cout <<
						"░░░░░░░░░░░░░▄▄▀▀▀▀▀▀▄▄\n"
						"░░░░░░░░░░▄▄▀▄▄▄█████▄▄▀▄\n"
						"░░░░░░░░▄█▀▒▀▀▀█████████▄█▄\n"
						"░░░░░░▄██▒▒▒▒▒▒▒▒▀▒▀▒▀▄▒▀▒▀▄\n"
						"░░░░▄██▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▄\n"
						"░░░░██▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▌\n"
						"░░░▐██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐█\n"
						"░▄▄███▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█\n"
						"▐▒▄▀██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐▌\n"
						"▌▒▒▌▒▀▒▒▒▒▒▒▄▀▀▄▄▒▒▒▒▒▒▒▒▒▒▒▒█▌\n"
						"▐▒▀▒▌▒▒▒▒▒▒▒▄▄▄▄▒▒▒▒▒▒▒▀▀▀▀▄▒▐\n"
						"░█▒▒▌▒▒▒▒▒▒▒▒▀▀▒▀▒▒▐▒▄▀██▀▒▒▒▌\n"
						"░░█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐▒▒▒▒▒▒▒▒█\n"
						"░░░▀▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▒▒▒▒▒▒▄▀\n"
						"░░░▐▒▒▒▒▒▒▒▒▒▄▀▐▒▒▒▒▒▐▒▒▒▒▄▀\n"
						"░░▄▌▒▒▒▒▒▒▒▄▀▒▒▒▀▄▄▒▒▒▌▒▒▒▐▀▀▀▄▄▄\n"
						"▄▀░▀▄▒▒▒▒▒▒▒▒▀▀▄▄▄▒▄▄▀▌▒▒▒▌░░░░░░\n"
						"▐▌░░░▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▀░░░░░░░\n"
						"░█░░░░░▀▄▄▒▒▒▒▒▒▒▒▒▒▒▒▄▀░█░░░░░░░\n"
						"░░█░░░░░░░▀▄▄▄▒▒▒▒▒▒▄▀░░░░█░░░░░░\n"
						"░░░█░░░░░░░░░▌▀▀▀▀▀▀▐░░░░░▐▌░░░░░\n";
				}
			}
			break;
		case MenuState::BREEDING:
			{
				try {
					std::string parent1, parent2, child;

					std::getline(std::cin, parent1);
					std::getline(std::cin, parent2);
					std::getline(std::cin, child);

					Pony parent1_p = load_pony(db, parent1);
					Pony parent2_p = load_pony(db, parent2);

					Pony child_p = breed(db, parent1_p, parent2_p, child);
					draw_pony(child_p);
					update_pony(db, child_p);
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
				}
				state = MenuState::MAIN;
			}
			break;
		case MenuState::FIGHT:
			{
				std::string pony1, pony2;

				std::getline(std::cin, pony1);
				std::getline(std::cin, pony2);

				try {
					auto pony1_p = load_pony(db, pony1);
					auto pony2_p = load_pony(db, pony2);
					pony1_p.health = pony1_p.get_effective_stats().max_health;
					pony2_p.health = pony2_p.get_effective_stats().max_health;

					Fight fight(pony1_p, pony2_p);

					while (fight.left_pony.health > 0 && fight.right_pony.health > 0) {
						fight.make_turn();
						std::cout << "----------------------------------" << std::endl;
						draw_pony(fight.left_pony);
						draw_pony(fight.right_pony);
						std::cout << "----------------------------------" << std::endl;
						std::cout << "c - dokończ walkę\n";
						std::cout << "ENTER - kolejna tura\n";
						{
							std::string input;
							std::getline(std::cin, input);

							if (input == "c") {
								while (fight.left_pony.health > 0 && fight.right_pony.health > 0) {
									fight.make_turn();
								}
							}
						}
					}

					std::cout << "Zwycięża " << (fight.left_pony.health > 0 ? pony1_p.name : pony2_p.name) << std::endl;
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
				}
			}
			state = MenuState::MAIN;
			break;
		case MenuState::SEARCH:
			{
				std::string input;
				std::getline(std::cin, input);

				if (input == "1") {
					auto ponies = load_all_ponies(db);
					for (const auto& pony : ponies) {
						draw_pony(pony);
						std::cin.get();
					}
					break;
				}
				if (input == "2") {
					std::string name;
					std::getline(std::cin, name);
					auto pony = load_pony(db, name);
					draw_pony(pony);
					break;
				}
				if (input == "3") {
					std::string id;
					std::getline(std::cin, id);
					auto pony = load_pony(db, std::stoi(id));
					draw_pony(pony);
					break;
				}
				if (input == "4") {
					break;
				}
				if (input == "5") {
					auto ponies = load_all_ponies(db);
					int random_index = rand() % ponies.size();
					auto pony = ponies[random_index];
					draw_pony(pony);
					break;
				}
				if (input == "6") {
					state = MenuState::MAIN;
					break;
				}
			}
			break;
		}
	}
};
