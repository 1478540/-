#include "Tetris.h"
#include<time.h>
#include<stdlib.h>
#include<vector>
#include"Block.h"
#include<conio.h>
#include<fstream>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

int speed[5] = { 500,400,300,200,50 };

Tetris::Tetris(int rows, int cols, int leftBorder, int topBorder, int blockSize)
{
	this->cols = cols;
	this->rows = rows;
	this->leftMargin = leftBorder;
	this->topMargin = topBorder;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++) {
		vector<int> mapRow;
		for (int j = 0; j < cols; j++) {
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{
	gameover = false;
	level = 0;
	update = true;
	score = 0;
	delay = speed[0];
	srand(time(NULL));

	initgraph(615, 775);
	loadimage(&imgBack, "picture/back.png", 615, 775, true);

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			map[i][j] = 0;
		}
	}

	fstream file("picture/recoder.txt");
	if (!file.is_open()) {
		high_score = 0;
	}
	else {
		file >> high_score;
	}
	file.close();
}

void Tetris::play()
{
	init();
	int timer = 0;

	nextBlock = new Block;//需要delete
	curBlock = nextBlock;
	nextBlock = new Block;

	while (1) {
		keyEvent();
		timer += delayTime();
		if (timer > delay) {
			timer = 0;
			drop();
			update = true;
		}
		if (update) {
			update = false;
			clearLine();
			updateWindow();
		}
		gameOver();
	}
}

void Tetris::keyEvent()
{
	unsigned char ch;
	int rotateFlag = false;
	int direction = 0;
	if (_kbhit()) {//判断是否有键盘输出
		ch = _getch();
		switch (ch) {
			case 'w':
				rotateFlag = true;
				break;
			case 's':
				delay = speed[4];
				break;
			case 'a':
				direction = -1;
				break;
			case 'd':
				direction = 1;
				break;
			case 'e':
				gameover = true;
				break;
			default:
				break;
		}
		update = true;
	}
	if (rotateFlag) {
		rotateFlag = false;
		rotate();
	}
	if (direction != 0) {
		moveLeftRight(direction);
		direction = 0;
	}
}

int Tetris::delayTime()
{
	static unsigned long long last_time = 0;
	unsigned long long current_time = GetTickCount();

	if (last_time == 0) {
		last_time = current_time;
		return 0;
	}
	else {
		int ret = current_time - last_time;
		last_time = current_time;
		return ret;
	}
	return 0;
}
//利用 静态变量 和 计数器GetTickCount()，来返回当前时间到上一次调用该函数时间的插值

void Tetris::updateWindow()
{

	putimage(0, 0, &imgBack);
	BeginBatchDraw();
	IMAGE** pic;
	pic = Block::getImgs();

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] == 0) 
				continue;
			else {
				int x = leftMargin + j * blockSize;
				int y = topMargin + i * blockSize;
				putimage(x, y, pic[map[i][j]-1]);
			}
		}
	}
	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(478, topMargin);
	drawScore();
	EndBatchDraw();
}
//BeginBatchDraw和EndBatchDraw来实现将一部分内容一起绘画出来
//刷新界面时注意图片覆盖问题，不要让背景图后刷新覆盖掉前面图片

void Tetris::clearLine()
{
	int line = 0;
	int k = rows - 1;
	for (int i = rows - 1; i >= 0; i--) {
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j] != 0) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < cols) {
			k--;
		}
		else {
			line++;
		}
	}
	if (line > 0) {
		accountScore(line);
		mciSendString("play picture/xiaochu1.mp3", NULL, 0, NULL);
	}
}
//利用两个游标同时从数组底下向上一边搜索一边复制来达成俄罗斯方块消行效果
//非常巧妙的算法，省时间有省空间
//要意识到，俄罗斯方块游戏中，要被消除的行实际上应该执行对上面尚未被消除行的复制操作


void Tetris::drop()
{
	backupBlock = *curBlock;
	curBlock->drop();

	if (!curBlock->blockInmap(map)) {
		backupBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
		gameJudge();
	}
	delay = speed[level];
}

void Tetris::moveLeftRight(int direction)
{
	backupBlock = *curBlock;
	curBlock->move_left_right(direction);
	if (!curBlock->blockInmap(map)) {
		*curBlock = backupBlock;
	}
}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7) return;

	backupBlock = *curBlock;
	curBlock->rotate();
	if (!curBlock->blockInmap(map)) {
		*curBlock = backupBlock;
	}
}

void Tetris::accountScore(int line)
{
	int Score[9] = { 10,30,50,80,100,120,140,150,200 };
	score += Score[line-1];
	level = score / 50;
	if (level >= 5) {
		level = 4;
	}
	delay = speed[level];
}

void Tetris::drawScore()
{
	char scoreText[36];
	sprintf_s(scoreText, sizeof(scoreText), "SCORE:%d", score);
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWeight = 20;
	settextstyle(&f);
	outtextxy(440, 500, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "HIGHEST:%d", high_score);
	outtextxy(400, 600, scoreText);

}

void Tetris::gameOver()
{
	if (gameover == true) {
		if (score > high_score){
			high_score = score;
			ofstream file("picture/recoder.txt", ios_base::out);
			if (file.is_open())
			{
				file << high_score;
			}
			file.close();
		}
		
		if (curBlock != NULL)
			delete curBlock;
		if (nextBlock != NULL)
			delete nextBlock;
		exit(0);
	}
		
}

void Tetris::gameJudge()
{
	if (curBlock->blockInmap(map) == false)
	{
		gameover = true;
	}
}

