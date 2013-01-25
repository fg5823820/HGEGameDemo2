#include "Utilities.h"
#include "UIObject.h"

CUIObject::CUIObject(int _id, Pos pos, Pos hidePos, 
					 hgeResourceManager* rs, char* name, 
					 float spd):
CObject(rs),
m_bHide(true)
{
	id = _id;

	m_showPos = pos;
	m_pos = m_hidePos = hidePos;
	m_spd = spd;

	bStatic=false;
	bVisible=true;
	bEnabled=true;

	m_name = name;

	m_spr = rs->GetSprite(m_name);
	m_width = m_spr->GetWidth();
	m_height = m_spr->GetHeight();
	rect.Set(m_pos.x, m_pos.y, m_pos.x+m_width, m_pos.y+m_height);
	m_spr->SetColor(0xffcccccc);
}

CUIObject::~CUIObject()
{
}

void CUIObject::Render()
{
	m_spr->Render(floor(m_pos.x), floor(m_pos.y));
}

void CUIObject::Update(float dt)
{

	rect.Set(m_pos.x, m_pos.y, m_pos.x+m_width, m_pos.y+m_height);
	if(m_bHide)
		Trace(&m_pos, m_hidePos, m_spd*dt);
	else
		Trace(&m_pos, m_showPos, m_spd*dt);
}

void CUIObject::MouseOver(bool bOver)
{
	if(bOver) 
	{
		gui->SetFocus(id);
		m_spr->SetColor(0xffffffff);
	}else
		m_spr->SetColor(0xffcccccc);
}

bool CUIObject::MouseLButton(bool bDown) 
{ 
	return bDown; 
}

CMoneyUI::CMoneyUI(int id, Pos pos, Pos hidePos, Pos fontPos, 
				   int* money, hgeResourceManager * rs, hgeFont * fnt, char* name,
				   float spd):
CUIObject(id,pos,hidePos,rs,name,spd),
m_font(fnt),
m_money(money),
m_fontPos(fontPos)
{
}

void CMoneyUI::Render()
{
	CUIObject::Render();
	m_font->printf(m_pos.x+m_fontPos.x, m_pos.y+m_fontPos.y, 
		HGETEXT_RIGHT, "%d", *m_money);
}

void SetItemHide(hgeGUI* gui, int id, bool b)
{
	((CUIObject*)gui->GetCtrl(id))->SetHide(b);
}


