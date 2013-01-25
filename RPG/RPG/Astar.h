//AStar.h: A*寻路算法
//
#pragma once

#include <vector>

#include "stdafx.h"
#include "Map.h"


enum NodeState
{
	EMPTY = 1,
	INOPEN = 2,
	INCLOSE = 4
};


struct AstarNode
{
	AstarNode():passable(true),G(0),H(0),parent(0),Modified(1){}
	bool passable;
	int G;	//G值
	int H;	//H值
	int F;	//H值
	char Modified;      // 该节点是否被修改过，记录而备清除1空,2 Open,4 Close
	int posx;
	int posy;
	AstarNode* parent;
	inline void computeF(){F=G+H;}
};

typedef std::vector<AstarNode*>				TILE_LIST;
typedef std::vector<AstarNode*>::iterator	TILE_ITR;


class CAstar
{
public:
	CAstar(int width, int height);
	~CAstar();

public:
	bool Init(CMap*);

	AstarNode* FindPath(int startingX, int startingY,
		int targetX, int targetY, char* map);//找到目标头结点

private:
	void ResetAstar();

	bool IsInMap(int x,int y)const //判断指定格子是否合法
	{return (x>=0&&x<m_mapWidth) && (y>=0&&y<m_mapHeight);}

	inline void	AddToOpenQueue(AstarNode *node);	//将节点排序加入Open队列
	AstarNode*	GetFromOpenQueue();                // 从Open队列取出最小的并放入Close队列
	void		PointToFather(AstarNode *father);	//父节点周围节点指向父节点

	inline void JudgeCost(AstarNode *node);   // 取得估计值的函数


	TILE_LIST	m_openList;
	

	AstarNode**	m_map;
	int			m_mapWidth;
	int			m_mapHeight;
	int			m_targetX,m_targetY;
	bool		m_end;
\
};

//x + y*width

