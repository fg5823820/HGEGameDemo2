#include "Object.h"

HGE* CObject::m_pHge = 0;

// ¹¹Ôìº¯Êý
CObject::CObject(hgeResourceManager* rs) :
m_name("UnName"),
m_pRs(rs),
m_width(0),
m_height(0)
{
	m_uID = NewID();
	ZeroMemory(&m_rect, sizeof(hgeRect));
	m_pHge = hgeCreate(HGE_VERSION);
}