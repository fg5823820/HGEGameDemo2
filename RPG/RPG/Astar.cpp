#include <algorithm>
#include "Astar.h"
#include <deque>

using namespace std;




template<class T>
bool Make2DArrayCPP(int row, int col, T ** &_2DArray)
{
	if((_2DArray = new T*[row])==NULL) return false;
	for(int i = 0;i < row;i ++)
		if((_2DArray[i] = new T[col])==NULL) return false;
	return true;
}

template<class T>
void Diliver2DArrayCPP(T** _2DArray, int row)
{
	for(int i = 0;i < row; i ++)
		delete[] _2DArray[i];
	delete[] _2DArray;
}

//比较函数
bool compare(AstarNode* lhs,AstarNode* rhs)
{
	return lhs->F < rhs->F;
}

//构造函数
//w 地图逻辑宽度
//h 地图逻辑高度
CAstar::CAstar(int w, int h):
m_mapWidth(w),
m_mapHeight(h),
m_map(0),
m_targetX(0),
m_targetY(0),
m_end(false)
{
	//m_map = new AstarNode[m_mapWidth*m_mapHeight];
	//ZeroMemory(m_map, sizeof(m_map));
	Make2DArrayCPP(m_mapHeight, m_mapWidth, m_map);
	for (int j=0;j<m_mapHeight;j++) 
	{
		for (int i=0;i<m_mapWidth;i++) 
		{
			m_map[j][i].posx = i;
			m_map[j][i].posy = j;
		}
	}
	m_openList.reserve(sizeof(AstarNode*)*m_mapWidth*m_mapHeight);
}

CAstar::~CAstar()
{
	m_openList.clear();
	Diliver2DArrayCPP(m_map, m_mapHeight);
}

bool CAstar::Init(CMap* map)
{
	if(!map)return false;
	char* tileMap = map->m_map;
	for (int j=0;j<m_mapHeight;j++) 
	{
		for (int i=0;i<m_mapWidth;i++) 
		{
			m_map[j][i].passable = tileMap[j*m_mapWidth+i]? true : false;
		}
	}
	return true;
}

//寻路主函数
//返回值：找到返回目标节点指针，找不到返回NULL
AstarNode* CAstar::FindPath(int startingX, int startingY,
			  int targetX, int targetY, char* map)
{
	if(!IsInMap(targetX, targetY) || !IsInMap(startingX, startingY))return NULL;
	if((startingX == targetX) && (startingY == targetY))return NULL;

	for (int j=0;j<m_mapHeight;j++) 
	{
		for (int i=0;i<m_mapWidth;i++) 
		{
			m_map[j][i].passable = map[j*m_mapWidth+i]? true : false;
		}
	}

	ResetAstar();

	m_targetX = targetX;
	m_targetY = targetY;

	AstarNode* root = &m_map[startingY][startingX];
	AddToOpenQueue(root);// 从起点开始，并把它就加入到一个由方格组成的 open list中
	GetFromOpenQueue();  // A 从 open list 中移除,加入到 close list 中

	PointToFather(root);//起点 A 设置为周围方格的父亲
	
	do
	{
		root = GetFromOpenQueue();// open list 中选择 F 值最小的 ( 方格 ) 节点,放到 close list 中
		if(root)
			PointToFather(root);
		else
			return NULL;
		if(m_end)
			return &m_map[targetY][targetX];

	}while(1);

	return NULL;

}

//参数为父节点，周围符合条件的节点指向父节点
void CAstar::PointToFather(AstarNode *father)
{
	int x,y;
	int tmpG;
	x = father->posx;
	y = father->posy;
	AstarNode* tmp;
	if(IsInMap(x,y-1))//上
	{
		tmp = &m_map[y-1][x];
		if(tmp->passable && tmp->Modified != INCLOSE)//忽略其中在 close list 中或是不可走 (unwalkable) 的方格
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G =10 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x,y+1))//下
	{
		tmp = &m_map[y+1][x];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G =10 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x-1,y))//左
	{
		tmp = &m_map[y][x-1];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G =10 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x+1,y))//右
	{
		tmp = &m_map[y][x+1];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G =10 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x-1,y-1))//左上
	{
		tmp = &m_map[y-1][x-1];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G = 14 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x-1,y+1))//左下
	{
		tmp = &m_map[y+1][x-1];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G = 14 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x+1,y-1))//右上
	{
		tmp = &m_map[y-1][x+1];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G = 14 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x+1,y+1))//右下
	{
		tmp = &m_map[y+1][x+1];
		if(tmp->passable && tmp->Modified != INCLOSE)//可通行，不在CLOSE
		{
			
			JudgeCost(tmp);//设置H
			if(tmp->Modified != INOPEN)//如果方格不在 open 中，则把它们加入到 open 中
			{
				tmp->G = 14 + father->G;//设置G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//如果已经在 open list 中，则检查这条路径是否更优
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //如果 G 值更小
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}

}

//将节点排序加入Open队列
inline void CAstar::AddToOpenQueue(AstarNode *node)
{
	node->Modified = INOPEN;
	m_openList.push_back(node);
}

 // 从Open队列取出最小的并放入Close队列
AstarNode* CAstar::GetFromOpenQueue()
{
	AstarNode* node = NULL;
	if(m_openList.empty())
	{
		return NULL;
	}
	else
	{
		TILE_ITR minNode = min_element(m_openList.begin(),m_openList.end(),compare);
		node = *minNode;
		m_openList.erase(minNode);
		node->Modified = INCLOSE;
		if(node->posx == m_targetX && node->posy == m_targetY)
			m_end = true;
	}
	return node;
}

// 取得估计值的函数指针
inline void CAstar::JudgeCost(AstarNode *node)
{
	node->H = 10*(abs(node->posx - m_targetX) + abs(node->posy - m_targetY));
}

void CAstar::ResetAstar()
{
	for (int j=0;j<m_mapHeight;j++) 
	{
		for (int i=0;i<m_mapWidth;i++) 
		{
			m_map[j][i].Modified = EMPTY;
			m_map[j][i].G = 0;
			m_map[j][i].H = 0;
			m_map[j][i].parent = 0;
		}
	}
	m_openList.clear();
	m_end = false;
}