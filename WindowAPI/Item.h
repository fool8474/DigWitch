#pragma once

struct ObjectMapData
{
	int _id;
	int _x;
	int _y;
	
};

class Item
{
private :
	int			_id;
	string		_name;

	int			_price;

	int			_frameX;
	int			_frameY;

	string		_imageName;
	image*		_image;

public :
	int			_useCraftNumber;
	int			_useIdOne;
	int			_useCountOne;
	int			_useIdTwo;
	int			_useCountTwo;
	int			_useIdThree;
	int			_useCountThree;

	int GetId() { return _id; }
	string GetName() { return _name; }
	int GetPrice() { return _price; }
	int GetFrameX() { return _frameX; }
	int GetFrameY() { return _frameY; }
	string GetImageName() { return _imageName; }
	image* GetImage() { return _image; }

	void SetPrice(int price) { _price = price; }
	void SetFrameX(int frameX) { _frameX = frameX; }
	void SetFrameY(int frameY) { _frameY = frameY; }

	HRESULT init();
	HRESULT init(int id, string name, int price, int frameX, int frameY, string imageName);

	void InitCraftIngredient(int numberOfUse, int oneId, int oneCount, int twoId = -1, int twoCount = -1, int threeId = -1, int threeCount = -1);
	void release();
	void update();
};

