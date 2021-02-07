#pragma once
#include "Object.h"
class Rock : public Object
{
private:
	int _initHp;
	int _hp;
	bool _moveRow;

public:
	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual bool Interaction();
	virtual void Move();
	virtual void Animation();
	virtual void DeathAnim();
	virtual void Death();
	virtual void SetBody();
	void Crush();

	int GetHp() { return _hp; }
	int GetInitHp() { return _initHp; }
	
	void SetHp(int hp) { _hp = hp; }
	void SetInitHp(int hp) { _initHp = hp; }
};
