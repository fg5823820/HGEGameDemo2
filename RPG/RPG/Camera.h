#pragma once

class HGE;

class C2DCamera
{
public:
	C2DCamera();
	~C2DCamera();

	inline void Strafe(float units)	{	dx += units;	} // 左/右
	inline void Fly(float units)	{	dy += units;	}  // 上/下

	void Zoom(float _x, float _y, float units);   

	inline void Rotate(float _x, float _y, float angle)
	{x = _x; y = _y; rot = angle;}  // 绕点旋转

	inline void ReSetZoom(){hscale = 1.0f;vscale = 1.0f;}

	void SetTransform();
	void EndTransform();

	void MouseCorrect(float* _x, float* _y)	{ *_x -= dx/hscale ; *_y -= dy/vscale; }
	void ObjectCorrect(float* _x, float* _y){ *_x += dx/hscale ; *_y += dy/vscale; }

private:
	float x,y;
	float dx,dy;
	float rot;
	float hscale,vscale;

	static HGE* m_pHge;

};

