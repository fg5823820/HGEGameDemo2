#include "Role.h"
#include "Utilities.h"
#include <string>
#define INDEX(x,y)		(x)+(y)*m_pMap->m_col //一维数组变下标转二维数字下标

CFindBestPos*	CRole::m_bestPosFinder	= 0;
CAstar*			CRole::m_pathFinder		= 0;

CRole::CRole(hgeResourceManager * rs, char* name, CMap* map, float spd):
CMoveableObj(rs),
m_dir(DOWN),
m_oldDir(DOWN),
m_pMap(map),
m_mapPosX(0),
m_mapPosY(0),
m_bBeginFindPath(0),
m_mapTile(0),
m_bSwt(false)
{
	m_name = name;
	m_oldPos = m_pos;
	m_speed = spd;
	m_mapTile = map->m_dynamicMap;
	ZeroMemory(m_pAni, sizeof(m_pAni));
	x1=y1= x2=y2= x3=y3= x4=y4 = -1;
	point1=point2=point3=point4 = false;
}

bool CRole::Init()
{
	std::string s(m_name);
	std::string up(".up");
	std::string down(".down");
	std::string right(".right");
	std::string left(".left");

	m_pAni[UP] = new hgeAnimation(*m_pRs->GetAnimation((s+up).c_str()));
	m_pAni[DOWN] = new hgeAnimation(*m_pRs->GetAnimation((s+down).c_str()));
	m_pAni[LEFT] = new hgeAnimation(*m_pRs->GetAnimation((s+left).c_str()));
	m_pAni[RIGHT] = new hgeAnimation(*m_pRs->GetAnimation((s+right).c_str()));
	for(int i = 0;i < 4; i ++)
		if(!m_pAni[i]) return false;

	if(!m_bestPosFinder)
		m_bestPosFinder = new CFindBestPos(m_pMap->m_col, m_pMap->m_row);

	if(!m_pathFinder)
	{
		m_pathFinder = new CAstar(m_pMap->m_col, m_pMap->m_row);
		m_pathFinder->Init(m_pMap);
	}

	
	return true;
}

void CRole::Cleanup()
{
	Delete(m_bestPosFinder);
	Delete(m_pathFinder);
	
	for(int i = 0;i < 4;i ++)
	{
		Delete(m_pAni[i]);
	}
}

