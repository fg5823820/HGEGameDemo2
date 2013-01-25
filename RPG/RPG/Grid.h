#pragma once 
#include "StdAfx.h"
#include "Object.h"

class CGrid : public CObject
{
public:
	CGrid(int col, int row, int colSize, int rowSize):
	  CObject(NULL),
		  m_col(col),
		  m_row(row),
		  m_colSize(colSize),
		  m_rowSize(rowSize),
		  m_bShow(false)
	  {}

	bool Init(){return true;}
	void Update(float){}
	void Render()
	{
		if(m_pHge->Input_KeyDown(HGEK_SPACE))
			m_bShow = !m_bShow;
		if(m_bShow)
		{
			for(int i = 0;i < m_col;i ++)
				m_pHge->Gfx_RenderLine((float)m_colSize*i, 0,
				(float)m_colSize*i,(float)m_row*m_rowSize);
			for(int j = 0;j < m_row;j ++)
				m_pHge->Gfx_RenderLine(0, (float)m_rowSize*j,
				(float)m_col*m_colSize,(float)m_rowSize*j);
		}
	}
	 void Cleanup(){}

private:
	int		m_col;//列（宽）
	int		m_row;//行（高）
	int		m_colSize;//列（宽）
	int		m_rowSize;//行（高）
	bool	m_bShow;


};