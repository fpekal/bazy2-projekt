#pragma once
#include <iostream>
#include <string>
#include <ranges>

#include "../db/pony-loader.h"
#include "../db/pony-saver.h"
#include "../breeding.h"
#include "../genes.h"
#include "../db/genes-saver.h"

static Gene::Type get_gene_type_from_string(const std::string& s) {
	if (s == "AA") {
		return Gene::Type::AA;
	} else if (s == "Aa") {
		return Gene::Type::Aa;
	} else if (s == "aA") {
		return Gene::Type::aA;
	} else {
		return Gene::Type::aa;
	}
}

class Menu {
public:
	enum MenuState {
		MAIN,
		BREEDING,
		FIGHT,
		SEARCH,
		SEARCH_STATS,
		ADMIN
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
			std::cout << "4. Wyszukaj kucyka po statystykach\n";
			std::cout << "5. Wyszukaj losowego kucyka\n";
			std::cout << "6. Powrot do menu glownego\n";
			break;
		case MenuState::SEARCH_STATS:
			std::cout << "Wyszukaj kucyka po statystykach\n";
			std::cout << "1. Życie\n";
			std::cout << "2. Maksymalne zdrowie\n";
			std::cout << "3. Minimalne obrażenia\n";
			std::cout << "4. Maksymalne obrażenia\n";
			std::cout << "5. Szybkość ataku\n";
			std::cout << "6. Obrona\n";
			std::cout << "7. Powrot do menu glownego\n";
			break;
		case MenuState::ADMIN:
			std::cout << "Admin" << std::endl;
			std::cout << "1. Utworz nowego kucyka\n";
			std::cout << "2. Usun kucyka\n";
			std::cout << "3. Zmien statystyki kucyka\n";
			std::cout << "4. Dodaj gen kucykowi\n";
			std::cout << "5. Usun gen kucykowi\n";
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
				} else if (input == "4") {
					state = MenuState::ADMIN;
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
					std::cout << "Podano błędne dane" << std::endl;
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
						if (fight.left_pony.health <= 0 || fight.right_pony.health <= 0) {
							break;
						}
						std::cout << "----------------------------------" << std::endl;
						std::cout << fight.left_pony.name << ":\n";
						std::string bar1;
						bar1.resize((int)((float)fight.left_pony.health / fight.left_pony.get_effective_stats().max_health * 20), '#');
						bar1.resize(20, '_');
						std::cout << "|" << bar1 << '|' << std::endl;
						std::cout << fight.right_pony.name << ":\n";
						std::string bar2;
						bar2.resize((int)((float)fight.right_pony.health / fight.right_pony.get_effective_stats().max_health * 20), '#');
						bar2.resize(20, '_');
						std::cout << "|" << bar2 << '|' << std::endl;
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
					std::cout << "Podano błędne dane" << std::endl;
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
					state = MenuState::SEARCH_STATS;
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
		case MenuState::SEARCH_STATS:
			{
				auto ponies = load_all_ponies(db);
				while(true) {
					std::cout << "Szukaj kucyka po statystykach\n";
					std::cout << "1. Życie\n";
					std::cout << "2. Maksymalne zdrowie\n";
					std::cout << "3. Minimalne obrażenia\n";
					std::cout << "4. Maksymalne obrażenia\n";
					std::cout << "5. Szybkość ataku\n";
					std::cout << "6. Obrona\n";
					std::cout << "7. Regeneracja zdrowia\n";
					std::cout << "8. Wyświetl odfiltrowane kucyki\n";
					std::cout << "9. Zresetuj filtr\n";
					std::cout << "10. Powrot\n";

					std::string input;
					std::getline(std::cin, input);

					auto filter_factory = [](int min, int max, int Stats::* stat) {
						return [min, max, stat](const Pony& pony) {
							return pony.get_effective_stats().*stat >= min && pony.get_effective_stats().*stat <= max;
						};
					};

					if (input == "1") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									[min = std::stoi(min), max = std::stoi(max)](const Pony& pony) {
										return pony.health >= min && pony.health <= max;
									}
								)
						);
					}
					else if (input == "2") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									filter_factory(std::stoi(min), std::stoi(max), &Stats::max_health)
								)
						);
					}
					else if (input == "3") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									filter_factory(std::stoi(min), std::stoi(max), &Stats::min_damage)
								)
						);
					}
					else if (input == "4") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									filter_factory(std::stoi(min), std::stoi(max), &Stats::max_damage)
								)
						);
					}
					else if (input == "5") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									filter_factory(std::stoi(min), std::stoi(max), &Stats::attack_speed)
								)
						);
					}
					else if (input == "6") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									filter_factory(std::stoi(min), std::stoi(max), &Stats::armor)
								)
						);
					}
					else if (input == "7") {
						std::cout << "[min, max]: ";
						std::string min, max;
						std::cin >> min >> max;
						ponies = std::ranges::to<decltype(ponies)>(
								ponies | std::views::filter(
									filter_factory(std::stoi(min), std::stoi(max), &Stats::health_regeneration)
								)
						);
					}
					else if (input == "8") {
						for (const auto& pony : ponies) {
							draw_pony(pony);
							std::cin.get();
						}
					}
					else if (input == "9") {
						ponies = load_all_ponies(db);
					}
					else if (input == "10") {
						state = MenuState::SEARCH;
						break;
					}
				}
			}
			break;
		case MenuState::ADMIN:
			{
				std::string input;
				std::getline(std::cin, input);

				if (input == "1") {
					std::string name;
					std::getline(std::cin, name);
					create_pony(db, name);
					break;
				}
				if (input == "2") {
					std::string name;
					std::getline(std::cin, name);
					Pony p = load_pony(db, name);
					delete_pony(db, p.id);
					break;
				}
				if (input == "3") {
					std::string name;
					std::string max_health, min_damage, max_damage, attack_speed, armor, health_regeneration;

					std::getline(std::cin, name);
					std::cin >> max_health >> min_damage >> max_damage >> attack_speed >> armor >> health_regeneration;

					Pony p = load_pony(db, name);
					p.learned_stats.max_health = std::stoi(max_health);
					p.learned_stats.min_damage = std::stoi(min_damage);
					p.learned_stats.max_damage = std::stoi(max_damage);
					p.learned_stats.attack_speed = std::stoi(attack_speed);
					p.learned_stats.armor = std::stoi(armor);
					p.learned_stats.health_regeneration = std::stoi(health_regeneration);
					update_pony(db, p);
					break;
				}
				if (input == "4") {
					std::string name;
					std::string gene_category, type;

					std::getline(std::cin, name);
					std::cin >> gene_category >> type;

					Pony p = load_pony(db, name);

					GeneCategory& gc = GeneCategory::categories.at(std::stoi(gene_category));
					Gene g = create_gene(db, gc, p);
					g.type = get_gene_type_from_string(type);
					update_gene(db, g);
					update_pony(db, p);
					break;
				}
				if (input == "5") {
					std::string name;
					std::string gene_id;

					std::getline(std::cin, name);
					std::getline(std::cin, gene_id);

					Pony p = load_pony(db, name);

					delete_gene(db, std::stoi(gene_id));
					update_pony(db, p);
					break;
				}
				if (input == "6") {
					state = MenuState::MAIN;
					break;
				}
			}
		}
	}
};