void CRole::Update(float dt)
{

	m_oldPos = m_pos;
	CMoveableObj::Update(dt);

	/*
	m_mapPosX = (int)(m_pos.x/m_pMap->m_tileWidth);
	m_mapPosY = (int)(m_pos.y/m_pMap->m_tileHeight);
	if(m_mapPosX < 0 || m_mapPosY < 0 || 
		m_pos.x < 0 || m_pos.y < 0 ||
		m_mapPosX >= m_pMap->m_col || m_mapPosY >= m_pMap->m_row) 
	{//阻止角色离开地图
		m_pos = m_oldPos;
		SetStop();
	}

	if(m_pos==m_dst)
	{
		if(m_bSwt)
		{
			m_dst = m_fdst;
			ComputeDir();
			m_bSwt = false;
		}
		else if(m_bBeginFindPath)
		{
			Pos next;
			if(GetNextPos(&next, 
				(float)m_pMap->m_tileWidth/2, (float)m_pMap->m_tileHeight/2))
			{
				m_dst = next;
				if(next.x != m_pos.x && next.y != m_pos.y)//转折点
				{
					ComputeDir();
					m_bBeginFindPath = false;
					m_bSwt = true;//打开转折开关
					ClearPath();
				}

			}else
			{
				Stop();
				m_bBeginFindPath = false;
			}
		}else
		{
			Stop();
			m_bBeginFindPath = false;
		}
	}
	else
	{
		if(!m_pAni[m_dir]->IsPlaying())
		{
			m_pAni[m_dir]->Play();
			m_pAni[m_dir]->SetFrame(1);
		}
		m_bMoving = true;
	}

	if(CollideMap() && !m_bBeginFindPath && m_bMoving && !m_bSwt)
	{
		m_bBeginFindPath = true;
		//m_bSwt = false;
		m_pos = m_oldPos;

		int t=timeGetTime(); //计算寻路时间
		FindPath(&m_pos, &m_fdst);
		printf("寻路消耗时间: %d\n",timeGetTime()-t); //
		if(GetNextPos(&m_dst, (float)m_pMap->m_tileWidth/2, (float)m_pMap->m_tileHeight/2))
			ComputeDir();
		else
		{
			m_bBeginFindPath = false;
			SetStop();
		}
	}*/


	//test
	if(m_pos==m_dst)
	{
		if(GetNextPos(&m_dst, 
			(float)m_pMap->m_tileWidth/2, (float)m_pMap->m_tileHeight/2))
		{
			ComputeDir();
		}else
		{
			Stop();
			m_bBeginFindPath = false;
		}

	}
	else
	{
		if(!m_pAni[m_dir]->IsPlaying())
		{
			m_pAni[m_dir]->Play();
			m_pAni[m_dir]->SetFrame(1);
		}
		m_bMoving = true;
	}


	m_rect.x1 = m_pos.x - m_pMap->m_tileWidth/2.f +1;
	m_rect.y1 = m_pos.y - m_pMap->m_tileHeight/2.f +1;
	m_rect.x2 = m_pos.x + m_pMap->m_tileWidth/2.f-1;
	m_rect.y2 = m_pos.y + m_pMap->m_tileHeight/2.f -1;

	x1 = (int)(m_rect.x1/m_pMap->m_tileWidth);
	y1 = (int)(m_rect.y1/m_pMap->m_tileHeight);
	x2 = (int)(m_rect.x2/m_pMap->m_tileWidth);
	y2 = (int)(m_rect.y1/m_pMap->m_tileHeight);
	x3 = (int)(m_rect.x1/m_pMap->m_tileWidth);
	y3 = (int)(m_rect.y2/m_pMap->m_tileHeight);
	x4 = (int)(m_rect.x2/m_pMap->m_tileWidth);
	y4 = (int)(m_rect.y2/m_pMap->m_tileHeight);

	if(IsInMap(x1,y1))
		m_mapTile[INDEX(x1,y1)] = false;
	if(IsInMap(x2,y2))
		m_mapTile[INDEX(x2,y2)] = false;
	if(IsInMap(x3,y3))
		m_mapTile[INDEX(x3,y3)] = false;
	if(IsInMap(x4,y4))
		m_mapTile[INDEX(x4,y4)] = false;


	for(MOBJ_ITR itr = m_mobjs->begin(); itr != m_mobjs->end();itr ++)
	{
		hgeRect* rct = (*itr)->GetRect();
		if(m_rect.Intersect(rct))
		{
			if((*itr)->GetID() != m_uID)
			{
				//m_pos = m_oldPos;
				//Stop();
				//x1 = (int)(m_rect.x1/m_pMap->m_tileWidth);
				//y1 = (int)(m_rect.y1/m_pMap->m_tileHeight);
				//x2 = (int)(m_rect.x2/m_pMap->m_tileWidth);
				//y2 = (int)(m_rect.y1/m_pMap->m_tileHeight);
				//x3 = (int)(m_rect.x1/m_pMap->m_tileWidth);
				//y3 = (int)(m_rect.y2/m_pMap->m_tileHeight);
				//x4 = (int)(m_rect.x2/m_pMap->m_tileWidth);
				//y4 = (int)(m_rect.y2/m_pMap->m_tileHeight);
				//if(IsInMap(x1,y1))
				//	point1 = m_mapTile[INDEX(x1,y1)];
				//if(IsInMap(x2,y2))
				//	point2 = m_mapTile[INDEX(x2,y2)];
				//if(IsInMap(x3,y3))
				//	point3 = m_mapTile[INDEX(x3,y3)];
				//if(IsInMap(x4,y4))
				//	point4 = m_mapTile[INDEX(x4,y4)];

				//if(IsInMap(x1,y1))
				//	m_mapTile[INDEX(x1,y1)] = false;
				//if(IsInMap(x2,y2))
				//	m_mapTile[INDEX(x2,y2)] = false;
				//if(IsInMap(x3,y3))
				//	m_mapTile[INDEX(x3,y3)] = false;
				//if(IsInMap(x4,y4))
				//	m_mapTile[INDEX(x4,y4)] = false;
				//
				////m_bBeginFindPath = true;

				FindPath(&m_pos, &m_fdst);

				if(GetNextPos(&m_dst, (float)m_pMap->m_tileWidth/2, (float)m_pMap->m_tileHeight/2))
					ComputeDir();
				else
				{
					//m_bBeginFindPath = false;
					SetStop();
				}

				//if(IsInMap(x1,y1))
				//	m_mapTile[INDEX(x1,y1)] = point1;
				//if(IsInMap(x2,y2))
				//	m_mapTile[INDEX(x2,y2)] = point2;
				//if(IsInMap(x3,y3))
				//	m_mapTile[INDEX(x3,y3)] = point3;
				//if(IsInMap(x4,y4))
				//	m_mapTile[INDEX(x4,y4)] = point4;
				//

				break;
			}
			
		}
	}

	m_pAni[m_dir]->Update(dt);

}
void CRole::Render()
{
	//m_pAni[m_dir]->Render(m_pos.x, m_pos.y);
	if(!(m_pos==m_dst))
	m_pRs->GetSprite("Dst")->Render(m_fdst.x, m_fdst.y);
	m_pAni[m_dir]->Render(floor(m_pos.x), floor(m_pos.y));
	for(DEQUE::iterator itr = m_pathList.begin();itr != m_pathList.end();itr ++)
	{
		if(itr+1 != m_pathList.end())
		{
			Pos begin = *itr;
			Pos end = *(itr+1);
			m_pHge->Gfx_RenderLine(begin.x, begin.y,
				end.x,end.y);
		}
	}
	

}

