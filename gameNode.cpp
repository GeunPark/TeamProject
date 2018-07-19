#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## 초기화 ## Init(void)
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
		SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화
		KEYMANAGER->Init();					//키매니저 초기화
		RND->Init();						//랜덤펑션 초기화
		IMAGEMANAGER->Init();				//이미지매니저 초기화

	}
	return S_OK;
}

//=============================================================
//	## 해제 ## Release(void)
//=============================================================
void gameNode::Release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);

		//키매니저 해제
		KEYMANAGER->Release();
		KEYMANAGER->ReleaseSingleton();

		//랜덤펑션 싱클톤 해제
		RND->Release();
		RND->ReleaseSingleton();

		//이미지매니저 싱글톤 해제
		IMAGEMANAGER->Release();
		IMAGEMANAGER->ReleaseSingleton();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## 업데이트 ## Update(void)
//=============================================================
void gameNode::Update(void)
{
	//새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	InvalidateRect(_hWnd, NULL, FALSE);
}

//=============================================================
//	## 렌더 ## Render(void)
//=============================================================
void gameNode::Render(void)
{

}

//=============================================================
//	## 메인프로시져 ## 
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//핸들DC 
	PAINTSTRUCT ps; //페인트구조체

	switch (iMessage)
	{
	case WM_TIMER:
		this->Update();
		break;

	case WM_PAINT:	//출력에 관한 모든것을 담당한다(문자, 그림, 도형등등 화면에 보이는 모든것)
		hdc = BeginPaint(hWnd, &ps);
		this->Render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		
		break;
	
	case WM_KEYDOWN: //키보드 키가 눌렸을때 메세지 발생
		switch (wParam)
		{
		case VK_ESCAPE:		//esc 키를 누르면 화면종료
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		//소멸자
		PostQuitMessage(0);
		return 0;
	}

	//윈도우 프로시져에서 처리되지 않은 나머지 메세지를 처리해준다
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	return LRESULT();
}
