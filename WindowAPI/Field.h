#pragma once
#include "Object.h"

class Field 
{
private:
	int		_x;
	int		_y;

	int		_xIndex;
	int		_yIndex;

	image*	_image;
	image*	_deco;
	image*	_road;

	int		_roadFrameX;
	int		_roadFrameY;
	int		_decoFrameX;
	bool	_useDeco;
	bool	_buildedRoad;

	Object* _fieldObject;
	Object* _reservObject;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	int GetX() { return _x; }
	int GetY() { return _y; }
	int GetXIndex() { return _xIndex; }
	int GetYIndex() { return _yIndex; }
	Object* GetFieldObject() { return _fieldObject; }
	Object* GetReservObject() { return _reservObject; }
	bool GetBuildedRoad() { return _buildedRoad; }

	void SetX(int x) { _x = x; _xIndex = _x / 96; }
	void SetY(int y) { _y = y; _yIndex = _y / 96; }
	void SetFieldObject(Object* obj) { _fieldObject = obj; }
	void SetReservObject(Object* obj) { _reservObject = obj; }
	void SetBuildedRoad(bool build) { _buildedRoad = build; }

	void DrawRoad();
};
