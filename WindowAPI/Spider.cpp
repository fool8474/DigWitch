#include "stdafx.h"
#include "Spider.h"

HRESULT Spider::init()
{
	return S_OK;
}

HRESULT Spider::init(int xIndex, int yIndex)
{
	Monster::init(xIndex, yIndex);
	_monsterType = MONSTERTYPE::MT_SPIDER;
	_image = IMAGEMANAGER->findImage("Monster_Spider");
	_moveTargetX = 0;

	return S_OK;
}

void Spider::release()
{
}

void Spider::update()
{
	if (_isDeath) DeathAnim();
	else
	{
		int _prevXIndex = _x / 96;
		int _prevYIndex = _y / 96;

		Move();
		Animation();

		_xIndex = _x / 96;
		_yIndex = _y / 96;
		if (_xIndex != _prevXIndex || _yIndex != _prevYIndex)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetFieldObject(this);
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetReservObject(nullptr);
			GRIDMANAGER->GetField(_prevXIndex, _prevYIndex)->SetFieldObject(nullptr);
		}

		CollisionCheck();
		Monster::SetBody();
	}
}

void Spider::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

void Spider::Move()
{
	if (_moveSpeed == 0)
	{
		if (_xIndex > 0
			&& (GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetBuildedRoad()
			)
		{
			GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->SetReservObject(this);
			_moveSpeed = -5;
			_moveTargetX = (_xIndex - 1) * 96 + 15;
		}

		else if (_xIndex < GRIDMANAGER->GetCurLine() - 1
			&& (GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetBuildedRoad())
		{
			GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->SetReservObject(this);
			_moveSpeed = 5;
			_moveTargetX = (_xIndex + 1) * 96;
		}
	}

	else if ((_moveSpeed > 0 && _x >= _moveTargetX) || (_moveSpeed < 0 && _x <= _moveTargetX))
	{
		int n = checkMoveContinue();
		if (n == 0)
		{
			_moveSpeed = 0;
		}

		else if (n == 1)
		{
			GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->SetReservObject(this);
			_moveSpeed = -5;
			_moveTargetX = (_xIndex - 1) * 96 + 15;
		}

		else if (n == 2)
		{
			GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->SetReservObject(this);
			_moveSpeed = 5;
			_moveTargetX = (_xIndex + 1) * 96;
		}
	}

	else
	{
		_x += _moveSpeed;
	}
}

int Spider::checkMoveContinue()
{
	if (_moveSpeed < 0)
	{
		if (_xIndex > 0
			&& (GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetBuildedRoad()
			)
			return 1;
	}
	if (_moveSpeed > 0)
	{
		if (_xIndex < GRIDMANAGER->GetCurLine() - 1
			&& (GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetReservObject() == nullptr || GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetReservObject() == this)
			&& GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetFieldObject() == nullptr
			&& GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetBuildedRoad()
			)
			return 2;
	}
	return 0;
}

void Spider::CollisionCheck()
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

bool Spider::Interaction()
{
	return false;
}

void Spider::Animation()
{
	if (_moveSpeed < 0) _frameY = 0;
	else _frameY = 1;

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
