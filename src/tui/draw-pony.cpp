#include "draw-pony.h"

#include <iostream>
#include <algorithm>

#include "ponysay.h"
#include "../util.h"

static void move_to_the_next_line(int pony_width) {
	move_cursor_to_left_edge();
	move_cursor_down();
	move_cursor_right(pony_width + 2);
}

static void draw_stats(const Pony& p, int pony_width) {
	move_to_the_next_line(pony_width);
	std::cout << "|";
	move_to_the_next_line(pony_width);
	std::cout << "| " << p.name;
	move_to_the_next_line(pony_width);
	std::cout << "|";
	move_to_the_next_line(pony_width);
	std::cout << "----------------------------------";
	move_to_the_next_line(pony_width);
	std::cout << "|";
	move_to_the_next_line(pony_width);
	std::cout << "| Życie: " << p.health;
	move_to_the_next_line(pony_width);
	std::cout << "|";
	move_to_the_next_line(pony_width);
	std::cout << "----------------------------------";
	move_to_the_next_line(pony_width);
	std::cout << "|";
	move_to_the_next_line(pony_width);
	std::cout << "| Maksymalne zdrowie: " << p.get_effective_stats().max_health;
	move_to_the_next_line(pony_width);
	std::cout << "| Minimalne obrażenia: " << p.get_effective_stats().min_damage;
	move_to_the_next_line(pony_width);
	std::cout << "| Maksymalne obrażenia: " << p.get_effective_stats().max_damage;
	move_to_the_next_line(pony_width);
	std::cout << "| Szybkość ataku: " << p.get_effective_stats().attack_speed;
	move_to_the_next_line(pony_width);
	std::cout << "| Obrona: " << p.get_effective_stats().armor;
	move_to_the_next_line(pony_width);
	std::cout << "| Regeneracja: " << p.get_effective_stats().health_regeneration;
	move_to_the_next_line(pony_width);
	std::cout << "|";
}

void draw_pony(const Pony& p) {
	int pony_width = -1;
	int pony_height = -1;

	{
		std::string pony = ponysay(p.name);
		std::cout << pony << std::endl;

		pony_width = pony.find('\n');
		pony_height = std::count(pony.begin(), pony.end(), '\n');
	}

	if (pony_width == -1) {
		return;
	}

	move_cursor_up(pony_height);
	draw_stats(p, pony_width);
	move_cursor_to_left_edge();
	move_cursor_down(pony_height - 16);
}
