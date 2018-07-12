#pragma once
#pragma once
#include "cGameNode.h"
#include <crtdbg.h>

#define CTRDBG_MAP_ALLOC
#define new new (_CLIENT_BLOCK, __FILE__, __LINE__)

class cMemoryLeak
{
public:
	HRESULT init();
	void release();

	cMemoryLeak();
	~cMemoryLeak();
};


