#pragma once
#include "gameNode.h"



class mainGame : public gameNode
{
private:
	char A;
	bool ssw;


	int hoon;

	float speed;
	
	int hwa;
	int jgh;

	int x;

public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	mainGame() {}
	~mainGame() {}
};


