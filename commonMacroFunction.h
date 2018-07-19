#pragma once
#define PI 3.141592654f		//180도
#define PI2 (PI * 2)			//360도

//나중에 이미지 회전시 사용할 값
#define PI_2 (PI / 2)		//90도
#define PI_4 (PI / 4)		//45도
#define PI_8 (PI / 8)		//22.5도
//===============================================================
//	## commonMacroFuntion ## (필요한 부분은 직접 만들어서 추가할것)
//===============================================================

//POINT
inline POINT Pointmake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//선 그리기
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

//RECT 중짐섬에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//렉탱글 함수 이용해서 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//일립스함수 이용해서 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//일립스 함수 이용해서 센터점 중심으로 그리기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline float GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float dirX, dirY;
	float distance;
	float angle;

	dirX = x2 - x1;
	dirY = y2 - y1;

	distance = sqrtf(dirX * dirX + dirY * dirY);

	angle = acosf(dirX / distance);

	if (y2 > y1)
	{
		angle = PI2 - angle;
		if (angle >= PI2) angle -= PI2;
	}
	return angle;
}