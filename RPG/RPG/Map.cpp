#include "Map.h"
#include "StdAfx.h"
#include <fstream>



HGE* CMap::m_pHge = 0;
CMap::CMap(int tileWidth, int tileHeight, char* fileName) :
m_tileWidth(tileWidth),
m_tileHeight(tileHeight),
m_fileName(fileName),
m_dynamicMap(0)
{
	m_pHge = hgeCreate(HGE_VERSION);
}
CMap::~CMap()
{
	m_pHge->Release();
}

bool CMap::Init()
{
	HTEXTURE tex = m_pHge->Texture_Load(m_fileName);
	if(!tex)return false;
	m_col = m_pHge->Texture_GetWidth(tex);
	m_row = m_pHge->Texture_GetHeight(tex);
	
	DWORD* data = m_pHge->Texture_Lock(tex);

	m_map = new char[m_col*m_row];
	
	for(int i = 0;i < m_col*m_row;i ++)
		m_map[i] = GETR(data[i])? 1 : 0;

	m_pHge->Texture_Unlock(tex);
	m_pHge->Texture_Free(tex);

	m_dynamicMap = new char[m_col*m_row];
	for(int i = 0;i < m_col*m_row;i ++)
	{
		m_dynamicMap[i] = m_map[i];
	}

	return true;
}


void CMap::Render()
{

}

void CMap::Update()
{
	//for(int i = 0;i < m_col*m_row;i ++)
	//{
	//	m_dynamicMap[i] = m_map[i];
	//}
	memcpy(m_dynamicMap, m_map, sizeof(char)*m_col*m_row);
}

void CMap::Cleanup()
{
	delete[] m_map;
	m_map = NULL;
	delete[] m_dynamicMap;
	m_dynamicMap = NULL;
}


bool CMap::Passable(int x, int y)const
{
	if(x >= m_col || y >= m_row || x < 0 || y < 0)return false;
	return m_map[y*m_col + x]? true : false;
}