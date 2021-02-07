#pragma once

class player;
class Inventory
{
private :
	vector<Item*>	_itemList;
	player*			_p;

public :
	vector<Item*>& GetItemList() { return _itemList; }
	void SetPlayer(player* p) { _p = p; }
	
	HRESULT init();
	void update();

	void removeItem(int index);
	void PushItem(Item* item);
	void UseItem(int index, bool isSell);
	void UseItemOne(int index);
	void SetInventoryUI();
	void CheckItemDoubleClick();
};