void CRole::ComputeDir()
{
	Pos tmp,tmp2;
	tmp2.x = m_dst.x - m_pos.x;
	tmp2.y = m_dst.y - m_pos.y;
	Rotate(&tmp2, &tmp, -M_PI_4);
	if(tmp.x>=0 && tmp.y>0)  
	{
		m_oldDir = m_dir = RIGHT;
		return;
	}
	if(tmp.x>=0 && tmp.y<=0)
	{
		m_oldDir = m_dir = UP;
		return;
	}
	if(tmp.x<0 && tmp.y>0)   
	{
		m_oldDir = m_dir = DOWN;
		return;
	}
	if(tmp.x<0 && tmp.y<=0) 
	{
		m_oldDir = m_dir = LEFT;
		return;
	}
	m_dir =	DOWN;
}

void CRole::SetDst(Pos pos)
{
	m_bBeginFindPath = false;
	m_fdst = m_dst = pos;
	ComputeDir();

	int x = (int)(m_fdst.x/m_pMap->m_tileWidth);
	int y = (int)(m_fdst.y/m_pMap->m_tileHeight);

	if(!m_pMap->Passable(x, y))//如果目标不可到达
	{
		int bestx;int besty;
		m_bestPosFinder->FindBestPos(x, y, &bestx, &besty, m_pMap->m_map);//寻找最近可走点
		m_fdst.x = (float)bestx*m_pMap->m_tileWidth;
		m_fdst.y = (float)besty*m_pMap->m_tileHeight;
		//printf("%d %d\n", bestx, besty);
	}
	ClearPath();
	//int t=timeGetTime(); //计算寻路时间
	FindPath(&m_pos, &m_fdst);
	//printf("寻路消耗时间: %d\n",timeGetTime()-t); //
	if(GetNextPos(&m_dst, 
			(float)m_pMap->m_tileWidth/2, (float)m_pMap->m_tileHeight/2))
	ComputeDir();
	else
		SetStop();
}

bool CRole::CollideMap()
{
	//m_rect.x1 = m_pos.x - m_pMap->m_tileWidth/2.f + 1;
	//m_rect.y1 = m_pos.y - m_pMap->m_tileHeight/2.f + 1;
	//m_rect.x2 = m_pos.x + m_pMap->m_tileWidth/2.f - 1;
	//m_rect.y2 = m_pos.y + m_pMap->m_tileHeight/2.f - 1;

	if(!m_pMap->Passable((int)(m_rect.x1/m_pMap->m_tileWidth),
		(int)(m_rect.y1/m_pMap->m_tileHeight)))return true;
	if(!m_pMap->Passable((int)(m_rect.x2/m_pMap->m_tileWidth),
		(int)(m_rect.y1/m_pMap->m_tileHeight)))return true;
	if(!m_pMap->Passable((int)(m_rect.x1/m_pMap->m_tileWidth),
		(int)(m_rect.y2/m_pMap->m_tileHeight)))return true;
	if(!m_pMap->Passable((int)(m_rect.x2/m_pMap->m_tileWidth),
		(int)(m_rect.y2/m_pMap->m_tileHeight)))return true;
	return false;
}

 //获取下一个位置
bool  CRole::GetNextPos(Pos* out,float x, float y)
{
	if(m_pathList.empty())return false;
	Pos pos = m_pathList.back();
	out->x = pos.x + x;out->y = pos.y + y;
	m_pathList.pop_back();
	return true;
}

//按需定义函数 开始寻路
bool CRole::FindPath(Pos* start, Pos* target)
{
	AstarNode* node = NULL;
	node = m_pathFinder->FindPath((int)(start->x/m_pMap->m_tileWidth), (int)(start->y/m_pMap->m_tileHeight), 
		(int)(target->x/m_pMap->m_tileWidth), (int)(target->y/m_pMap->m_tileHeight), m_mapTile);//坐标转换
	if(!node) return false;

	m_pathList.clear();


	for(;node->parent != NULL;node = node->parent)
	{
			m_pathList.push_back(
				Pos(
				(float)node->posx*m_pMap->m_tileWidth, (float)node->posy*m_pMap->m_tileHeight)
				);
		
	}
	return true;
}
