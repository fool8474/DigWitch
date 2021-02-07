#include "stdafx.h"
#include "Rock.h"

HRESULT Rock::init()
{
	return S_OK;
}

HRESULT Rock::init(int xIndex, int yIndex)
{
	_objectType = OBJECTTYPE::OT_ROCK;
	_x = xIndex * 96;
	_y = yIndex * 96;
	_xIndex = xIndex;
	_yIndex = yIndex;

	_frameDirection = 1;
	_frameTimer = 0;
	_frameX = 0;
	_frameY = 0;

	_alpha = 255;
	_moveSpeed = 0;

	_image = nullptr;

	return S_OK;
}

void Rock::release()
{
}

void Rock::Move()
{
	bool isMoved = false;
	if (_isMove)
	{
		if (_moveSpeed == 0)
		{
			if (_xIndex < GRIDMANAGER->GetCurLine() - 1)
			{
				Field* field = GRIDMANAGER->GetField(_xIndex + 1, _yIndex);
				if ((field->GetReservObject() == nullptr || (field->GetReservObject() != nullptr && field->GetReservObject()->GetObjectType() == OBJECTTYPE::OT_MONSTER)
					|| field->GetReservObject() == this)
					&& (field->GetFieldObject() == nullptr || (field->GetFieldObject() != nullptr && field->GetFieldObject()->GetObjectType() == OBJECTTYPE::OT_MONSTER))
					&& field->GetBuildedRoad())
				{
					field->SetReservObject(this);
					_moveSpeed = 4;
					_moveRow = true;
				}
			}

			if (_yIndex < FIELDSIZEY - 1)
			{
				Field* field = GRIDMANAGER->GetField(_xIndex, _yIndex + 1);
				if ((field->GetReservObject() == nullptr || (field->GetReservObject() != nullptr && field->GetReservObject()->GetObjectType() == OBJECTTYPE::OT_MONSTER)
					|| field->GetReservObject() == this)
					&& (field->GetFieldObject() == nullptr || (field->GetFieldObject() != nullptr && field->GetFieldObject()->GetObjectType() == OBJECTTYPE::OT_MONSTER))
					&& field->GetBuildedRoad())
				{

					GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->SetReservObject(this);
					_moveSpeed = 4;
					_moveRow = false;
				}
			}
		}

		else
		{
			if (_moveRow) _x += _moveSpeed;
			else _y += _moveSpeed;
		}
	}
}

void Rock::Animation()
{
	if (_isMove)
	{
		if (_moveSpeed != 0)
		{
			_frameTimer += 1;
			if (_frameTimer == 2)
			{
				_frameTimer = 0;
				_frameX += 1;
				if (_frameX > _image->getMaxFrameX()) _frameX = 1;
			}
		}
	}
}

void Rock::Crush()
{
	RECT temp;
	player* p = GRIDMANAGER->GetPlayer();

	if (IntersectRect(&temp, &p->GetBody(), &_body))
	{
		p->SetDeath();
		SetDeath();

		PARTICLEMANAGER->AddGenerator(
			PARTICLETYPE::PT_OPEN, 25, 25, 0, 0, 3, 3, 1, 1, 0, PI * 2, 0, 0, 3, 255, 30, 10, 
			vector<string>{"PARTICLE_Stone1", "PARTICLE_Stone2", "PARTICLE_Stone3", "PARTICLE_Stone4"},
			GENERATETYPE::ONETIME, _x + 48, _y + 48, 5, 30, 15
		);

		return;
	}

	Object* obj = GRIDMANAGER->GetField(_xIndex, _yIndex)->GetFieldObject();
	if (obj != nullptr && !obj->GetIsDeath() && obj->GetObjectType() == OBJECTTYPE::OT_MONSTER)
	{
		obj->SetDeath();
		this->SetDeath();

		PARTICLEMANAGER->AddGenerator(
			PARTICLETYPE::PT_OPEN, 25, 25, 0, 0, 3, 3, 1, 1, 0, PI * 2, 0, 0, 3, 255, 30, 10, vector<string>{"PARTICLE_Stone1", "PARTICLE_Stone2", "PARTICLE_Stone3", "PARTICLE_Stone4"},
			GENERATETYPE::ONETIME, _x + 48, _y + 48, 5, 30, 15
		);

		return;
	}
}

void Rock::update()
{
	if (_isDeath)
	{
		DeathAnim();
	}
	else
	{
		int _prevXIndex = _x / 96;
		int _prevYIndex = _y / 96;

		Move();
		Animation();

		_xIndex = _x / 96;
		_yIndex = _y / 96;
		Crush();

		if (_xIndex != _prevXIndex || _yIndex != _prevYIndex)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetFieldObject(this);
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetReservObject(nullptr);
			GRIDMANAGER->GetField(_prevXIndex, _prevYIndex)->SetFieldObject(nullptr);
			_moveSpeed = 0;
		}

		SetBody();
	}
}

void Rock::DeathAnim()
{
	_alpha -= 15;
	if (_alpha < 0) _alpha = 0;
	if (_alpha == 0)
	{
		Death();
	}
}

void Rock::Death()
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

void Rock::SetBody()
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

void Rock::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);

	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

bool Rock::Interaction()
{
	return false;
}
