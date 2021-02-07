#pragma once
#include "Object.h"
#include "Item.h"
class Tree : public Plant
{
private:
	PLANTTYPE	_type;

public:
	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual bool Interaction();
	virtual void SetBody();
	void Restore();

	void SetPlantType(PLANTTYPE type) { type = _type; }
	virtual void SetLevel(int level) {
		_level = level;
		_hp = _initHp = 100 + (_level * 80);
	}
};
