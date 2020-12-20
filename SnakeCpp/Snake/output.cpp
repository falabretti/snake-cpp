#include <iostream>
#include <Windows.h>

#include "output.h"
#include "snake.h"

extern char map[ROWS][COLUMNS];
extern int score;

// https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
void clear_screen(char fill = ' ') {
	COORD tl = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void draw_map() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void draw_score() {
	std::cout << "SCORE: " << score << std::endl;
}

void draw_game_over() {
	clear_screen();
	std::cout << "\nGAME OVER\n";
	std::cout << "Your score: " << score << std::endl;
}