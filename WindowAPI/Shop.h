#pragma once
#include "Item.h"

class player;
class Shop
{
private :
	
	int _id;

	bool _isSelected;
	image* _shopImage;
	image* _npcImage;

	float _shopX;
	float _shopY;
	float _npcX;
	float _npcY;

	player* _p;
	RECT _shopRect;

	vector<Item> _vItemList;

	float _scrollPercent;

public :

	HRESULT init(int id, int x, int y, string imageName);
	void release();
	void update();
	void render(HDC hdc);
	void SetNpcVariable(int x, int y, string imageName);
	void SetShopUIOn();
	void AddItem(Item item);
	void BuyItem(int index);
	void CheckBuyItem();

	void ScrollBarMove();
	
	bool GetIsSelected() { return _isSelected; }
	float GetShopX() { return _shopX; }
	float GetShopY() { return _shopY; }
	RECT GetShopRect() { return _shopRect; }
	vector<Item>& GetItemList() { return _vItemList; }
	
	void SetIsSelected(bool isSelected) { _isSelected = isSelected; }
	void SetPlayer(player* p) { _p = p; }

	void CalculateScrollBarPercent();
};

