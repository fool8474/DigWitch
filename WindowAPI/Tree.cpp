#include "stdafx.h"
#include "Tree.h"

HRESULT Tree::init()
{
	return S_OK;
}

HRESULT Tree::init(int xIndex, int yIndex)
{
	_objectType = OBJECTTYPE::OT_TREE;
	_x = xIndex * 96;
	_y = yIndex * 96;
	_xIndex = xIndex;
	_yIndex = yIndex;

	_frameDirection = 1;
	_frameTimer = 0;
	_frameX = 0;
	_frameY = 0;

	_alpha = 255;
	_isMove = false;
	_moveSpeed = 0;
	_blockPlayer = true;
	_image = nullptr;

	return S_OK;
}

void Tree::release()
{
}

void Tree::update()
{
	Restore();
}

void Tree::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

bool Tree::Interaction()
{
	_hp -= GRIDMANAGER->GetPlayer()->GetDamage();
	if (_hp < 0)
	{
		_hp = 0;
		_isDeath = true;
		GRIDMANAGER->GetPlayer()->SetTarget(nullptr);
		GRIDMANAGER->GetField(_xIndex, _yIndex)->SetFieldObject(nullptr);

		for (int i = 0; i < GRIDMANAGER->GetObjects().size(); i++)
		{
			if (GRIDMANAGER->GetObjects()[i] == this)
			{
				GRIDMANAGER->GetObjects().erase(GRIDMANAGER->GetObjects().begin() + i);
				break;
			}
		}
		return true;
	}

	_alpha = 255 * (_hp / (float)_initHp);
	return false;
}

void Tree::Restore()
{
	if (GRIDMANAGER->GetPlayer()->GetState() != PLAYERSTATE::GATHERING)
	{
		_hp += 5;
		if (_hp > _initHp) _hp = _initHp;
		_alpha = 255 * (_hp / (float)_initHp);
	}
}

void Tree::SetBody()
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