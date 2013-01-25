
#include "SceneManager.h"
#include "Utilities.h"
#include "MapElement.h"
#include "Grid.h"
#include <algorithm>

using std::sort;

HGE* CSceneManager::m_pHge = 0;
CSceneManager::CSceneManager() :
m_scene(ON_SELECT),
m_pGUI(0),
m_pBG(0),
m_pSltSpr(0),
m_pMask(0),
m_pCamera(0),
m_pRole(0),
m_alpha(0),
m_timer(0.0f),
m_money(0),
m_pMap(0),
m_bMenuOn(0)
{
	m_pHge = hgeCreate(HGE_VERSION);
}

bool CSceneManager::Init()
{
	if(m_pHge->Resource_AttachPack("res.dat"))printf("LoadPack Success!\n");
	else printf("LoadPack Fail!Try To Load From File...\n");
	m_pRs = new hgeResourceManager(SCRIPTNAME);
	m_pRs->Precache();
	m_pCamera = new C2DCamera();
	m_pBG = m_pRs->GetSprite("Logo");
	m_pSltSpr = m_pRs->GetSprite("TouchStart");
	m_pMask = m_pRs->GetSprite("Black");
	m_pGUI = new hgeGUI();
	m_pGUI->SetCursor(m_pRs->GetSprite("Cursor"));

	m_pMap = new CMap(20,20, "city.bmp");
	if(!m_pMap->Init())
		return false;

	m_pRole = new CRole(m_pRs, "reimu" , m_pMap);
	m_pRole->Init();
	m_pRole->SetPos(400.f,350.f);
	m_objs.push_back(m_pRole);

	m_objs.push_back(new CGrid(m_pMap->m_col,m_pMap->m_row,m_pMap->m_tileWidth,m_pMap->m_tileHeight));
	CMapElement* elem = new CMapElement(m_pRs, Pos(40,40*8), "Elem01");
	elem->Init();
	m_objs.push_back(elem);

	elem = new CMapElement(m_pRs, Pos(40*2,40*10), "Elem02");
	elem->Init();
	m_objs.push_back(elem);

	for(int i = 0;i < 8;i ++)
	{
		//AddNpc("youmu", 300, 200 + 40*i);
		//AddNpc("pachi", 350, 200 + 40*i);
	}

	printf("Init Success!\n");
	return true;
}

void CSceneManager::AddNpc(char* name, float x, float y)
{
	CNpc* npc = NULL;
	npc = new CNpc(m_pRs, name, m_pMap, 0);
	npc->Init();
	npc->SetPos(x, y);
	m_objs.push_back(npc);
}

void CSceneManager::Cleanup()
{
	m_pRs->Purge();
	for(OBJ_ITR itr = m_objs.begin();itr != m_objs.end();itr ++)
	{
		(*itr)->Cleanup();
		Delete(*itr);
	}
	m_objs.clear();
	Delete(m_pGUI);
	Delete(m_pCamera);
	Delete(m_pRs);
}

bool CSceneManager::Update(float dt)
{
	GuiControl(dt);
	m_pMap->Update();

	switch(m_scene)
	{
	case ON_SELECT:
		OnSelect(dt);
		break;
	case GAME_SCENE:
		GameScene(dt);
		break;
	}
	if(m_alpha < 0) m_alpha = 0;
	
	return false;
}


void CSceneManager::OnSelect(float dt)
{
	static float timer = 0.f;
	static bool swch = true;
	static bool swch2 = true;
	if(m_pHge->Input_KeyDown(HGEK_LBUTTON)) swch2 = false;
	if(swch2)
	{
		if(swch)
		{
			timer += dt;
			if(timer > 1.0f)
			{
				timer = 1.f;
				swch = false;
			}
		}else
		{
			timer -= dt;
			if(timer < 0.0f)
			{
				timer = 0.f;
				swch = true;
			}
		}
	}else
	{
		if(swch)
		{
			timer += dt*15;
			if(timer > 1.0f)
			{
				timer = 1.f;
				swch = false;
			}
		}else
		{
			timer -= dt*15;
			if(timer < 0.0f)
			{
				timer = 0.f;
				swch = true;
			}
		}
		m_timer += dt;
		if(m_timer > 1.0f)
		{
			InitGameScene();
			//m_pRs->Purge(1);//问题不明
		}
	}
	int alpha = (int)(timer * 255);
	m_alpha = (int)(m_timer * 255);
	if(alpha < 0) alpha = 0;
	m_pSltSpr->SetColor(ARGB(alpha, 0xff, 0xff, 0xff));
	
}

