#pragma once
#include "Object.h"

class player;
class Totem;
class TotemBullet : public Object
{
private:
	Totem*		_parent;
	DIRECTION	_dir;
	bool		_isFire;

public:
	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void Move();
	virtual bool Interaction();
	virtual void SetBody();
	virtual void Animation();
	virtual void CollisionCheck();
	virtual void DeathAnim();
	virtual void Death();

	void ReleaseBullet();
	void SetDirection(DIRECTION dir) { _dir = dir; }
	void SetParent(Totem* obj) { _parent = obj; }
	
	Totem* GetParent() { return _parent; }
};
