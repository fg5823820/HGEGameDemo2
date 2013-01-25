#include "BFSearchPos.h"
#include "Map.h"

#define INDEX(point) (point.x)+(point.y)*col //һά������±�ת��ά�����±�

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
		( testPoint.y >=0 && testPoint.y < row ))//up�Ƿ����
	{//�������
		if(!visited[INDEX(testPoint)])//����Ƿ��Ѿ�����
		{//���δ����
			if(tiles[INDEX(testPoint)].passable)//����Ƿ���
			{//�����ͨ��
				*best = testPoint;//������ѵ�
				return true;//�˳�
			}else
			{//�������ͨ��
				visited[INDEX(testPoint)] = 1;//����Ѿ�����
				queue.push(testPoint);//�������
			}
		}//����Ѿ����������������
	}
	return false;
}

void CFindBestPos::FindBestPos(BSPoint v, BSPoint *best, Tile *tiles)
{
	best->x = -1;best->y = -1; 
	for(int i = 0;i < col*row;i ++) visited[i] = 0;//��ʼ����������
		
	visited[INDEX(v)] = 1;		//����ѷ���

	BSPoint u, up, down, left, right, up_left, up_right, down_left, down_right;
	que.push(v);				//��ʼ���v�����

	while(!que.empty())			//���зǿ�ʱ
	{
		u = que.front();que.pop();	//������

		up.x = u.x;up.y = u.y-1;//�� 
		if(TestPoint(up, best, que, visited, tiles))break;

		down.x = u.x;down.y = u.y+1; //��
		if(TestPoint(down, best, que, visited, tiles))break;

		left.x = u.x-1;left.y = u.y; //��
		if(TestPoint(left, best, que, visited, tiles))break;

		right.x = u.x+1;right.y = u.y;//�� 
		if(TestPoint(right, best, que, visited, tiles))break;


		up_left.x = u.x-1;up_left.y = u.y-1;//����
		if(TestPoint(up_left, best, que, visited, tiles))break;

		up_right.x = u.x+1;up_right.y = u.y-1;//����
		if(TestPoint(up_right, best, que, visited, tiles))break;

		down_left.x = u.x-1;down_left.y = u.y+1;//���� 
		if(TestPoint(down_left, best, que, visited, tiles))break;

		down_right.x = u.x+1;down_right.y = u.y+1;//����
		if(TestPoint(down_right, best, que, visited, tiles))break;

	}
	que.c.clear();
}