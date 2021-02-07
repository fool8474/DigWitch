#pragma once
#include "Monster.h"

class player;
class Sasin : public Monster
{
private:
	player* _p;
	int _moveTargetY;
	
public:
	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void SetPlayer(player* p) { _p = p; }

	virtual void Move();
	void CollisionCheck();
	virtual void Animation();
};
