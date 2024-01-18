#include "Block.h"
#include<stdlib.h>

int blocks[7][4] = {
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,4,5,7,
	2,3,5,7,
	3,5,6,7,
	2,3,4,5
};

IMAGE* Block::imgs[8] = { NULL, };
int Block::size = 36;
int Block::class_count = 0;

Block::Block()
{
	if (Block::imgs[0] == NULL) {
		IMAGE imgTemp;
		loadimage(&imgTemp, "picture/Tetris.png", 288, 36, true);//拉升图片以调整到合适大小

		SetWorkingImage(&imgTemp);
		for (int i = 0; i < 8; i++) {
			Block::imgs[i] = new IMAGE;//还要在析构函数里删除空间
			getimage(imgs[i], i * 36, 0, 36, 36);
		}
		SetWorkingImage();
	}

	blockType = rand() % 7+1;
	for (int i = 0; i < 4; i++) {
		int value = blocks[blockType-1][i];
		blockPosition[i].row = value / 2;
		blockPosition[i].col = value % 2;
	}
	img = Block::imgs[blockType-1];
	Block::class_count++;
}

Block::~Block()
{
	Block::class_count--;
	if (Block::class_count == 0) {
		delete[]Block::imgs;
	}
}



void Block::drop()
{
	for (int i = 0; i < 4; i++) {
		blockPosition[i].row++;
	}
}

void Block::move_left_right(int direction)
{
	for (int i = 0; i < 4; i++) {
		blockPosition[i].col+=direction;
	}
}

void Block::rotate()
{
	Point p = blockPosition[1];

	for (int i = 0; i < 4; i++) {
		Point temp = blockPosition[i];
		blockPosition[i].col = p.col - temp.row + p.row;
		blockPosition[i].row = p.row + temp.col - p.col;
	}
}

void Block::draw(int leftMargin, int topMargin)
{
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + blockPosition[i].col * Block::size;
		int y = topMargin + blockPosition[i].row * Block::size;
		putimage(x, y, img);
	}
}

IMAGE** Block::getImgs()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this != &other) {
		this->blockType = other.blockType;
		this->img = Block::imgs[blockType-1];//自己加的
		for (int i = 0; i < 4; i++) {
			this->blockPosition[i] = other.blockPosition[i];
		}
	}
	return *this;
}

bool Block::blockInmap(const vector<vector<int>>& map)
{
	int x = map.size();
	int y = map[0].size();
	for (int i = 0; i < 4; i++) {
		if (blockPosition[i].col < 0 || blockPosition[i].col >= y ||
			blockPosition[i].row < 0 || blockPosition[i].row >= x ||
			map[blockPosition[i].row][blockPosition[i].col] != 0)
			return false;
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++) {
		map[blockPosition[i].row][blockPosition[i].col] = blockType;
	}
}

int Block::getBlockType()
{
	return blockType;
}
