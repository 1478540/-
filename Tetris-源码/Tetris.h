
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

	//���̿���
	void init();
	void play();
private:
	//��Ϸ�߼�����
	void clearLine();//�ص� 
	void drop();
	void moveLeftRight(int direction);
	void rotate();
	void accountScore(int line);

	//����滭
	void updateWindow();//ע�� 
	void drawScore();

	//���̿���
	void keyEvent();
	int delayTime();//�ص�
	void gameOver();
	void gameJudge();

private:
	//�����������
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBack;

	//�߼���������
	int update;
	int delay;
	vector<vector<int>> map;
	Block* curBlock;
	Block* nextBlock;
	Block backupBlock;

	//��Ϸ��������
	int rows;
	int cols;
	int score;
	int high_score;
	int level;
	bool gameover;
};

#endif // !TETRIS_H

