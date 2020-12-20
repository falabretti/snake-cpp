#include <iostream>
#include <ctime>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <Windows.h>

#include "snake.h"
#include "input.h"
#include "output.h"

Point snake = { 5, 5 };

std::vector<Point> snake_body;
std::vector<Point> food_queue;

char map[ROWS][COLUMNS];

bool run = true;

int score = 0;

bool is_wall(Point p) {
	return p.x == 0 or p.x == ROWS - 1 or p.y == 0 or p.y == COLUMNS - 1;
}

void build_map() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			map[i][j] = (is_wall({ i, j }) ? WALL : EMPTY);
		}
	}
}

void set_position(char element, Point p) {
	map[p.x][p.y] = element;
}

Point random_point() {

	srand(time(NULL));
	int x = rand() % (ROWS - 2) + 1;
	int y = rand() % (COLUMNS - 2) + 1;

	return { x, y };
}

Point new_food() {

	Point p = random_point();

	while (map[p.x][p.y] == SNAKE) {
		p = random_point();
	}

	return p;
}

void spawn_food() {

	Point food = new_food();
	set_position(FOOD, food);
}

Point teleport(Point wall) {

	Point p;

	if (wall.x == 0) {
		p = { COLUMNS - 2, wall.y };
	}
	else if (wall.x == COLUMNS - 1) {
		p = { 1, wall.y };
	}
	else if (wall.y == 0) {
		p = { wall.x, ROWS - 2 };
	}
	else if (wall.y == ROWS - 1) {
		p = { wall.x, 1 };
	}

	return p;
}

bool is_food(Point p) {
	return map[p.x][p.y] == FOOD;
}

void set_snake() {

	for (Point p : snake_body) {
		map[p.x][p.y] = SNAKE;
	}
}

bool next_food = false;

void clear_map() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (not is_wall({ i, j }) and map[i][j] != FOOD) {
				map[i][j] = EMPTY;
			}
		}
	}
}

void update_body() {

	Point tail = snake_body.at(snake_body.size() - 1);
	Point first_food = food_queue.at(0);

	if (next_food) {
		snake_body.push_back({ first_food.x, first_food.y });
		food_queue.erase(food_queue.begin());
		next_food = false;
	}

	if (first_food.x == tail.x and first_food.y == tail.y) {
		next_food = true;
	}
}

bool is_snake(Point p) {
	return map[p.x][p.y] == SNAKE;
}

Point next[] = {
	{ -1, 0 },
	{ 0, -1 },
	{ 1, 0 },
	{ 0, 1 }
};

void move() {

	Point prev_pos = snake;
	Point new_pos;

	new_pos = { snake.x + next[(int)direction].x, snake.y + next[(int)direction].y };

	if (is_snake(new_pos)) {
		run = false;
	}

	if (is_wall(new_pos)) {
		new_pos = teleport(new_pos);
	}

	if (is_food(new_pos)) {
		score += 10;
		spawn_food();
		food_queue.push_back(new_pos);
	}

	snake = new_pos;
	snake_body.insert(snake_body.begin(), snake);
	snake_body.pop_back();
	clear_map();
	if (food_queue.size()) {
		update_body();
	}
	set_snake();
}

int main() {

	std::thread input_handle(input_handler);

	build_map();
	snake_body.push_back(snake);

	set_position(SNAKE, snake);
	spawn_food();

	while (run) {
		using namespace std::literals::chrono_literals;

		move();
		draw_map();
		draw_score();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });

		std::this_thread::sleep_for(33ms);
	}

	input_handle.join();
	draw_game_over();
	
	return 0;
}
