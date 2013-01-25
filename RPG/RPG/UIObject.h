#pragma once

#include "StdAfx.h"
#include "Object.h"
#include <hgegui.h>

void SetItemHide(hgeGUI* gui,int id,bool b);

class CUIObject : public hgeGUIObject, public CObject
{
public:
	CUIObject(int id, Pos pos, Pos hidePos,hgeResourceManager* rs,char* name, float spd = 200.f);
	virtual~CUIObject();

	bool	Init(){return true;}
	void	Cleanup(){}
	virtual void	Render();
	virtual void	Update(float);
	virtual void	Enter() {}
	virtual void	Leave() {}
	virtual void	Reset() {}
	virtual bool	IsDone() { return true; }
	virtual void	Focus(bool bFocused) {}
	virtual void	MouseOver(bool bOver);

	virtual bool	MouseMove(float x, float y) { return false; }
	virtual bool	MouseLButton(bool bDown);
	virtual bool	MouseRButton(bool bDown) { return false; }
	virtual bool	MouseWheel(int nNotches) { return false; }
	virtual bool	KeyClick(int key, int chr) { return false; }

	inline  void	SetHide(bool b){m_bHide=b;}

	enum ID
	{
		MENU_ENTRY = 1,
		HEAD,
		MONEY,
		ITEM_S,
		SKILL,
		ITEM
	};

protected:
	Pos			m_hidePos,m_showPos;
	float		m_spd;
	hgeSprite*  m_spr;
	bool		m_bHide;
};

class CMoneyUI : public CUIObject
{
public:
	CMoneyUI(int id, Pos pos, Pos hidePos,Pos fontOffsetPos,
		int* money, hgeResourceManager*, hgeFont*, char* name,
		float spd = 200.f);

	void	Render();
	void	MouseOver(bool bOver){}

private:
	hgeFont*	m_font;
	int*		m_money;
	Pos			m_fontPos;
};