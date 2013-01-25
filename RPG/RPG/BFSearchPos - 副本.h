//用广度优先算法搜索可走的最近点
//
#pragma once
#include <queue>
#include "stdafx.h"

struct Tile;

struct BSPoint
{
	BSPoint():x(0),y(0){}
	BSPoint(int _x,int _y):x(_x),y(_y){}
    int  x;
    int  y;
};

class CFindBestPos
{
public:
	CFindBestPos(int width, int height);
	~CFindBestPos();

	void FindBestPos(BSPoint v, BSPoint* best, Tile* tiles);


private:
	bool TestPoint( BSPoint testPoint, 
		BSPoint* &best, 
		std::queue<BSPoint>& queue,
		bool* &visited, Tile* tiles);

	std::queue<BSPoint> que;
	bool* visited;
	int col;
	int row;
};