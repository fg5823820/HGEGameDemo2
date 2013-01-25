#include "Npc.h"

CNpc::CNpc(hgeResourceManager * rs, char *name, CMap *map, CAi* ai, float spd):
CRole(rs, name, map, spd ),
m_pAi(ai)
{
	
}

void CNpc::Update(float dt)
{
	CRole::Update(dt);


	Pos pos;
	pos.x = m_pHge->Random_Float(-200,200) + m_pos.x;
	pos.y = m_pHge->Random_Float(/*-200,200*/0,0) + m_pos.y;

	static float time = 0;
	time += dt;
	if(time > 2.0f)
	{
		time = 0;
		SetDst(pos);
	}
}