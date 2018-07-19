#pragma once
#include "gameNode.h"



class mainGame : public gameNode
{
private:
	char A;
	bool ssw;


	int hoon;

	float speed;
	

	int jgh;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	mainGame() {}
	~mainGame() {}
};


