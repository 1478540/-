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
	void rotate();//�ص㣬���鷴ת�㷨
	void draw(int leftMargin, int topMargin);
	static IMAGE** getImgs();
	bool blockInmap(const vector<vector<int>>& map);
	void solidify(vector<vector<int>>& map);
	int getBlockType();
private:
	int blockType;
	IMAGE* img;
	static IMAGE* imgs[8];//�洢ÿ�����������Ӧ��ͼƬ
	static int size;
	static int class_count;
	Point blockPosition[4];	//�洢ÿ���󷽿����ĸ�С���������
};

#endif // !BLOCK_H
