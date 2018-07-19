#pragma once
#include "SingletonBase.h"
#include "Image.h"
//=============================================================
//	## ImageManager ## (�̹��� �Ŵ���)
//=============================================================

class ImageManager : public  SingletonBase <ImageManager>
{
private:
	typedef map<string, Image*> MapImageList;				//������ ���� �̹������
	typedef map<string, Image*>::iterator MapImageIter;		//������ ���� �̹�������� �ݺ���

private:
	MapImageList _mImageList;		//���� �̹��� Ŭ������ ���� STL��


public:
	//�̹��� �Ŵ��� �ʱ�ȭ
	HRESULT Init();
	//�̹��� �Ŵ��� ����
	void Release();

	//�� ��Ʈ������ �ʱ�ȭ
	Image* AddImage(string strKey, int width, int height);
	//�̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	Image* AddImage(string strKey, const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	Image* AddImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	Image* AddFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	Image* AddFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);

	//�̹��� Ű������ ã��
	Image* FindImage(string strKey);
	//�̹��� Ű������ ����
	BOOL DeleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL DeleteAll();

//============================================================================================================================================
// ## �Ϲ� ���� ##
//============================================================================================================================================
	void Render(string strKey, HDC hdc, int destX = 0, int destY = 0);
	void Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);
//============================================================================================================================================
// ## ���� ���� ##
//============================================================================================================================================
	void AlphaRender(string strKey, HDC hdc, BYTE alpha);
	void AlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);
//============================================================================================================================================
// ## ������ ���� ##
//============================================================================================================================================
	void FrameRender(string strKey, HDC hdc, int destX, int destY);
	void FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	ImageManager() {};
	~ImageManager() {};
};

