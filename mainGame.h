#pragma once
#include "gameNode.h"



class mainGame : public gameNode
{
private:
	char A;
	bool ssw;
<<<<<<< HEAD

	float speed;
	
=======
	int jgh;
>>>>>>> f4e956ab6001c25d504c1f4df8b358d0f3a98ef7
public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	mainGame() {}
	~mainGame() {}
};

