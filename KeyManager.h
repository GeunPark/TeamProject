#pragma once
#include "SingletonBase.h"

#define KEYMAX 256

class KeyManager : public SingletonBase <KeyManager>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

public:
	//Ű�Ŵ��� �ʱ�ȭ
	HRESULT Init();
	//Ű�Ŵ��� ����
	void Release();

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ������ �������?
	bool isOnceKeyUp(int key);
	//Ű�� ��� �������ֳ�?
	bool isStayKeyDown(int key);
	//���Ű��?
	bool isToggleKey(int key);

	KeyManager() {}
	~KeyManager() {}
};

