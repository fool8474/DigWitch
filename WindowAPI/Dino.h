#pragma once
#include "Monster.h"
class Dino : public Monster
{
private:
	int _moveTargetY;
public:
	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void Move();
	int checkMoveContinue();
	void CollisionCheck();
	virtual bool Interaction();
	virtual void Animation();
};

