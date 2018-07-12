#include "stdafx.h"
#include "../cGameNode.h"
#include "cProgressBar.h"
#include "Sprite/cSprite.h"

cProgressBar::cProgressBar()
{
}


cProgressBar::~cProgressBar()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void cProgressBar::Setup(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	// ü�� �� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;
	// ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgress = RectMake(x, y, width, height);
	
	// ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = TEXTUREMANAGER->GetSprite(frontImage);
	//_progressBarFront->Init(frontImage, x, y, width, height, true, RGB(255, 0, 255));
	
	_progressBarBack = TEXTUREMANAGER->GetSprite(backImage);
	//_progressBarBack->Init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	// ���� ���� �ʱ�ȭ
	_width = _progressBarFront->textureInfo.Width;

}

void cProgressBar::Update()
{
	_rcProgress = RectMakeCenter(
		_x + _progressBarBack->textureInfo.Width / 2,
		_y + _progressBarBack->textureInfo.Height / 2,
		_progressBarBack->textureInfo.Width,
		_progressBarBack->textureInfo.Height);
}

void cProgressBar::Render()
{
	RECT rc;
	SetRect(&rc, 0, 0, _progressBarBack->textureInfo.Width, _progressBarBack->textureInfo.Height);
	_progressBarBack->Render(rc,D3DXVECTOR3(0,0,0),D3DXVECTOR3(_x,_y,0));
	
	SetRect(&rc, 0, 0, _width, _progressBarBack->textureInfo.Height);
	_progressBarFront->Render(rc, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(_x, _y, 0));

}

void cProgressBar::SetGauge(float currentGauge, float maxGauge)
{
	// ������ ������ ����
	_width = (currentGauge / maxGauge) * _progressBarBack->textureInfo.Width;
}
