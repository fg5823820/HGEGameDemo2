//�ù�������㷨�������ߵ������
//
#pragma once
#include <queue>
#include "stdafx.h"

class CFindBestPos
{
public:
	CFindBestPos(int width, int height);
	~CFindBestPos();

	void FindBestPos(int x,int y, int *bestx, int *besty, char *tiles);

private:

	bool TestPoint( int x, int y, int* &bestx, int* &besty, char* tiles);

	bool**			m_visited;
	int				m_col;
	int				m_row;
	std::queue<long> m_que;
};