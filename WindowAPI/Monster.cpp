#include "stdafx.h"
#include "Monster.h"

HRESULT Monster::init()
{
	return S_OK;
}

HRESULT Monster::init(int xIndex, int yIndex)
{
	_x = xIndex * 96;
	_xIndex = xIndex;
	_y = yIndex * 96;
	_yIndex = yIndex;

	_level = 0;
	_frameX = 0;
	_frameY = 0;
	_frameTimer = 0;
	_frameDirection = 1;
	_image = nullptr;
	_blockPlayer = false;
	_moveSpeed = 0;
	_isMove = true;
	_canCrushing = true;
	_isInteractable = false;
	_alpha = 255;
	_objectType = OBJECTTYPE::OT_MONSTER;

	return S_OK;
}

void Monster::release()
{
}

void Monster::update()
{
}

void Monster::render(HDC hdc)
{
}

void Monster::SetBody()
{
	if (_image != nullptr)
	{
		if (_image->getFrameHeight() != 0)
		{
			_body = RectMake(_x + 10, _y + 10, _image->getFrameWidth() * 0.75f, _image->getFrameHeight() * 0.75f);
		}

		else
		{
			_body = RectMake(_x + 10, _y + 10, _image->getHeight() * 0.75f, _image->getWidth() * 0.75f);
		}
	}
}

void Monster::DeathAnim()
{
	_alpha -= 15;
	if (_alpha < 0) _alpha = 0;
	if (_alpha == 0)
	{
		Death();
	}
}

void Monster::Death()
{
	GRIDMANAGER->GetPlayer()->SetTarget(nullptr);
	GRIDMANAGER->GetField(_xIndex, _yIndex)->SetFieldObject(nullptr);

	for (int i = 0; i < GRIDMANAGER->GetObjects().size(); i++)
	{
		if (GRIDMANAGER->GetObjects()[i] == this)
		{
			GRIDMANAGER->GetObjects().erase(GRIDMANAGER->GetObjects().begin() + i);
			return;
		}
	}
}

void Monster::Move()
{

	bool isMoved = false;
	if (_isMove)
	{
		if (_moveSpeed == 0)
		{

		}

		else
		{

		}
	}
}

bool Monster::Interaction()
{
	return false;
}

void Monster::Animation()
{
}