void CSceneManager::InitGameScene()
{
	m_timer = 1.0f;
	m_scene = GAME_SCENE;
	m_pBG = m_pRs->GetSprite("Map");
	m_pGUI->AddCtrl(new CUIObject(CUIObject::MENU_ENTRY ,
		Pos(SCREEN_WIDTH-68,0), Pos(SCREEN_WIDTH-68,-64),m_pRs, "Menu"));
	m_pGUI->AddCtrl(new CUIObject(CUIObject::ITEM ,
		Pos(32,128), Pos(32,-64),m_pRs, "Skill",500.f));
	m_pGUI->AddCtrl(new CUIObject(CUIObject::SKILL ,
		Pos(32,64), Pos(32,-64),m_pRs, "Item",500.f));
	m_pGUI->AddCtrl(new CUIObject(CUIObject::HEAD ,
		Pos(8,0), Pos(8,-64),m_pRs, "Avatar"));
	m_pGUI->AddCtrl(new CUIObject(CUIObject::ITEM_S ,
		Pos(SCREEN_WIDTH-102,SCREEN_HEIGHT-64), 
		Pos(SCREEN_WIDTH-102,SCREEN_HEIGHT+1),m_pRs, "Item_s"));
	m_pGUI->AddCtrl(new CMoneyUI(CUIObject::MONEY ,
		Pos(SCREEN_WIDTH-311,SCREEN_HEIGHT-60), 
		Pos(SCREEN_WIDTH-311,SCREEN_HEIGHT+5),
		Pos(154,12),
		&m_money,m_pRs,m_pRs->GetFont("MoneyFont"),"Money"));
}

void CSceneManager::GameScene(float dt)
{
	if(m_timer > 0.0f) m_timer -= dt;
	if(m_timer < 0.0f) m_timer = 0.0f;
	m_alpha = (int)(m_timer * 255);


	
	//m_pRole->Update(dt);
	for(OBJ_ITR itr = m_objs.begin();itr != m_objs.end();itr ++)
	{
		(*itr)->Update(dt);
	}
	if(m_pHge->Input_KeyDown(HGEK_LBUTTON) && !m_bUIOn)
		m_pRole->SetDst(GetMousePos());

	if(m_pRole->IsMoving())
		SetItemHide(m_pGUI,CUIObject::MENU_ENTRY,true);
	else if(m_bMenuOn)
		SetItemHide(m_pGUI,CUIObject::MENU_ENTRY,true);
	else
		SetItemHide(m_pGUI,CUIObject::MENU_ENTRY,false);

	m_money++;

	CameraCtrl(dt);
	sort(m_objs.begin(), m_objs.end(), CompareByY());
}


//UI管理
void CSceneManager::GuiControl(float dt)
{
	static bool bhead = true;
	int id=m_pGUI->Update(dt);
	switch(id)
	{
	case CUIObject::MENU_ENTRY:
		for(int i = CUIObject::HEAD;i <= CUIObject::ITEM_S;i++)
			SetItemHide(m_pGUI,i,false);
		SetItemHide(m_pGUI, CUIObject::MENU_ENTRY,true);
		m_bUIOn = true;
		m_bMenuOn = true;
		break;
	case CUIObject::HEAD:
		if(bhead)
		{
			for(int i = CUIObject::SKILL;i <= CUIObject::ITEM;i++)
				SetItemHide(m_pGUI,i,false);
			for(int i = CUIObject::MONEY;i <= CUIObject::ITEM_S;i++)
				SetItemHide(m_pGUI,i,true);
			bhead = false;
		}else
		{
			for(int i = CUIObject::SKILL;i <= CUIObject::ITEM;i++)
				SetItemHide(m_pGUI,i,true);
			for(int i = CUIObject::MONEY;i <= CUIObject::ITEM_S;i++)
				SetItemHide(m_pGUI,i,false);
			bhead = true;
		}
		break;
	}

	if(m_pHge->Input_KeyDown(HGEK_LBUTTON) && m_scene != ON_SELECT)
		if(!id)
		{
			if(m_bMenuOn)
			{
				if(!bhead)
				{
					for(int i = CUIObject::SKILL;i <= CUIObject::ITEM;i++)
						SetItemHide(m_pGUI,i,true);
					for(int i = CUIObject::MONEY;i <= CUIObject::ITEM_S;i++)
						SetItemHide(m_pGUI,i,false);
					
					bhead = true;
				}else
				{
					for(int i = CUIObject::HEAD;i <= CUIObject::ITEM;i++)
						SetItemHide(m_pGUI,i,true);
					m_bMenuOn = false;
				}
			}
			else
				m_bUIOn = false;
		}
}

