#pragma once
#include "Monster.h"

class Spike : public Monster
{
private:
	DIRECTION _dir;
	int _fireTimer;
	bool _isAttacking;
public:

	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void OnOff();
	void CollisionCheck();
	virtual bool Interaction();
	virtual void Animation();

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
