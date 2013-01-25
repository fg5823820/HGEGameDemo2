#include "MoveableObj.h"
#include "Utilities.h"

MOBJ* CMoveableObj::m_mobjs = new MOBJ;
CMoveableObj::CMoveableObj(hgeResourceManager* rs) :
CObject(rs),
m_speed(0.f),
m_bMoving(false)
{
	m_mobjs->push_back(this);
}

CMoveableObj::~CMoveableObj()
{
	Delete(m_mobjs);
}

void CMoveableObj::Update(float dt)
{
	Trace(&m_pos, m_dst, m_speed*dt);
}

