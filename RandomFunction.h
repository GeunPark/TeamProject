#pragma once
#include "SingletonBase.h"
#include <time.h>

//=============================================================
//	## RandomFuntion ## (·£´ýÆã¼Ç)
//=============================================================

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction() 
	{
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT Init() { return S_OK; }
	void Release() {}

	//GetInt
	inline int GetInt(int num) { return rand() % num; }
	//GetFromIntTo
	inline int GetFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};

