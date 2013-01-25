#include "BFSearchPos.h"
#include "Map.h"

#define INDEX(point) (point.x)+(point.y)*col //一维数组变下标转二维数字下标

CFindBestPos::CFindBestPos(int width, int height):
visited(0),
col(width),
row(height)
{
	visited = new bool[width*height]; 
}

CFindBestPos::~CFindBestPos()
{
	delete visited;
	visited = 0;
}

bool CFindBestPos::TestPoint( BSPoint testPoint, 
							 BSPoint *&best, 
							 std::queue<BSPoint> &queue, 
							 bool *&visited, 
							 Tile *tiles)
{
	if(( testPoint.x >=0 && testPoint.x < col ) && 
		( testPoint.y >=0 && testPoint.y < row ))//up是否存在
	{//如果存在
		if(!visited[INDEX(testPoint)])//检查是否已经访问
		{//如果未访问
			if(tiles[INDEX(testPoint)].passable)//检查是否能
			{//如果能通过
				*best = testPoint;//返回最佳点
				return true;//退出
			}else
			{//如果不能通过
				visited[INDEX(testPoint)] = 1;//标记已经访问
				queue.push(testPoint);//放入队列
			}
		}//如果已经访问则忽略这个结点
	}
	return false;
}

void CFindBestPos::FindBestPos(BSPoint v, BSPoint *best, Tile *tiles)
{
	best->x = -1;best->y = -1; 
	for(int i = 0;i < col*row;i ++) visited[i] = 0;//初始化访问数组
		
	visited[INDEX(v)] = 1;		//标记已访问

	BSPoint u, up, down, left, right, up_left, up_right, down_left, down_right;
	que.push(v);				//初始结点v入队列

	while(!que.empty())			//队列非空时
	{
		u = que.front();que.pop();	//出队列

		up.x = u.x;up.y = u.y-1;//上 
		if(TestPoint(up, best, que, visited, tiles))break;

		down.x = u.x;down.y = u.y+1; //下
		if(TestPoint(down, best, que, visited, tiles))break;

		left.x = u.x-1;left.y = u.y; //左
		if(TestPoint(left, best, que, visited, tiles))break;

		right.x = u.x+1;right.y = u.y;//右 
		if(TestPoint(right, best, que, visited, tiles))break;


		up_left.x = u.x-1;up_left.y = u.y-1;//左上
		if(TestPoint(up_left, best, que, visited, tiles))break;

		up_right.x = u.x+1;up_right.y = u.y-1;//右上
		if(TestPoint(up_right, best, que, visited, tiles))break;

		down_left.x = u.x-1;down_left.y = u.y+1;//左下 
		if(TestPoint(down_left, best, que, visited, tiles))break;

		down_right.x = u.x+1;down_right.y = u.y+1;//右下
		if(TestPoint(down_right, best, que, visited, tiles))break;

	}
	que.c.clear();
}