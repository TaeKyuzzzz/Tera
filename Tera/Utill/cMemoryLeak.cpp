#include "stdafx.h"
#include "cMemoryLeak.h"



cMemoryLeak::cMemoryLeak()
{
}


cMemoryLeak::~cMemoryLeak()
{
}


HRESULT cMemoryLeak::init()
{
	//�޸� ������ Ž���ϱ� ���� �÷��� ������� �ؾ���
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int* test = new int[100];
	//int* test = new int[100];

	delete[] test;

	//ã���� �˷��ش�
	_crtBreakAlloc;

	//�����޸� ���°� �������ش�
	_CrtDumpMemoryLeaks();

	return S_OK;
}

void cMemoryLeak::release()
{
}

