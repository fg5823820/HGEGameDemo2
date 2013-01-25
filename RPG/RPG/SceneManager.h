#pragma once 
#include "StdAfx.h"
#include "Npc.h"
#include "UIObject.h"
#include "Camera.h"
#include "Map.h"
typedef std::vector<CObject*>			OBJECTS;
typedef std::vector<CObject*>::iterator OBJ_ITR;


class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager(){m_pHge->Release();}

	bool Init();
	void Render();
	bool Update(float);
	void Cleanup();

	enum Scene
	{
		ON_SELECT,
		GAME_SCENE,
		ON_ITEMUI
	};

private:
	void OnSelect(float);
	void GameScene(float);
	void InitGameScene();
	void GuiControl(float);
	void CameraCtrl(float);
	Pos  GetMousePos();
	void AddNpc(char* name, float x, float y);

private:

	Scene		m_scene;

	hgeGUI*		m_pGUI;
	hgeSprite*	m_pBG;
	hgeSprite*	m_pSltSpr;
	hgeSprite*	m_pMask;
	C2DCamera*	m_pCamera;
	CRole*		m_pRole;
	CMap*		m_pMap;

	int			m_alpha;
	float		m_timer;

	int			m_money;
	bool		m_bUIOn;
	bool		m_bMenuOn;

private:
	OBJECTS		m_objs;
	hgeResourceManager* m_pRs;
	static HGE*	m_pHge;

};

