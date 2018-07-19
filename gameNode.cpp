#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## Init(void)
//=============================================================
HRESULT gameNode::Init(void)
{
	return S_OK;
}

HRESULT gameNode::Init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);		//Ÿ�̸� �ʱ�ȭ
		KEYMANAGER->Init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->Init();						//������� �ʱ�ȭ
		IMAGEMANAGER->Init();				//�̹����Ŵ��� �ʱ�ȭ

	}
	return S_OK;
}

//=============================================================
//	## ���� ## Release(void)
//=============================================================
void gameNode::Release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);

		//Ű�Ŵ��� ����
		KEYMANAGER->Release();
		KEYMANAGER->ReleaseSingleton();

		//������� ��Ŭ�� ����
		RND->Release();
		RND->ReleaseSingleton();

		//�̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->Release();
		IMAGEMANAGER->ReleaseSingleton();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## ������Ʈ ## Update(void)
//=============================================================
void gameNode::Update(void)
{
	//���ΰ�ħ (���߿� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� �ʴ´�)
	//������۸� ���� ������� �ʴ´� (true => false)
	InvalidateRect(_hWnd, NULL, FALSE);
}

//=============================================================
//	## ���� ## Render(void)
//=============================================================
void gameNode::Render(void)
{

}

//=============================================================
//	## �������ν��� ## 
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//�ڵ�DC 
	PAINTSTRUCT ps; //����Ʈ����ü

	switch (iMessage)
	{
	case WM_TIMER:
		this->Update();
		break;

	case WM_PAINT:	//��¿� ���� ������ ����Ѵ�(����, �׸�, ������� ȭ�鿡 ���̴� ����)
		hdc = BeginPaint(hWnd, &ps);
		this->Render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		
		break;
	
	case WM_KEYDOWN: //Ű���� Ű�� �������� �޼��� �߻�
		switch (wParam)
		{
		case VK_ESCAPE:		//esc Ű�� ������ ȭ������
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		//�Ҹ���
		PostQuitMessage(0);
		return 0;
	}

	//������ ���ν������� ó������ ���� ������ �޼����� ó�����ش�
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	return LRESULT();
}
