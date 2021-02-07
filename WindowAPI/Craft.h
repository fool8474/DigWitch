#pragma once
class Inventory;
class Craft
{
private:
	vector<Item*>	_craftList;
	Inventory* _inven;
	int	_currentSelectedId;
	bool _canCraft;

	int _numberItemA;
	int _indexA;
	int _numberItemB;
	int _indexB;
	int _numberItemC;
	int _indexC;

public:
	vector<Item*>& GetCraftList() { return _craftList; }
	void SetInventory(Inventory* inven) { _inven = inven; }

	HRESULT init();
	void update();

	void GoCraftPage();
	void CraftItem(int id);
	void CraftPageSetting(int id);
	void CheckCanCraft(int id);
	bool GetCanCraft(int id);
	int getCurrentSelectedId() { return _currentSelectedId; }
	void CraftChecker();
	/*
	void removeItem(int index);
	void PushItem(Item* item);
	void SetInventoryUI();
	void CheckItemDoubleClick();
	*/
};

