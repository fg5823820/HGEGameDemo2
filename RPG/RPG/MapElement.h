#pragma once
#include "Object.h"
#include <hgesprite.h>
class CMapElement : public CObject
{
public:
	CMapElement(hgeResourceManager* rs, Pos pos, char* name);

	virtual bool Init();
	virtual void Render();
	virtual void Update(float);
	virtual void Cleanup();

protected:
	hgeSprite*	m_pSpr;
};