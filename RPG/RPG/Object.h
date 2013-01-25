

#pragma once
#include "stdafx.h"
#include <hgerect.h>
#include <hgeresource.h>

struct CompareByY;

class CObject
{
public:
	CObject(hgeResourceManager* rs);
	virtual ~CObject(){m_pHge->Release();}

private:
	// �½�����ID
	inline UINT NewID(){ static UINT id;return id ++; }

public:
	virtual bool Init() = 0;
	virtual void Render() = 0;
	virtual void Update(float) = 0;
	virtual void Cleanup() = 0;

public:
	// ��ȡ����ID
	inline UINT		GetID() const	{	return m_uID;	}
	// ��ȡ��������
	inline char*	GetName() const	{	return m_name;	}
	// ��ȡ����λ��
	inline Pos		GetPos() const	{	return m_pos;	}
	// ��ȡ����
	inline hgeRect* GetRect() 		{	return &m_rect;	}
	// ���ö���ID
	inline void		SetID(UINT id)				{	m_uID = id;		}
	// ���ö�������
	inline void		SetName(char* name)			{	m_name = name;	}
	// ���ö���λ��
	inline void		SetPos(const Pos& pos)		{	m_pos = pos;	}
	// ��������
	inline void		SetRect(const hgeRect& rect){	m_rect = rect;	}

	friend CompareByY;

protected:
	UINT	  m_uID;		// ����ID
	char*	  m_name;		// ��������
	Pos		  m_pos;		// λ��
	hgeRect	  m_rect;		// ����Χ
	float	  m_width,m_height;

	hgeResourceManager*	m_pRs;

protected:
	static HGE* m_pHge;
};

struct CompareByY
{
	CompareByY(){}
	bool operator()(CObject* lhs, CObject *rhs)const
	{return lhs->m_pos.y < rhs->m_pos.y;}
};









