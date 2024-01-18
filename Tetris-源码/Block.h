#ifndef BLOCK_H
#define BLOCK_H

#include<graphics.h>
#include<vector>
#include<memory>
using namespace std;

struct Point {
	int row;
	int col;
};

class Block
{
public:
	Block();
	~Block();

	Block& operator=(const Block& other);
	void drop();
	void move_left_right(int direction);
	void rotate();//重点，方块反转算法
	void draw(int leftMargin, int topMargin);
	static IMAGE** getImgs();
	bool blockInmap(const vector<vector<int>>& map);
	void solidify(vector<vector<int>>& map);
	int getBlockType();
private:
	int blockType;
	IMAGE* img;
	static IMAGE* imgs[8];//存储每个方块种类对应的图片
	static int size;
	static int class_count;
	Point blockPosition[4];	//存储每个大方块中四个小方块的坐标
};

#endif // !BLOCK_H
