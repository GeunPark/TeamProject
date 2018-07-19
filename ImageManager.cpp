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
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
	img = new Image;
	if (FAILED(img->Init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	/* STL ���� �ٽ� #################################################################################### */ 
	//Ű, ���� ���� ������!!!!
	//ù��° = Ű(Ű��) -> first 
	//�ι��� = ��(����) -> second
	//�����͸� �߰��Ҷ� Ű, ������ ������ ����־�� �Ѵ�.
	//pair, make_pair�� ����ؼ� �߰��Ѵ�.

	// pair ���
	//_mImageList.insert(pair<string, Image*>(strKey, img));
	// make_pair ���

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * ImageManager::AddImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
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
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
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
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
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
	//�߰��Ϸ��� �̹����� �����ϴ��� Ű������ Ȯ��
	Image* img = FindImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� ���� �Ѵٸ� ���� ������ �ʰ� �ٷ� ����
	if (img) return img;

	//������ �̹��� ���� ����
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
	//�ش�Ű �˻�
	MapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		return key->second;
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL;
	return NULL;
}

BOOL ImageManager::DeleteImage(string strKey)
{
	//�ش�Ű �˻�
	MapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ� �̹���Ŭ���� ����
	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->Release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//���� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;	
	}

	//�˻��� Ű�� �̹����� ��ã�Ҵٸ� NULL;
	return FALSE;
}

BOOL ImageManager::DeleteAll()
{
	//�� ��ü�� ���鼭 �ϳ��� ���� �����
	MapImageIter iter = _mImageList.begin();
	//for(;;) => while(true)
	for (;iter != _mImageList.end();)
	{
		//�̹����� ������ �̹��� Ŭ���� ����
		if (iter->second != NULL)
		{
			iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else	//�̹����� ������
		{
			++iter;
		}
	}

	//�� ��ü�� ����
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


