#pragma once

#include <stdio.h>
#include <math.h>
#include <hge.h>
#include <vector>
//#include <hgecollision.h>


#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	576
#define NONE			-1

#define SCRIPTNAME		"ResScript.txt"		//脚本名
#define GAMEICON		"dust.ico"			//图标名
#define LOGNAME			"hgeRPG.log"		//LOG文件名
#define TITLE			"RPGTest"			//窗口名

template<class T> void Delete(T& t)
{
	if (t)
	{
		delete t;
		t = 0;
	}
}

struct Pos
{
	Pos():x(0),y(0){}
	Pos(float _x,float _y):x(_x),y(_y){}
	bool operator == (const Pos& pos)const//约等
	{
		return (abs(x-pos.x) < 0.1f && abs(y-pos.y) < 0.1f);
	}
	float x;
	float y;
};


