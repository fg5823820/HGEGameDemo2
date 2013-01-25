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

//�ȽϺ���
bool compare(AstarNode* lhs,AstarNode* rhs)
{
	return lhs->F < rhs->F;
}

//���캯��
//w ��ͼ�߼����
//h ��ͼ�߼��߶�
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

//Ѱ·������
//����ֵ���ҵ�����Ŀ��ڵ�ָ�룬�Ҳ�������NULL
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
	AddToOpenQueue(root);// ����㿪ʼ���������ͼ��뵽һ���ɷ�����ɵ� open list��
	GetFromOpenQueue();  // A �� open list ���Ƴ�,���뵽 close list ��

	PointToFather(root);//��� A ����Ϊ��Χ����ĸ���
	
	do
	{
		root = GetFromOpenQueue();// open list ��ѡ�� F ֵ��С�� ( ���� ) �ڵ�,�ŵ� close list ��
		if(root)
			PointToFather(root);
		else
			return NULL;
		if(m_end)
			return &m_map[targetY][targetX];

	}while(1);

	return NULL;

}

//����Ϊ���ڵ㣬��Χ���������Ľڵ�ָ�򸸽ڵ�
void CAstar::PointToFather(AstarNode *father)
{
	int x,y;
	int tmpG;
	x = father->posx;
	y = father->posy;
	AstarNode* tmp;
	if(IsInMap(x,y-1))//��
	{
		tmp = &m_map[y-1][x];
		if(tmp->passable && tmp->Modified != INCLOSE)//���������� close list �л��ǲ����� (unwalkable) �ķ���
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G =10 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x,y+1))//��
	{
		tmp = &m_map[y+1][x];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G =10 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x-1,y))//��
	{
		tmp = &m_map[y][x-1];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G =10 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x+1,y))//��
	{
		tmp = &m_map[y][x+1];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G =10 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G +10;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x-1,y-1))//����
	{
		tmp = &m_map[y-1][x-1];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G = 14 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x-1,y+1))//����
	{
		tmp = &m_map[y+1][x-1];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G = 14 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x+1,y-1))//����
	{
		tmp = &m_map[y-1][x+1];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G = 14 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}
	if(IsInMap(x+1,y+1))//����
	{
		tmp = &m_map[y+1][x+1];
		if(tmp->passable && tmp->Modified != INCLOSE)//��ͨ�У�����CLOSE
		{
			
			JudgeCost(tmp);//����H
			if(tmp->Modified != INOPEN)//��������� open �У�������Ǽ��뵽 open ��
			{
				tmp->G = 14 + father->G;//����G
				tmp->parent = father;tmp->computeF();
				AddToOpenQueue(tmp);
			}else//����Ѿ��� open list �У���������·���Ƿ����
			{
				tmpG = father->G + 14;
				if(tmpG < tmp->G) //��� G ֵ��С
				{
					tmp->parent = father;tmp->computeF();
					tmp->G = tmpG;
				}
			}
		}
	}

}

//���ڵ��������Open����
inline void CAstar::AddToOpenQueue(AstarNode *node)
{
	node->Modified = INOPEN;
	m_openList.push_back(node);
}

 // ��Open����ȡ����С�Ĳ�����Close����
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

// ȡ�ù���ֵ�ĺ���ָ��
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