#pragma once
//============================================================================================================================================
// ## image ## (������ ��� ������Ʈ �ȴ�.)
//============================================================================================================================================
#define MAGENTA	RGB(255, 0, 255)

class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//���ҽ��� �ε�
		LOAD_FILE,				//���Ϸ� �ε�
		LOAD_EMPTY,				//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		redID;					//���ҽ� ID
		HDC			hMemDC;					//�޸� DC
		HBITMAP		hBit;					//��Ʈ��
		HBITMAP		hOBit;					//�õ��Ʈ��
		float		x;						//�̹��� x��ǥ
		float		y;						//�̹��� y��ǥ
		int			width;					//�̹��� ����ũ��
		int			height;					//�̹��� ����ũ��
		int			currentFrameX;			//���� ������ X
		int			currentFrameY;			//���� ������ Y
		int			maxFrameX;				//�ִ� X ������ ����
		int			maxFrameY;				//�ִ� Y ������ ����
		int			frameWidth;				//1�������� ���α���
		int			frameHeight;			//1�������� ���α���
		BYTE		loadType;				//�̹��� �ε�Ÿ��

		tagImage()	//������ = �ʱ�ȭ
		{
			redID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO		_imageInfo;		//�̹��� ����
	CHAR*				_fileName;		//�̹��� �̸�
	BOOL				_isTrans;		//���� ���ٰų�? (����Ÿ)
	COLORREF			_transColor;	//���� ���� RGB (����Ÿ = RGB(255, 0, 255))

	LPIMAGE_INFO		_blendImage;	//���ĺ��� �̹���
	BLENDFUNCTION		_blendFunc;		//���ĺ��� ���

public:
	Image();
	~Image();

	//�� ��Ʈ������ �ʱ�ȭ
	HRESULT Init(int width, int height);
	//�̹��� ���ҽ��� �ʱ�ȭ (������)
	HRESULT Init(DWORD resID, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//�̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT Init(const char* fileName, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT Init(const char* fileName, float x, float y, int width, int height, bool isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//������ �̹��� ���Ϸ� �ʱ�ȭ (�ֻ��)
	HRESULT Init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);
	HRESULT Init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = TRUE, COLORREF transColor = MAGENTA);


	//���ĺ��� �ʱ�ȭ
	HRESULT InitForAlphaBlend(void);




	//����
	void Release(void);


	//============================================================================================================================================
	// ## �Ϲ� ���� ##
	//============================================================================================================================================

	void Render(HDC hdc, int destX = 0, int destY = 0);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH);

	//============================================================================================================================================
	// ## ���ķ��� ##
	//============================================================================================================================================
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH, BYTE alpha);
	//============================================================================================================================================
	// ## �����ӷ��� ##
	//============================================================================================================================================
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void FrameRender(HDC hdc, int destX, int destY, int sourW, int sourH, int currentFrameX, int currentFrameY);
	//=============================================================
	//	## �������� ##
	//=============================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	//============================================================================================================================================
	// ## inline ## ( �ζ��� �Լ��� - ����, ���� )
	//===========================================================================================================================================
	//DC ���
	inline HDC GetMemDC(void) { return _imageInfo->hMemDC; }

	//�̹��� x ��ǥ
	inline float GetX(void) { return _imageInfo->x; }
	inline void SetX(float x) { _imageInfo->x = x; }

	//�̹��� y ��ǥ
	inline float GetY(void) { return _imageInfo->y; }
	inline void SetY(float y) { _imageInfo->y = y; }

	//�̹��� ���� ��ǥ
	inline void SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//�̹��� ����, ���� ũ��
	inline int GetWidth(void) { return _imageInfo->width; }
	inline int GetHeight(void) { return _imageInfo->height; }

	//�ٿ�� �ڽ�(�浹�� ��Ʈ)
	inline RECT boudingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
		(int)_imageInfo->x + _imageInfo->width,
		(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}
	inline RECT boudingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//������ x
	inline int GetFrameX(void) { return _imageInfo->currentFrameX; }
	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ y
	inline int GetFrameY(void) { return _imageInfo->currentFrameY; }
	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//�̹��� ���������� ����, ���� ũ��
	inline int GetFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int GetFrameHeight(void) { return _imageInfo->frameHeight; }

	//�ƽ� ������ x, y
	inline int GetMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int GetmaxFrameY(void) { return _imageInfo->maxFrameY; }
};