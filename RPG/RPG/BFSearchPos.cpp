#include "BFSearchPos.h"
#include "Map.h"

#define POS(x,y) (((long)y<<16)|x)
#define POS_X(pos)   (pos&0xffff)
#define POS_Y(pos)   (pos>>16)
#define INDEX(x,y)		(x)+(y)*m_col //一维数组变下标转二维数字下标

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



CFindBestPos::CFindBestPos(int width, int height):
m_col(width),
m_row(height)
{
	Make2DArrayCPP(m_row, m_col, m_visited);
	for (int j=0;j<m_row;j++) 
	{
		for (int i=0;i<m_col;i++) 
		{
			m_visited[j][i] = false;
		}
	}
}

CFindBestPos::~CFindBestPos()
{
	Diliver2DArrayCPP(m_visited, m_row);
}

bool CFindBestPos::TestPoint( int x,  int y, 
							 int* &bestx, int* &besty,
							 char *tiles)
{
	if(( x >=0 && x < m_col ) && 
		( y >=0 && y < m_row ))//此结点是否存在
	{//如果存在
		if(!m_visited[y][x])//检查是否已经访问
		{//如果未访问
			if(tiles[INDEX(x,y)])//检查是否能
			{//如果能通过
				*bestx = x;//返回最佳点
				*besty = y;//返回最佳点
				return true;//退出
			}else
			{//如果不能通过
				m_visited[y][x] = true;//标记已经访问
				m_que.push(POS(x,y));//放入队列
			}
		}//如果已经访问则忽略这个结点
	}
	return false;
}

void CFindBestPos::FindBestPos(int x,int y, int *bestx, int *besty, char *tiles)
{
	//printf("col:%d row:%d\nx:%d y:%d",m_col, m_row,x,y);
	if( x < 0 || x >= m_col  ||  y < 0 || y >= m_row )
	{//此结点不合法
		*bestx = -1;*besty = -1;
		return;
	}
	//初始化数组
	for(int i = 0;i < m_row;i ++)
	{
		for(int j = 0;j < m_col;j ++)
		{
			m_visited[i][j]=false;
		}
	}
		
	m_visited[y][x] = true;		//标记已访问

	long u;
	m_que.push(POS(x,y));				//初始结点v入队列

	while(!m_que.empty())			//队列非空时
	{
		u = m_que.front();m_que.pop();	//出队列
		//上 
		if(TestPoint(POS_X(u), POS_Y(u)-1, bestx, besty, tiles))break;

		//下
		if(TestPoint(POS_X(u), POS_Y(u)+1, bestx, besty, tiles))break;

		//左 
		if(TestPoint(POS_X(u)-1, POS_Y(u), bestx, besty, tiles))break;

		//右 
		if(TestPoint(POS_X(u)+1, POS_Y(u), bestx, besty, tiles))break;


		//左上
		if(TestPoint(POS_X(u)-1, POS_Y(u)-1, bestx, besty, tiles))break;

		//右上
		if(TestPoint(POS_X(u)+1, POS_Y(u)+1, bestx, besty, tiles))break;

		//左下 
		if(TestPoint(POS_X(u)-1, POS_Y(u)+1, bestx, besty, tiles))break;

		//右下
		if(TestPoint(POS_X(u)+1, POS_Y(u)+1, bestx, besty, tiles))break;
	//	up_left.x = u.x-1;up_left.y = u.y-1;//左上
	//	if(TestPoint(up_left, best, m_que, m_visited, tiles))break;

	//	up_right.x = u.x+1;up_right.y = u.y-1;//右上
	//	if(TestPoint(up_right, best, m_que, m_visited, tiles))break;

	//	down_left.x = u.x-1;down_left.y = u.y+1;//左下 
	//	if(TestPoint(down_left, best, m_que, m_visited, tiles))break;

	//	down_right.x = u.x+1;down_right.y = u.y+1;//右下
	//	if(TestPoint(down_right, best, m_que, m_visited, tiles))break;

	}
	m_que.c.clear();
}