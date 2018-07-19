#pragma once
#include "Image.h"

//����� �̹����� ���������� ����� �α�
static Image* _backBuffer = IMAGEMANAGER->AddImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;			//ȭ�� HDC
	bool _managerInit;	//�Ŵ��� �ʱ�ȭ �߳�?

public:
	virtual HRESULT Init(void);
	virtual HRESULT Init(bool managerInit);
	virtual	void Release(void);
	virtual	void Update(void);
	virtual	void Render(void);

	//����� �̹��� ���
	Image* GetBackBuffer(void) { return _backBuffer; }

	//�޸� DC ���
	HDC GetMemDC() { return _backBuffer->GetMemDC(); }

	//HDC ��� (ȭ��DC)
	HDC GetHDC() { return _hdc; }


	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}	// �Ҹ��ڿ� virtual Ű���带 ���̴� ���� ������ �ܰ� ����
};

