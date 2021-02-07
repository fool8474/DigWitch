#include "stdafx.h"
#include "Item.h"

HRESULT Item::init()
{
	return S_OK;
}

HRESULT Item::init(int id, string name, int price, int frameX, int frameY, string imageName)
{
	_id = id;
	_name = name;
	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);
	_price = price;
	_frameX = frameX;
	_frameY = frameY;

	return S_OK;
}

void Item::InitCraftIngredient(int numberOfUse, int oneid, int oneCount, int twoId, int twoCount, int threeId, int threeCount)
{
	_useCraftNumber = numberOfUse;
	_useIdOne = oneid;
	_useCountOne = oneCount;
	_useIdTwo = twoId;
	_useCountTwo = twoCount;
	_useIdThree = threeId;
	_useCountThree = threeCount;
}

void Item::release()
{
}

void Item::update()
{
}