#pragma once
#include "singletonBase.h"
#include "Shop.h"

class NPCManager : public singletonBase<NPCManager>
{
private :
	vector<Shop*> _vShops;
public :
	
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	vector<Shop*> GetShops() { return _vShops; }
};