Pos  CSceneManager::GetMousePos()
{
	Pos tmp;
	m_pHge->Input_GetMousePos(&tmp.x, &tmp.y);
	m_pCamera->MouseCorrect(&tmp.x, &tmp.y);
	return tmp;
}

void CSceneManager::CameraCtrl(float dt)
{
	Pos tmp = m_pRole->GetPos();
	m_pCamera->ObjectCorrect(&tmp.x, &tmp.y);
//printf("%.2f %.2f\n",tmp.x, tmp.y);
	Pos pt1(SCREEN_WIDTH/4.f, SCREEN_HEIGHT/4.f);
	Pos pt2((SCREEN_WIDTH/4.f)*3, (SCREEN_HEIGHT/4.f)*3);
	if(!CollidePiontInEllipse(pt1, pt2, 
						   Pos(SCREEN_WIDTH/2.f, SCREEN_HEIGHT/2.f), //椭圆中心点
						   tmp))
	{
		hgeVector v(SCREEN_WIDTH/2.f-tmp.x, SCREEN_HEIGHT/2.f-tmp.y);
		v.Normalize();
		m_pCamera->Strafe(dt*m_pRole->GetSpeed()/1.2f*v.x);
		m_pCamera->Fly(dt*m_pRole->GetSpeed()/1.2f*v.y);
	}

	if(m_pHge->Input_GetKeyState(HGEK_UP))
		m_pCamera->Zoom( SCREEN_WIDTH/2.0f ,SCREEN_HEIGHT/2.0f, dt/2.0f );
	
	if(m_pHge->Input_GetKeyState(HGEK_DOWN))
		m_pCamera->Zoom( SCREEN_WIDTH/2.0f ,SCREEN_HEIGHT/2.0f, -dt/2.0f );

	if(m_pHge->Input_GetKeyState(HGEK_SPACE))
		m_pCamera->ReSetZoom();
}


void CSceneManager::Render()
{
	m_pCamera->SetTransform();
	m_pBG->Render(0,0);

	//debug////////////////
	static bool show = false;
	if(m_pHge->Input_KeyDown(HGEK_M))
		show = !show;
	if(show)
	{
		for(int i = 0;i < m_pMap->m_row;i ++)
		{
			for(int j = 0;j < m_pMap->m_col;j ++)
			{
				if(!(m_pMap->m_dynamicMap)[i*m_pMap->m_col+j])
					m_pRs->GetSprite("Tile")->Render((float)j*m_pMap->m_tileWidth, (float)i*m_pMap->m_tileHeight);
			}
		}
	}
	//////////////////////
	
	switch(m_scene)
	{
	case ON_SELECT:
		m_pSltSpr->RenderEx(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f + m_pSltSpr->GetHeight()*2,
			0.f,2.0f,2.0f);
		break;
	case GAME_SCENE:
		for(OBJ_ITR itr = m_objs.begin();itr != m_objs.end();itr ++)
		{
			(*itr)->Render();
		}
		break;
	}
	m_pCamera->EndTransform();

	m_pGUI->Render();
	if(m_alpha != 0)
	{
		m_pMask->SetColor(ARGB(m_alpha, 0x00, 0x00, 0x00));
		m_pMask->Render(0,0);
	}
	
	m_pRs->GetFont("MoneyFont")->printf(5, 100, HGETEXT_LEFT, 
		"FPS:%d %.2f %.2f\nFunction key:'SPACE' 'M'", m_pHge->Timer_GetFPS(), 
		m_pRole->GetPos().x, m_pRole->GetPos().y);
}