#include "stdafx.h"
#include "player.h"
#include "Inventory.h"
#include "Craft.h"

HRESULT player::init()
{
	_objectType = OBJECTTYPE::OT_PLAYER;
	_x = 0;
	_y = 96 * 100 / 2;
	_image = IMAGEMANAGER->findImage("Character");
	_frameX = 0;
	_frameY = 0;
	_state = PLAYERSTATE::IDLE;
	_frameTimer = 0;
	_damage = 5;

	_body = RectMake(_x + 20, _y + 30, 50, 60);

	_isInteractable = false;

	_alpha = 255;
	_isDeath = false;
	_staffLevel = 0;
	_canCrushing = true;
	_money = 0;
	_mp = 50;

	_inven = new Inventory();
	_inven ->init();

	_inven->SetPlayer(this);
	
	_useCheat = false;
	_craft = new Craft();
	_craft->init();
	_craft->SetInventory(_inven);

	return S_OK;
}

void player::release()
{

}

void player::update()
{
	if (_isDeath && !_useCheat)
	{
		DeathAnim();
	}

	else
	{
		int xIndex = _xIndex;
		int yIndex = _yIndex;

		switch (_state)
		{
		case IDLE:
			Move();
			break;
		case GATHERING:
			if (INPUT->GetKeyDown(VK_SPACE)) ChangeState(PLAYERSTATE::IDLE);
			if (_target == nullptr || _target->Interaction()) ChangeState(PLAYERSTATE::IDLE);
			break;
		case SKILL:
			break;
		case DEATH:
			break;
		}

		Animation();

		_body = RectMake(_x + 20, _y + 30, 50, 60);

		_xIndex = _x / 96;
		_yIndex = _y / 96;

		if (_xIndex != xIndex || _yIndex != yIndex)
		{
			GRIDMANAGER->GetField(_xIndex, _yIndex)->SetBuildedRoad(true);
			CAMERAMANAGER->movePivot(_x, _y);

			GRIDMANAGER->GetField(_xIndex, _yIndex)->DrawRoad();
			if (_xIndex > 0) GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->DrawRoad();
			if (_xIndex < GRIDMANAGER->GetCurLine() - 1) GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->DrawRoad();
			if (_yIndex > 0) GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->DrawRoad();
			if (_yIndex < FIELDSIZEY - 1) GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->DrawRoad();
		}

	
		// ui
		_inven->update();
		_craft->update();
		SetUI();



	}
}

void player::SetUI()
{
	dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("stage"))->SetText("STAGE " + (to_string(_xIndex / FIELDLEVEL+ 1)));
	dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("m"))->SetText(to_string(_xIndex * 3) + "m");
	dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_money")->GetChild("moneyText"))->SetText(to_string(_money));
}

void player::Move()
{
	Object* obj;
	if (INPUT->GetKeyDown(VK_RIGHT))
	{
		if (_xIndex < GRIDMANAGER->GetCurLine() - 1)
		{
			if (CheckMoveOrInteract(_xIndex + 1, _yIndex) == false)
			{
				_x += 96;
				GRIDMANAGER->MoveToRight();
			}
		}
	}

	else if (INPUT->GetKeyDown(VK_UP))
	{
		if (_yIndex > 0)
		{
			if (CheckMoveOrInteract(_xIndex, _yIndex - 1) == false) _y -= 96;
		}
	}

	else if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (_yIndex < FIELDSIZEY - 1)
		{
			if (CheckMoveOrInteract(_xIndex, _yIndex + 1) == false) _y += 96;
		}
	}
}

bool player::CheckMoveOrInteract(int x, int y)
{
	Object* obj = GRIDMANAGER->GetField(x, y)->GetFieldObject();
	if (obj != nullptr)
	{
		if (obj->GetIsInteractable())
		{
			if ((obj->GetObjectType() == OBJECTTYPE::OT_TREE && obj->GetLevel() <= _staffLevel) || 
				obj->GetObjectType() != OBJECTTYPE::OT_TREE)
			{
				ChangeState(PLAYERSTATE::GATHERING);
				_target = GRIDMANAGER->GetField(x, y)->GetFieldObject();
				return true;
			}
		}

		if (obj->GetBlockPlayer() == false)
		{
			return false;
		}

		else
		{
			return true;
		}
	}
}

void player::ChangeState(PLAYERSTATE state)
{
	_frameX = 0;
	_frameY = 0;
	_frameTimer = 0;
	_frameDirection = 1;
	_state = state;
}

void player::render(HDC hdc)
{
	switch (_state)
	{
	case IDLE:
		IMAGEMANAGER->findImage("Character")->frameAlphaRender(hdc, CAMERAMANAGER->getDistanceX(), CAMERAMANAGER->getDistanceY(), _frameX, _frameY, _alpha);
		break;
	case GATHERING:
		IMAGEMANAGER->findImage("Character_Gather")->frameAlphaRender(hdc, CAMERAMANAGER->getDistanceX(), CAMERAMANAGER->getDistanceY() - 5, _frameX, _frameY, _alpha);
		break;
	case SKILL:
		break;
	case DEATH:
		break;
	default:
		break;
	}

	if (INPUT->GetKey(VK_BACK)) CAMERAMANAGER->Rectangle(hdc, _body);
}

void player::Animation()
{
	switch (_state)
	{
	case IDLE: break;
	case GATHERING:
		_frameTimer++;
		if (_frameTimer > 10)
		{
			_frameTimer = 0;
			_frameX += _frameDirection;
			if (_frameX == IMAGEMANAGER->findImage("Character_Gather")->getMaxFrameX() || _frameX == 0)
			{
				_frameDirection = -_frameDirection;
			}
		}
		break;
	case SKILL: break;
	case DEATH: break;
	}
}

void player::DeathAnim()
{
	_alpha -= 15;
	if (_alpha < 0) _alpha = 0;
	if (_alpha == 0)
	{
		Death();
	}
}

void player::Death()
{
	GRIDMANAGER->GetFieldVv().clear();
	GRIDMANAGER->GetObjects().clear();
	GRIDMANAGER->GetBullet().clear();
	GRIDMANAGER->SetCurLine(0);
	GRIDMANAGER->GetNewField();
	
	_x = 0;
	_y = 96 * 100 / 2;
	_frameX = 0;
	_frameY = 0;
	_state = PLAYERSTATE::IDLE;
	_frameTimer = 0;		
	_body = RectMake(_x + 20, _y + 30, 50, 60);
	_isDeath = false;
	_mp = 50;
	_alpha = 255;
}
