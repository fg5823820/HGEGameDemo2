#include "Camera.h"
#include <hge.h>
#include <math.h>

HGE* C2DCamera::m_pHge = 0;
C2DCamera::C2DCamera() :
x(0.f),y(0.f),
dx(0.f),dy(0.f),
rot(0.f),
hscale(1.f),vscale(1.f)
{
	m_pHge = hgeCreate(HGE_VERSION);
}

C2DCamera::~C2DCamera()
{
	m_pHge->Release();
}

void C2DCamera::SetTransform()
{
	m_pHge->Gfx_SetTransform(x, y, floor(dx), floor(dy), rot, hscale, vscale);
	//m_pHge->Gfx_SetTransform(x, y, dx, dy, rot, hscale, vscale);
}

void C2DCamera::EndTransform()
{
	m_pHge->Gfx_SetTransform();
}

void C2DCamera::Zoom(float _x, float _y, float units)
{ 
	x = _x;
	y = _y;
	vscale = hscale +=units; 
	if(hscale <= 0.01f)vscale = hscale = 0.01f;
} 