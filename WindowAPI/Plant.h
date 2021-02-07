#pragma once
#include "Object.h"
#include "Item.h"

enum PLANTTYPE
{
	PT_HURB, PT_FLOWER, PT_MUSHROOM, PT_BERRY
};

class Plant : public Object
{
protected :
	string		_name;
	int			_hp;
	int			_initHp;
	int			_id;
	PLANTTYPE	_type;
	Item*		_item;

	int			_itemCount;
	int			_itemRandom;
public :
	virtual HRESULT init();
	virtual HRESULT init(int xIndex, int yIndex);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual bool Interaction();	
	virtual void SetBody();

	void Restore();

	int GetLevel() { return _level; }
	string GetName() { return _name; }
	int GetInitHp() { return _initHp; }
	int GetHp() { return _hp; }

	void SetItem(Item* item) { _item = item; }
	void SetHp(int hp) { _initHp = _hp = hp; }
	void SetName(string name) { _name = name; }
	void SetPlantType(PLANTTYPE type) { type = _type; }
	void SetId(int id) { _id = id; }
	void SetCount(int count) { _itemCount = count; }
	void SetCountRandom(int random) { _itemRandom = random; }

	virtual void SetLevel(int level) { 
		_level = level; 
	}
};