#include "GameEngine.h"
#include "StdAfx.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-------------------------------------------------------------
#ifndef  NDEBUG     
	AllocConsole();                  //����Console����
	freopen("CONOUT$", "a", stdout); //ʹ��׼�������Console����
#endif
	//-------------------------------------------------------------
	printf("Start!\n\n"); ///
	CGameEngine::Instance().RunEngine();

    return 0;
}