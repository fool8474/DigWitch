#pragma once
#include "Object.h"
enum MONSTERTYPE
{
	MT_DINO, MT_SPIDER, MT_SPIKE, MT_TOTEM, MT_SASIN
};

class Monster : public Object
{
protected :
	MONSTERTYPE _monsterType;
public :

	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	virtual void SetBody();
	virtual void DeathAnim();
	virtual void Death();
	virtual void Move();
	virtual bool Interaction();
	virtual void Animation();


};

