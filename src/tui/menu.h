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
			std::cout << "Wyszukiwanie" << std::endl;

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
					update_pony(db, child_p);
				}
				catch (std::exception& e) {
					std::cout << e.what() << std::endl;
				}
				state = MenuState::MAIN;
			}
			break;
		case MenuState::FIGHT:
			state = MenuState::MAIN;
			break;
		case MenuState::SEARCH:
			{
				auto ponies = load_all_ponies(db);
				for (const auto& pony : ponies) {
					std::cout << pony.name << std::endl;
				}
			}
			state = MenuState::MAIN;
			break;
		}
	}
};
