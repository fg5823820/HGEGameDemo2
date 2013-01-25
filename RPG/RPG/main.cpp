#include "GameEngine.h"
#include "StdAfx.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-------------------------------------------------------------
#ifndef  NDEBUG     
	AllocConsole();                  //创建Console窗口
	freopen("CONOUT$", "a", stdout); //使标准输出导向Console窗口
#endif
	//-------------------------------------------------------------
	printf("Start!\n\n"); ///
	CGameEngine::Instance().RunEngine();

    return 0;
}