#pragma once
#include "Object.h"

enum PLAYERSTATE {
	IDLE, GATHERING, SKILL, DEATH
};

class Craft;
class Inventory;
class player : public Object
{
private:

	PLAYERSTATE	_state;

	Object*		_target;

	int			_mp;
	int			_money;
	float		_damage;

	int			_staffLevel;
	Inventory*	_inven;
	Craft*		_craft;
	bool		_useCheat;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	int			GetMoney()		{ return _money; }
	PLAYERSTATE GetState()		{ return _state; }
	float		GetDamage()		{ return _damage; }
	Object*		GetTarget()		{ return _target; }
	int			GetStaffLevel() { return _staffLevel; }
	Inventory*	GetInven()		{ return _inven; }
	Craft*		GetCraft()		{ return _craft; }

	void SetMoney(int money)		{ _money = money; }
	void SetTarget(Object* target)	{ _target = target; }
	void SetStaffLevel(int level)	{ _staffLevel = level; }
	void SetInven(Inventory* inven) { _inven = inven; }

	void SetUI();

	void Move();
	bool CheckMoveOrInteract(int x, int y);
	void ChangeState(PLAYERSTATE state);
	void Animation();
	virtual void DeathAnim();
	virtual void Death();

	player() {}
	~player() {}
};

