#include "stdafx.h"
#include "ProgressBar.h"
#include "player.h"
#include "Plant.h"

HRESULT ProgressBar::init()
{
	img = IMAGEMANAGER->findImage("UI_ProgressBar");
	imgBack = IMAGEMANAGER->findImage("UI_ProgressBarBack");

	return S_OK;
}

void ProgressBar::render(HDC hdc)
{
	if (_p->GetState() == PLAYERSTATE::GATHERING)
	{
		Plant* target = dynamic_cast<Plant*>(_p->GetTarget());
		imgBack->render(hdc, 650, 800);
		img->render(hdc, 650, 800, 0, 0, img->getWidth() - (target->GetHp() / (float)target->GetInitHp()) * img->getWidth(), img->getHeight());
	}
}

