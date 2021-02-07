#pragma once
#include "singletonBase.h"
#include "Item.h"
#include "Plant.h"

class DataManager : public singletonBase<DataManager>
{
private :
	map<int, Item> _mItem;
	map<string, Item> _mItemString;
	map<int, Plant> _mPlant;

public :
	HRESULT init();

	Item GetItem(int id) { return _mItem[id]; }
	Item GetItem(string name) { return _mItemString[name]; }
	map<int, Item> GetItemList() { return _mItem; }
	Plant GetPlant(int id) { return _mPlant[id]; }

	void SetItemData();
	void SetPlantData();
};

