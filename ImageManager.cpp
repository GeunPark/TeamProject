#include "stdafx.h"
#include "ImageManager.h"


HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	this->DeleteAll();
}

Image * ImageManager::AddImage(string strKey, int width, int height)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/* STL 맵의 핵심 #################################################################################### */ 
	//키, 값을 잊지 말도록!!!!
	//첫번째 = 키(키값) -> first 
	//두번쨰 = 값(벨류) -> second
	//데이터를 추가할때 키, 벨류를 쌍으로 집어넣어야 한다.
	//pair, make_pair를 사용해서 추가한다.

	// pair 사용
	//_mImageList.insert(pair<string, Image*>(strKey, img));
	// make_pair 사용

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->Init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->Init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가하려는 이미지가 존재하는지 키값으로 확인
	Image* img = FindImage(strKey);

	//추가하려는 이미지가 이미 존재 한다면 새로 만들지 않고 바로 리턴
	if (img) return img;

	//없으면 이미지 새로 생성
	img = new Image;
	if (FAILED(img->Init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::FindImage(string strKey)
{
	//해당키 검색
	MapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 이미지클래스 리턴
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 이미지를 못찾았다면 NULL;
	return NULL;
}

BOOL ImageManager::DeleteImage(string strKey)
{
	//해당키 검색
	MapImageIter key = _mImageList.find(strKey);

	//검색한 키를 찾았다면 이미지클래스 삭제
	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->Release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//맵의 반복자 삭제
		_mImageList.erase(key);

		return TRUE;	
	}

	//검색한 키로 이미지를 못찾았다면 NULL;
	return FALSE;
}

BOOL ImageManager::DeleteAll()
{
	//맵 전체를 돌면서 하나씩 전부 지운다
	MapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	for (;iter != _mImageList.end();)
	{
		//이미지가 있으니 이미지 클래스 삭제
		if (iter->second != NULL)
		{
			iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else	//이미지가 없으면
		{
			++iter;
		}
	}

	//맵 전체를 삭제
	_mImageList.clear();

	return TRUE;
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY);
}

void ImageManager::Render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	Image* img = FindImage(strKey);

	if (img) img->Render(hdc, destX, destY ,sourX, sourY, sourW, sourH);
}

void ImageManager::AlphaRender(string strKey, HDC hdc, BYTE alpha)
{
	Image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, alpha);
}

void ImageManager::AlphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	Image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, destX, destY, alpha);
}

void ImageManager::AlphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
{
	Image* img = FindImage(strKey);

	if (img) img->AlphaRender(hdc, destX, destY, sourX, sourY, sourW, sourH, alpha);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = FindImage(strKey);

	if (img) img->FrameRender(hdc, destX, destY);
}

void ImageManager::FrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = FindImage(strKey);

	if (img) img->FrameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}


