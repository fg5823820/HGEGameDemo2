#pragma once

#include "Singleton.h"

class HGE;
class CSceneManager;

class CGameEngine : public CSingleton<CGameEngine>
{
public:
	CGameEngine();
	~CGameEngine();

	void RunEngine();

private:
	//Íâ°üº¯Êý
	static bool FrameFunc();
	static bool ReaderFunc();

	bool Init();                
	void Release();             
	bool Render();              
	bool Update();      

private:
	CSceneManager* m_pMgr;
	static HGE*	m_pHge;

};
