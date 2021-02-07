#include "stdafx.h"
#include "Dino.h"

HRESULT Dino::init()
{
	return S_OK;
}

HRESULT Dino::init(int xIndex, int yIndex)
{
	Monster::init(xIndex, yIndex);
	_monsterType = MONSTERTYPE::MT_SPIDER;
	_image = IMAGEMANAGER->findImage("Monster_Dino");
	_moveTargetY = 0;

	return S_OK;
}

void Dino::release()
{
}

void Dino::update()
{
	if (_isDeath) DeathAnim();
	else
	{
		int _prevXIndex = _x / 96;
		int _prevYIndex = _y / 96;

		Move();
		Animation();
		CollisionCheck();

		_xIndex = _x / 96;
		_yIndex = _y / 96;
		if (_xIndex != _prevXIndex || _yIndex != _prevYIndex)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetFieldObject(this);
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetReservObject(nullptr);
			GRIDMANAGER->GetField(_prevXIndex, _prevYIndex)->SetFieldObject(nullptr);
		}

		Monster::SetBody();
	}
}

void Dino::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

void Dino::Move()
{
	if (_moveSpeed == 0)
	{
		if (_yIndex > 0
			&& (GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetBuildedRoad()
			)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->SetReservObject(this);
			_moveSpeed = -5;
			_moveTargetY = (_yIndex - 1) * 96 + 15;
		}

		else if (_yIndex < FIELDSIZEY - 1
			&& (GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetBuildedRoad())
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->SetReservObject(this);
			_moveSpeed = 5;
			_moveTargetY = (_yIndex + 1) * 96;
		}
	}

	else if ((_moveSpeed > 0 && _y >= _moveTargetY) || (_moveSpeed < 0 && _y <= _moveTargetY))
	{
		int n = checkMoveContinue();
		if (n == 0)
		{
			_moveSpeed = 0;
		}

		else if (n == 1)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->SetReservObject(this);
			_moveSpeed = -5;
			_moveTargetY = (_yIndex - 1) * 96 + 15;
		}

		else if (n == 2)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->SetReservObject(this);
			_moveSpeed = 5;
			_moveTargetY = (_yIndex + 1) * 96;
		}
	}

	else
	{
		_y += _moveSpeed;
	}
}

int Dino::checkMoveContinue()
{
	if (_moveSpeed < 0)
	{
		if (_yIndex > 0
			&& (GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetBuildedRoad()
			)
			return 1;
	}
	if (_moveSpeed > 0)
	{
		if (_yIndex < FIELDSIZEY - 1
			&& (GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetBuildedRoad()
			)
			return 2;
	}
	return 0;
}


void Dino::CollisionCheck()
{
	RECT temp;
	player* p = GRIDMANAGER->GetPlayer();

	if (IntersectRect(&temp, &p->GetBody(), &_body))
	{
		p->SetDeath();
		SetDeath();
		return;
	}
}

bool Dino::Interaction()
{
	return false;
}

void Dino::Animation()
{
	if (_moveSpeed != 0)
	{
		_frameTimer++;
		if (_frameTimer == 10)
		{
			_frameTimer = 0;
			_frameX = _frameX == 0 ? 1 : 0;
		}
	}
}
