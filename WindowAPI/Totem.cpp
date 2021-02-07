#include "stdafx.h"
#include "Totem.h"

HRESULT Totem::init()
{
	return S_OK;
}

HRESULT Totem::init(int xIndex, int yIndex)
{
	Monster::init(xIndex, yIndex);
	_monsterType = MONSTERTYPE::MT_TOTEM;
	_image = IMAGEMANAGER->findImage("Monster_Totem");
	_fireTimer = 30;
	_blockPlayer = true;

	return S_OK;
}

void Totem::release()
{
}

void Totem::update()
{
	if (_isDeath) DeathAnim();
	else
	{
		Move();
		Fire();
		Animation();

		_xIndex = _x / 96;
		_yIndex = _y / 96;
	}
}

void Totem::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

void Totem::Fire()
{
	if (_bullet == nullptr)
	{
		_fireTimer--;
		if (_fireTimer < 0)
		{
			_bullet = new TotemBullet();
			switch (_dir)
			{
				case DIRECTION::DR_D : _bullet->init(_x + 19, _y + 50); break;
				case DIRECTION::DR_U : _bullet->init(_x + 20, _y - 40); break;
				case DIRECTION::DR_R : _bullet->init(_x + 55, _y + 40); break;
				case DIRECTION::DR_L : _bullet->init(_x - 25, _y + 40); break;
			}
			_bullet->SetBody();
			_bullet->SetParent(this);
			_bullet->SetDirection(_dir);

			GRIDMANAGER->GetBullet().push_back(_bullet);
			_fireTimer = RANDOM->range(20, 50);
		}
	}
}

bool Totem::Interaction()
{
	return false;
}

void Totem::Animation()
{
}
