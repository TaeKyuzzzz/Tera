#pragma once

//====================================================================
//	(필요한 부분은 직접 만들어서 추가 할 것!!) 
//====================================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//선그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x ,y, x + width, y + height };
	return rc;
}

//Rect 만들기(센터부터)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
//원그리기

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//원그리기 (센터로 부터)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline DWORD FtoDW(float f)
{
	return *((DWORD*)(&f));
}

inline bool IsEqualString(const char * c1, const char * c2)
{
	return strcmp(c1, c2) == 0;
}

//vector3의 y(높이)성분을 제외한 거리를 구할때 쓰세요.
inline float DistanceXZ(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	D3DXVECTOR2 temp;
	temp.x = a.x - b.x;
	temp.y = a.z - b.z;

	return D3DXVec2Length(&temp);
}