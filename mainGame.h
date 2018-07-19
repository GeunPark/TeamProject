#pragma once
#include "gameNode.h"



class mainGame : public gameNode
{
private:
	char A;
	
public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	mainGame() {}
	~mainGame() {}
};

