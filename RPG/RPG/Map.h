#pragma once 
#include <string>

class HGE;

//struct char
//{
//public:
//	char():
//	  passable(true),
//		  height(0)
//	{}
//	bool			passable;	//能否通行
//	unsigned char	height;		//高度信息
//};

class CMap
{
public:
	CMap(int tileWidth, int tileHeight, char* fileName);
	~CMap();

	bool Init();
	void Render();
	void Update();
	void Cleanup();
	
	//char* m_map							{return m_map;}
	//inline int	 GetCol()const			{return m_col;}
	//inline int	 GetRow()const			{return m_row;}
	inline float GetMapWidth()const		{return (float)m_tileWidth*m_col;	}
	inline float GetMapHeight()const	{return (float)m_tileHeight*m_row;	}
	//inline float GetMapTileWidth()const	 {return (float)m_tileWidth;		}
	//inline float GetMapTileHeight()const {return (float)m_tileHeight;		}
	bool	 Passable(int x, int y)const;

	
	int		m_tileWidth;
	int		m_tileHeight;
	int		m_col;			//(宽)
	int		m_row;			//(高)
	char*	m_map;
	char*	m_dynamicMap;

private:
	char*	m_fileName;
	static HGE* m_pHge;
	
};

