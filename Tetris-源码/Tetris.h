
#ifndef TETRIS_H
#define TETRIS_H


#include<graphics.h>
#include<vector>
#include"Block.h"
using namespace std;

class Tetris
{
public:
	Tetris(int rows, int cols, int leftBorder, int topBorder, int blockSize);

	//进程控制
	void init();
	void play();
private:
	//游戏逻辑运行
	void clearLine();//重点 
	void drop();
	void moveLeftRight(int direction);
	void rotate();
	void accountScore(int line);

	//界面绘画
	void updateWindow();//注意 
	void drawScore();

	//进程控制
	void keyEvent();
	int delayTime();//重点
	void gameOver();
	void gameJudge();

private:
	//界面绘制属性
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBack;

	//逻辑控制属性
	int update;
	int delay;
	vector<vector<int>> map;
	Block* curBlock;
	Block* nextBlock;
	Block backupBlock;

	//游戏基本属性
	int rows;
	int cols;
	int score;
	int high_score;
	int level;
	bool gameover;
};

#endif // !TETRIS_H

