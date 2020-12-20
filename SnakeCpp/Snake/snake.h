#ifndef SNAKE_H
#define SNAKE_H

typedef struct Point {
	int x;
	int y;
};

const char WALL = '#';
const char EMPTY = ' ';
const char SNAKE = 'O';
const char FOOD = '@';

const int ROWS = 30;
const int COLUMNS = 30;

#endif
