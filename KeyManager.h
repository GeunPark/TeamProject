#pragma once
#include "SingletonBase.h"

#define KEYMAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	//키매니저 초기화
	HRESULT Init();
	//키매니저 해제
	void Release();

	//키가 한번만 눌렸냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렀다 띄어졌냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌려져있냐?
	bool isStayKeyDown(int key);
	//토글키냐?
	bool isToggleKey(int key);

	KeyManager() {}
	~KeyManager() {}
};

