#pragma once

class HGE;

class C2DCamera
{
public:
	C2DCamera();
	~C2DCamera();

	inline void Strafe(float units)	{	dx += units;	} // ��/��
	inline void Fly(float units)	{	dy += units;	}  // ��/��

	void Zoom(float _x, float _y, float units);   

	inline void Rotate(float _x, float _y, float angle)
	{x = _x; y = _y; rot = angle;}  // �Ƶ���ת

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

