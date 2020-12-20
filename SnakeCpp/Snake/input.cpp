#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <unordered_map>

#include "input.h"

extern bool run;

enum class Direction { UP, LEFT, DOWN, RIGHT };
Direction direction = Direction::RIGHT;

std::unordered_map<char, Direction> direction_map = {
	{ 'w', Direction::UP },
	{ 's', Direction::DOWN },
	{ 'a', Direction::LEFT },
	{ 'd', Direction::RIGHT }
};

bool valid_key(char c) {
	return direction_map.find(c) != direction_map.end();
}

void input_handler() {
	while (run) {
		if (_kbhit()) {
			int key = _getch();
			if (valid_key(key)) {
				direction = direction_map.at(key);
			}
		}
	}
}
