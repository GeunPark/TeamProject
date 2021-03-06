#include "stdafx.h"
#include "Image.h"
#pragma comment (lib, "msimg32.lib")

Image::Image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _blendImage(NULL)
{
}
Image::~Image()
{
}



HRESULT Image::Init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈 먼저 하자
	if (_imageInfo != NULL) this->Release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans - FALSE;
	_transColor = RGB(0, 0, 0);

	//리소스 얻는데 실페하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->Release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈 먼저 하자
	if (_imageInfo != NULL) this->Release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->redID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->redID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일이름
	_fileName = NULL;

	//투명키 컬러 셋팅
	_isTrans - isTrans;
	_transColor = transColor;

	//리소스 얻는데 실페하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->Release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->Release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);


	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실페하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->Release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::Init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->Release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;


	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);


	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실페하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->Release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::Init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
	if (_imageInfo != NULL) this->Release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;


	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);


	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실페하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->Release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::Init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	// 재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 하자
		if (_imageInfo != NULL) this->Release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->redID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;


	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);


	//투명키 컬러 셋팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실페하면 종료
	if (_imageInfo->hBit == 0)
	{
		this->Release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::InitForAlphaBlend(void)
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블랜드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp - AC_SRC_OVER;

	//이미지 정보 구조체 새로 생성 후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->redID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::Release(void)
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명 컬러키 초기화
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	//알파 블렌드 이미지 정보가 있다면
	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		//포인터 삭제
		SAFE_DELETE(_imageInfo);
	}
}


void Image::Render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0,						//복사 시작지점 X
			0,						//복사 시작지점 Y
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 ( 마 젠 타 )
	}
	else //원본 이미지 그대로 출력꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			destX,					//복사될 좌표 시작점 X
			destY,					//복사될 좌표 시작점 Y
			sourW,					//복사될 이미지 가로크기
			sourH,					//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX,					//복사 시작지점 X
			sourY,					//복사 시작지점 Y
			sourW,					//복사 영역 가로크기
			sourH,					//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 ( 마 젠 타 )
	}
	else //원본 이미지 그대로 출력꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, sourW, sourH, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void Image::AlphaRender(HDC hdc, BYTE alpha)
{
	//알파블렌드를 처음사용하냐?
	//알파블렌드를 사용할 수 있도록 초기화 해라
	
	if (!_blendImage) this->InitForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할꺼냐 ?
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0,						//복사 시작지점 X
			0,						//복사 시작지점 Y
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 ( 마 젠 타 )

		//알파블랜드
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할꺼냐 ?
	{
		//알파블렌드
		AlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파블렌드를 처음사용하냐?
	//알파블렌드를 사용할 수 있도록 초기화 해라

	if (!_blendImage) this->InitForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없앤 후 알파블렌딩 할꺼냐 ?
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사될 좌표 시작점 X
			0,						//복사될 좌표 시작점 Y
			_imageInfo->width,		//복사될 이미지 가로크기
			_imageInfo->height,		//복사될 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0,						//복사 시작지점 X
			0,						//복사 시작지점 Y
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 ( 마 젠 타 )

									//알파블랜드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //원본 이미지 그대로 알파블렌딩 할꺼냐 ?
	{
		//알파블렌드
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha)
{
	//알파 블랜드를 처음 사용하나?
	//알파 블랜드를 사용할수있도록 초기화 해라
	if (!_blendImage)this->InitForAlphaBlend();

	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans) //여기서 색깔만 빼고
	{
		//1. 출력해야 될 화면DC에 그려져 있는 내용을 블렌드이미지에 그린다
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			_blendImage->hMemDC,   //복사할 장소의 DC
			0,                  //복사될 좌표 시작점 X
			0,                  //복사될 좌표 시작점 Y
			_imageInfo->width,      //복사될 이미지 가로크기
			_imageInfo->height,      //복사될 이미지 세로크기
			_imageInfo->hMemDC,      //복사될 대상 DC
			0, 0,               //복사 시작지점
			_imageInfo->width,      //복사 영역 가로크기
			_imageInfo->height,      //복사 영역 세로크기
			_transColor);         //복사할때 제외할 색상 (마젠타)
								  //다시 이동
								  //화면 DC에 있는걸 색상을 날리고 날린 이미지를 알파블랜드DC에 있는걸 화면DC로 옮긴다.(총 3번에 이동을 한다)
		AlphaBlend(hdc, destX, destY, sourW, sourH,
			_blendImage->hMemDC, sourX, sourY, sourW, sourH, _blendFunc);
	}
	else //원본 이미지 그대로 알파블랜딩 할꺼냐?
	{
		//알파블랜드
		AlphaBlend(hdc, destX, destY, sourW, sourH,
			_imageInfo->hMemDC, sourX, sourY, sourW, sourH, _blendFunc);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,													//복사할 장소의 DC
			destX,													//복사될 좌표 시작점 X
			destY,													//복사될 좌표 시작점 Y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점 Y
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor);											//복사할때 제외할 색상 ( 마 젠 타 )
	}
	else //원본 이미지 그대로 출력꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY, 
			_imageInfo->frameWidth, _imageInfo->frameHeight, 
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//이미지 예외처리
	//int hp;
	//if(hp < 0) hp = 0;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,													//복사할 장소의 DC
			destX,													//복사될 좌표 시작점 X
			destY,													//복사될 좌표 시작점 Y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점 Y
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor);											//복사할때 제외할 색상 ( 마 젠 타 )
	}
	else //원본 이미지 그대로 출력꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::FrameRender(HDC hdc, int destX, int destY, int sourW, int sourH, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //배경색 없앨꺼냐?
	{
		//GditransparentBlt : 비트맵의특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,													//복사할 장소의 DC
			destX,													//복사될 좌표 시작점 X
			destY,													//복사될 좌표 시작점 Y
			sourW,									//복사될 이미지 가로크기
			sourH,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사 시작지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사 시작지점 Y
			_imageInfo->frameWidth,									//복사 영역 가로크기
			_imageInfo->frameHeight,								//복사 영역 세로크기
			_transColor);											//복사할때 제외할 색상 ( 마 젠 타 )
	}
	else //원본 이미지 그대로 출력꺼냐?
	{
		//BitBlt : DC간의 영역끼리 서로 고속복사를 해주는 함수
		BitBlt(hdc, destX, destY,
			sourW, sourH,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			Render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(알파렌더-이미지잘라서붙이기)
			AlphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}