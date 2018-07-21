#include "stdafx.h"
#include "cDeviceManager.h"


cDeviceManager::cDeviceManager()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION); // sdk ������ ���ڷ� ����  <- D3D ��ü ����
											   // ���̷�Ʈ �������̽��� �����ϴ� �Լ��� ���ڷ� sdk�� ������ �Ѱ��ش�. ( ��� �̷������� ���� )


											   // �ϵ��� �����ϴ��� Ȯ���ϴ� �۾��� �������
	D3DCAPS9  stCaps;// �ϵ������ ������ ���� �� �ִ� ����ü
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps); // stCaps �� �ϵ� ������ ����

	int nVertaxProcessing;
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// ����̽� ĸ�� ���� D3DDEVCAPS_HWTRANSFORMANDLIGHT �� ��Ʈ������ �Ǹ� ( Ʈ������, ����Ʈ ����� ������ �ָ�
		nVertaxProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}
	else
	{
		nVertaxProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}

	// �츮�� ������� �ϴ� ����̽��� �Ӽ��� �����ϴµ� ���ȴ�.
	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	// ���� ����Ʈ�� ���� ȿ������ ����
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;				// �ø��� ü���� ��ȯ�Ǵ� ����� ����
	stD3DPP.Windowed = true;								// â���� ��﷡ ��üȭ������ ��﷡
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;				// �������� ũ�� ����
	stD3DPP.EnableAutoDepthStencil = true;					// ���Ľ�? ���� ��� ����
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;			// ���� ( �� ũ�⸦ ����)

	m_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,		// ���
		D3DDEVTYPE_HAL,			// ����̽� Ÿ��
		g_hWnd,						// ���� �ڵ�
		nVertaxProcessing,		// �÷���
		&stD3DPP,				// ����̽��� �Ӽ�
		&m_pD3DDevice			// ������ ����̽� ������Ʈ�� �����Ͱ� ���ϵż� ���⿡ ��
	);
}


cDeviceManager::~cDeviceManager()
{

}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void cDeviceManager::Destroy()
{
	int a = 10;
	ULONG ul = m_pD3DDevice->Release(); // ����̽��� ������� ���۷��� ī��Ʈ�� ��ȯ�Ѵ�.
	//assert(ul == 0 && "����̽��� �̿��� ������ ��ü �߿� �������� ���� ��ü�� �ֽ��ϴ�.");

	m_pD3D->Release();			//
}