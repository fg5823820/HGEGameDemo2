#pragma once
#include "MoveableObj.h"
#include "Map.h"
#include "Astar.h"
#include "BFSearchPos.h"
#include <deque>

typedef std::deque<Pos>	DEQUE;

class CRole : public CMoveableObj
{
public:
	CRole(hgeResourceManager*, char* name, CMap* map, float spd = 200.f);
	virtual~CRole(){}

	virtual bool Init();
	virtual void Update(float);
	virtual void Render();
	virtual void Cleanup();

	void SetDst(Pos);

	inline bool IsMoving()const			{return m_bMoving;}
	inline void SetPos(float x,float y) {m_pos.x = x;m_pos.y = y;m_fdst = m_dst = m_pos;}
	inline void SetStop()				{m_dst = m_pos;}
	inline Pos	GetPos()const			{return  m_pos;}

	enum Dir{ UP, DOWN, LEFT, RIGHT };

protected:
	bool GetNextPos(Pos*,float offsetx, float offsety);
	bool FindPath(Pos* start, Pos* target);
	void ClearPath(){m_pathList.clear();}

	void Stop(){m_pAni[m_dir]->Stop();
	m_pAni[m_dir]->SetFrame(0);m_bMoving = false;m_dst = m_pos;}

	void ComputeDir();
	bool CollideMap();
	void ChangeMap(hgeRect*);
	void ResetMap(hgeRect*);
	bool IsInMap(int x,int y)const {return (x>=0&&x<m_pMap->m_col) && (y>=0&&y<m_pMap->m_row);}

	
	CMap*			m_pMap;
	hgeAnimation*	m_pAni[4];
	int				m_dir,m_oldDir;
	int				m_mapPosX,m_mapPosY;
	Pos				m_oldPos;
	Pos				m_fdst;//绝对终点
	bool			m_bBeginFindPath;
	bool			m_bSwt;
	char*			m_mapTile;
	
	hgeRect			m_oldRect;
	DEQUE			m_pathList;


	static CFindBestPos*	m_bestPosFinder;
	static CAstar*			m_pathFinder;

	//地图信息保存
	int x1,y1, x2,y2, x3,y3, x4,y4;
	bool point1,point2,point3,point4;
	

};