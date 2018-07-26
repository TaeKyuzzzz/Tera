#pragma once

//====================================================================
//	(�ʿ��� �κ��� ���� ���� �߰� �� ��!!) 
//====================================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x ,y, x + width, y + height };
	return rc;
}

//Rect �����(���ͺ���)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//�簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
//���׸���

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//���׸��� (���ͷ� ����)
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

//vector3�� y(����)������ ������ �Ÿ��� ���Ҷ� ������.
inline float DistanceXZ(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	D3DXVECTOR2 temp;
	temp.x = a.x - b.x;
	temp.y = a.z - b.z;

	return D3DXVec2Length(&temp);
}