//AStar.h: A*Ѱ·�㷨
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
	int G;	//Gֵ
	int H;	//Hֵ
	int F;	//Hֵ
	char Modified;      // �ýڵ��Ƿ��޸Ĺ�����¼�������1��,2 Open,4 Close
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
		int targetX, int targetY, char* map);//�ҵ�Ŀ��ͷ���

private:
	void ResetAstar();

	bool IsInMap(int x,int y)const //�ж�ָ�������Ƿ�Ϸ�
	{return (x>=0&&x<m_mapWidth) && (y>=0&&y<m_mapHeight);}

	inline void	AddToOpenQueue(AstarNode *node);	//���ڵ��������Open����
	AstarNode*	GetFromOpenQueue();                // ��Open����ȡ����С�Ĳ�����Close����
	void		PointToFather(AstarNode *father);	//���ڵ���Χ�ڵ�ָ�򸸽ڵ�

	inline void JudgeCost(AstarNode *node);   // ȡ�ù���ֵ�ĺ���


	TILE_LIST	m_openList;
	

	AstarNode**	m_map;
	int			m_mapWidth;
	int			m_mapHeight;
	int			m_targetX,m_targetY;
	bool		m_end;
\
};

//x + y*width

