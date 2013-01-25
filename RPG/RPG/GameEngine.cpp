#include "StdAfx.h"
#include "GameEngine.h"
#include "SceneManager.h"
HGE* CGameEngine::m_pHge = 0;

//事件外包
bool CGameEngine::FrameFunc()
{
	return CGameEngine::Instance().Update();
}

//渲染外包
bool CGameEngine::ReaderFunc()
{
	return CGameEngine::Instance().Render();
}


CGameEngine::CGameEngine()
{
}

CGameEngine::~CGameEngine()
{	
}

void CGameEngine::RunEngine()
{
	m_pHge = hgeCreate(HGE_VERSION);	

    m_pHge->System_SetState(HGE_LOGFILE, LOGNAME);
    m_pHge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    m_pHge->System_SetState(HGE_RENDERFUNC, ReaderFunc);
    m_pHge->System_SetState(HGE_TITLE, TITLE);
    m_pHge->System_SetState(HGE_WINDOWED, true);
    m_pHge->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
    m_pHge->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
    m_pHge->System_SetState(HGE_SCREENBPP, 32);
    m_pHge->System_SetState(HGE_ICON, GAMEICON);
	m_pHge->System_SetState(HGE_USESOUND, false);
    m_pHge->System_SetState(HGE_SHOWSPLASH, false);	
	m_pHge->System_SetState(HGE_DONTSUSPEND, true);
	//m_pHge->System_SetState(HGE_FPS, HGEFPS_VSYNC );						

    if(m_pHge->System_Initiate())
    {
        if(Init()) m_pHge->System_Start();
        else MessageBox(NULL, L"载入失败！", L"错误", MB_ICONSTOP);
		Release();
    }

	m_pHge->System_Shutdown();
	m_pHge->Release();
}

bool CGameEngine::Init()   
{
	m_pMgr = NULL;
	m_pMgr = new CSceneManager();
	if(!m_pMgr->Init())return false;
	return true;
}

void CGameEngine::Release()    
{
	m_pMgr->Cleanup();
}

bool CGameEngine::Render()        
{
	m_pHge->Gfx_BeginScene();
	m_pHge->Gfx_Clear(0);

	m_pMgr->Render();

	m_pHge->Gfx_EndScene();
	return false;
}

bool CGameEngine::Update()
{
	if(m_pHge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	float dt = m_pHge->Timer_GetDelta();
	//if(dt > 0.016f)
	//	dt = 0.016f;
	return m_pMgr->Update(dt);
}