#include "stdafx.h"
#include "Sasin.h"
#include "player.h"

HRESULT Sasin::init()
{
	return S_OK;
}

HRESULT Sasin::init(int xIndex, int yIndex)
{
	Monster::init(xIndex, yIndex);
	_monsterType = MONSTERTYPE::MT_SASIN;
	_image = IMAGEMANAGER->findImage("Monster_Sasin");
	_alpha = 0;
	return S_OK;
}

void Sasin::release()
{
}

void Sasin::update()
{
	if (_alpha < 255) {
		_alpha += 2;
		if (_alpha > 255) _alpha = 255;
	}

	else
	{
		Move();
		Animation();
		CollisionCheck();

		Monster::SetBody();
	}
}

void Sasin::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

void Sasin::Move()
{
	int xDis = abs(_p->GetX() - _x);
	int yDis = abs(_p->GetY() - _y);

	if (yDis < 10)
	{
		if(xDis < 4) xDis = _p->GetX();

		else
		{
			if (_p->GetX() > _x)
			{
				_x += 2;
			}

			else
			{
				_x -= 2;
			}
		}
	}

	else
	{
		if (_p->GetY() > _y)
		{
			_y += 4;
		}

		else
		{
			_y -= 4;
		}
	}
}

void Sasin::CollisionCheck()
{
	RECT temp;
	player* p = GRIDMANAGER->GetPlayer();

	if (IntersectRect(&temp, &p->GetBody(), &_body))
	{
		p->SetDeath();
		return;
	}
}

void Sasin::Animation()
{
	_frameTimer++;
	if (_frameTimer == 10)
	{
		_frameTimer = 0;
		_frameX = _frameX == 0 ? 1 : 0;
	}
}
