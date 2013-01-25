#pragma once
#include "Object.h"
#include <hgevector.h>

typedef std::vector<CObject*>			MOBJ;
typedef std::vector<CObject*>::iterator MOBJ_ITR;
/*
**可移动物体，只能进行点对点移动
*/

class CMoveableObj : public CObject
{
public:
	CMoveableObj(hgeResourceManager* rs);
	virtual ~CMoveableObj();

	virtual bool Init() = 0;
	virtual void Render() = 0;
	virtual void Update(float dt);
	virtual void Cleanup() = 0;

	inline float GetSpeed()const {return m_speed;}

protected:

	static MOBJ* m_mobjs;

	Pos			m_dst;//目标
	float		m_speed;
	bool		m_bMoving;
};