#pragma once
#include "SingletonBase.h"
#include "Image.h"
//=============================================================
//	## ImageManager ## (이미지 매니저)
//=============================================================

class ImageManager : public  SingletonBase <ImageManager>
{
private:
	typedef map<string, Image*> MapImageList;				//맵으로 만든 이미지목록
	typedef map<string, Image*>::iterator MapImageIter;		//맵으로 만든 이미지목록의 반복자

private:
	MapImageList _mImageList;		//실제 이미지 클래스를 담을 STL맵


public:
	//이미지 매니저 초기화
	HRESULT Init();
	//이미지 매니저 해제
	void Release();

	//빈 비트맵으로 초기화
	Image* AddImage(string strKey, int width, int height);
	//이미지 파일로 초기화 (주사용)
	Image* AddImage(string strKey, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* AddImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일로 초기화 (주사용)
	Image* AddFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	Image* AddFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	//이미지 키값으로 찾기
	Image* FindImage(string strKey);
	//이미지 키값으로 삭제
	BOOL DeleteImage(string strKey);
	//이미지 전체 삭제
	BOOL DeleteAll();

//============================================================================================================================================
// ## 일반 렌더 ##
//============================================================================================================================================
	void Render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);
//============================================================================================================================================
// ## 알파 렌더 ##
//============================================================================================================================================
	void AlphaRender(string strKey, HDC hdc, BYTE alpha);
	void AlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);
//============================================================================================================================================
// ## 프레임 렌더 ##
//============================================================================================================================================
	void FrameRender(string strKey, HDC hdc, int destX, int destY);
	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	ImageManager() {};
	~ImageManager() {};
};

