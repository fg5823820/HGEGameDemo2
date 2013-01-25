#include "MapElement.h"

CMapElement::CMapElement(hgeResourceManager *rs, Pos pos, char* name) :
CObject(rs),
m_pSpr(0)
{
	m_name = name;
	m_pos = pos;
}

bool CMapElement::Init()
{
	m_pSpr = new hgeSprite(*m_pRs->GetSprite(m_name));
	if(!m_pSpr) return false;
	return true;
}

void CMapElement::Render()
{
	m_pSpr->Render(m_pos.x, m_pos.y);
}

void CMapElement::Update(float dt)
{

}

void CMapElement::Cleanup()
{
	Delete(m_pSpr);
}