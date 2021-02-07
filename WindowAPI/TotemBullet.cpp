#include "stdafx.h"
#include "TotemBullet.h"
#include "Totem.h"
#include "player.h"

HRESULT TotemBullet::init()
{
	Object::init();
	_isFire = false;

	return S_OK;
}

HRESULT TotemBullet::init(int x, int y)
{
	_x = x;
	_y = y;
	_isFire = false;
	_xIndex = x / 96;
	_yIndex = y / 96;
	_frameX = 0;
	_frameY = 0;
	_frameTimer = 0;
	_frameDirection = 1;

	_canCrushing = true;
	_isMove = true;
	_isInteractable = false;

	_alpha = 255;
	_moveSpeed = 10;
	_image = IMAGEMANAGER->findImage("Bullet_Totem");

	_objectType = OT_BULLET;

	return S_OK;
}

void TotemBullet::release()
{
}

void TotemBullet::update()
{
	if (_isDeath) DeathAnim();
	else
	{
		Animation();
		Move();
		SetBody();
		CollisionCheck();

		_xIndex = _x / 96;
		_yIndex = _y / 96;
	}
}

void TotemBullet::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

void TotemBullet::Move()
{
	if (_isFire)
	{
		switch (_dir)
		{
		case DIRECTION::DR_U:
			_y -= _moveSpeed;
			break;

		case DIRECTION::DR_D:
			_y += _moveSpeed;
			break;

		case DIRECTION::DR_L:
			_x -= _moveSpeed;
			break;

		case DIRECTION::DR_R:
			_x += _moveSpeed;
			break;
		}
	}
}

bool TotemBullet::Interaction()
{
	return false;
}

void TotemBullet::SetBody()
{
	if (_image != nullptr)
	{
		_body = RectMake(_x + 15, _y + 15, _image->getFrameWidth() * 0.5f, _image->getFrameHeight() * 0.5f);
	}
}

void TotemBullet::Animation()
{
	if (!_isFire)
	{
		_frameTimer++;
		if (_frameTimer == 4)
		{
			_frameX++;
			if (_frameX == _image->getMaxFrameX())
			{
				_isFire = true;
			}

			_frameTimer = 0;
		}
	}
}

void TotemBullet::CollisionCheck()
{
	if (_isFire)
	{
		if (_x < 0 || _x > GRIDMANAGER->GetCurLine() * 96 || _y < 0 || _y > FIELDSIZEY * 96)
		{
			SetDeath();
			return;
		}
		
		RECT temp;
		player* p = GRIDMANAGER->GetPlayer();

		if (IntersectRect(&temp, &p->GetBody(), &_body))
		{
			p->SetDeath();
			SetDeath();
			return;
		}

		Object* obj = GRIDMANAGER->GetField(_xIndex, _yIndex)->GetFieldObject();
		if (obj != nullptr && obj != _parent && !obj->GetIsDeath())
		{
			if (IntersectRect(&temp, &_body, &obj->GetBody()))
			{
				if (obj->GetObjectType() == OBJECTTYPE::OT_MONSTER)
				{
					obj->SetDeath();
				}

				SetDeath();
				return;
			}
		}
	}
}

void TotemBullet::DeathAnim()
{
	_frameTimer++;
	if (_frameTimer == 4)
	{
		_frameX--;
		if (_frameX == 0)
		{
			Death();
		}

		_frameTimer = 0;
	}
}

void TotemBullet::Death()
{
	ReleaseBullet();
}

void TotemBullet::ReleaseBullet()
{
	_parent->SetBullet(nullptr);
	_parent = nullptr;

	for (int i = 0; i < GRIDMANAGER->GetBullet().size(); i++)
	{
		if (GRIDMANAGER->GetBullet()[i] == this)
		{
			GRIDMANAGER->GetBullet().erase(GRIDMANAGER->GetBullet().begin() + i);
			break;
		}
	}
}
