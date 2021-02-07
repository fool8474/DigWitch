#include "stdafx.h"
#include "Plant.h"

HRESULT Plant::init()
{
	return S_OK;
}

HRESULT Plant::init(int xIndex, int yIndex)
{
	_objectType = OT_PLANT;
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

	_image = nullptr;
	_isDeath = false;
	_blockPlayer = true;

	return S_OK;
}

void Plant::release()
{
}

void Plant::update()
{
	Restore();
}

void Plant::render(HDC hdc)
{
	CAMERAMANAGER->frameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha);
	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

bool Plant::Interaction()
{
	_hp -= GRIDMANAGER->GetPlayer()->GetDamage();

	PARTICLEMANAGER->AddGenerator(
		PARTICLETYPE::PT_OPEN, 50, 50, 0, 0, 3, 3, 1, 1, 0, PI * 2, 0, 0, 5, 255, 25, 10, vector<string>{"PARTICLE_Leave1", "PARTICLE_Leave2", "PARTICLE_Leave3", "PARTICLE_Leave4", "PARTICLE_Leave5", "PARTICLE_Leave6"},
		GENERATETYPE::ONETIME, _x + 20, _y + 20, 1, 50, 1
	);

	if (_hp < 0)
	{
		_hp = 0;
		_isDeath = true;
		GRIDMANAGER->GetPlayer()->SetTarget(nullptr);
		GRIDMANAGER->GetField(_xIndex, _yIndex)->SetFieldObject(nullptr);

		int numOfItem = _itemCount + RANDOM->range(_itemRandom);
		for (int i = 0; i < numOfItem; i++)
		{
			UIImage* img = new UIImage();
			img->init(_item->GetName(), CAMERAMANAGER->getRelativeX(_x) + RANDOM->range(-100, 100), CAMERAMANAGER->getRelativeY(_y) + RANDOM->range(-100, 100), _item->GetImage()->getFrameWidth(), _item->GetImage()->getFrameHeight(), _item->GetImageName(), true, _item->GetFrameX(), _item->GetFrameY());
			img->SetIsViewing(true);
			UIMANAGER->_vItemToBag.push_back(img);
		}
		
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

void Plant::SetBody()
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

void Plant::Restore()
{
	if (GRIDMANAGER->GetPlayer()->GetState() != PLAYERSTATE::GATHERING)
	{
		_hp += 5;
		if (_hp > _initHp) _hp = _initHp;
		_alpha = 255 * (_hp / (float)_initHp);
	}
}
