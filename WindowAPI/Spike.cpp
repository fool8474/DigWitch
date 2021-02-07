#include "stdafx.h"
#include "Spike.h"

HRESULT Spike::init()
{
	return S_OK;
}

HRESULT Spike::init(int xIndex, int yIndex)
{
	Monster::init(xIndex, yIndex);
	_monsterType = MONSTERTYPE::MT_TOTEM;
	_image = IMAGEMANAGER->findImage("Monster_Spike");
	_fireTimer = 30;

	return S_OK;
}

void Spike::release()
{
}

void Spike::update()
{
	if (_isDeath) DeathAnim();
	else
	{
		Move();
		OnOff();
		Animation();
		CollisionCheck();

		_xIndex = _x / 96;
		_yIndex = _y / 96;
	}
}

void Spike::OnOff()
{
	_fireTimer--;
	if (_fireTimer <= 0)
	{
		_isAttacking = !_isAttacking;
		_fireTimer = 50;
	}
}

void Spike::CollisionCheck()
{
	RECT temp;
	player* p = GRIDMANAGER->GetPlayer();

	if (_isAttacking)
	{
		if (IntersectRect(&temp, &p->GetBody(), &_body))
		{
			p->SetDeath();
			SetDeath();
			return;
		}
	}
}

void Spike::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _isAttacking ? 1 : 0, 0, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}


bool Spike::Interaction()
{
	return false;
}

void Spike::Animation()
{
}
