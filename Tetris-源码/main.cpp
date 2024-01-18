#include"Tetris.h"
#include"Block.h"
#include<iostream>
using namespace std;

int main() {
	Tetris game(20, 10, 40, 40, 36);
	game.play();
	return 0;
}