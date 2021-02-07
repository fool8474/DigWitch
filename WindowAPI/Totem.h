#pragma once
#include "Monster.h"
#include "TotemBullet.h"

class Totem : public Monster
{
private:
	DIRECTION _dir;
	TotemBullet* _bullet;
	int _fireTimer;
public:

	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void Fire();
	virtual bool Interaction();
	virtual void Animation();

	void SetBullet(TotemBullet* bullet) { _bullet = bullet; }
	void SetDirection(DIRECTION dir) 
	{ 
		_dir = dir; 
		switch (dir)
		{
		case DIRECTION::DR_U: _frameX = 0; break;
		case DIRECTION::DR_D: _frameX = 1; break;
		case DIRECTION::DR_R: _frameX = 2; break;
		case DIRECTION::DR_L: _frameX = 3; break;
		}
	}
};

