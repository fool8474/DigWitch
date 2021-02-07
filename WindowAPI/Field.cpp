#include "stdafx.h"
#include "Field.h"

HRESULT Field::init()
{
	_image = IMAGEMANAGER->findImage("Dirt");
	_deco = IMAGEMANAGER->findImage("Field_Grass_Deco");
	_decoFrameX = RANDOM->range(_deco->getMaxFrameX());
	_useDeco = RANDOM->range(10) == 9 ? true : false;
	_fieldObject = nullptr;
	_reservObject = nullptr;
	_road = IMAGEMANAGER->findImage("Dirt");
	_x = 0;
	_y = 0;

	return S_OK;
}

void Field::release()
{
}

void Field::update()
{
}

void Field::render(HDC hdc)
{
	CAMERAMANAGER->FrameRender(hdc, _image, _x, _y, 1, 1);
	if (_useDeco) CAMERAMANAGER->FrameRender(hdc, _deco, _x, _y, _decoFrameX, 0);

	if (_buildedRoad)
	{
		CAMERAMANAGER->FrameRender(hdc, _road, _x, _y, _roadFrameX, _roadFrameY);
	}

	//string n = to_string(_fieldObject == nullptr) + " " + to_string(_reservObject == nullptr);
	//CAMERAMANAGER->TextDraw(hdc, _x, _y, n.c_str(), n.length());
}

void Field::DrawRoad()
{
	bool surroundRoad[4]; // 상 하 좌 우
	int xMax = GRIDMANAGER->GetFieldVv().size() - 1;
	int yMax = GRIDMANAGER->GetFieldVv()[_xIndex].size() - 1;
	surroundRoad[0] = _yIndex - 1 < 0 ? false : GRIDMANAGER->GetField(_xIndex, _yIndex - 1)->GetBuildedRoad();
	surroundRoad[1] = _yIndex + 1 >= yMax ? false : GRIDMANAGER->GetField(_xIndex, _yIndex + 1)->GetBuildedRoad();
	surroundRoad[2] = _xIndex - 1 < 0 ? false : GRIDMANAGER->GetField(_xIndex - 1, _yIndex)->GetBuildedRoad();
	surroundRoad[3] = _xIndex + 1 >= xMax ? false : GRIDMANAGER->GetField(_xIndex + 1, _yIndex)->GetBuildedRoad();

	if (surroundRoad[0] && surroundRoad[1] && surroundRoad[2] && surroundRoad[3]) // ╂
	{
		_roadFrameX = 5;
		_roadFrameY = 0;
	}

	else if (surroundRoad[0] && surroundRoad[1] && surroundRoad[2]) // ㅓ
	{
		_roadFrameX = 0;
		_roadFrameY = 1;
	}

	else if (surroundRoad[0] && surroundRoad[1] && surroundRoad[3]) // ㅏ
	{
		_roadFrameX = 2;
		_roadFrameY = 1;
	}

	else if (surroundRoad[0] && surroundRoad[2] && surroundRoad[3]) // ㅗ
	{
		_roadFrameX = 1;
		_roadFrameY = 0;
	}

	else if (surroundRoad[1] && surroundRoad[2] && surroundRoad[3]) // ㅜ
	{
		_roadFrameX = 1;
		_roadFrameY = 2;
	}

	else if (surroundRoad[0] && surroundRoad[1])					// ㅣ
	{
		_roadFrameX = 7;
		_roadFrameY = 2;
	}

	else if (surroundRoad[0] && surroundRoad[2])					// ┘
	{
		_roadFrameX = 0;
		_roadFrameY = 0;
	}

	else if (surroundRoad[0] && surroundRoad[3])					// ㄴ
	{
		_roadFrameX = 2;
		_roadFrameY = 0;
	}

	else if (surroundRoad[1] && surroundRoad[2])					// ㄱ
	{
		_roadFrameX = 0;
		_roadFrameY = 2;
	}

	else if (surroundRoad[1] && surroundRoad[3])					// ┎
	{
		_roadFrameX = 2;
		_roadFrameY = 2;
	}

	else if (surroundRoad[2] && surroundRoad[3])					// ㅡ
	{
		_roadFrameX = 7;
		_roadFrameY = 1;
	}

	else if (surroundRoad[0])
	{
		_roadFrameX = 5;
		_roadFrameY = 2;
	}


	else if (surroundRoad[1])
	{
		_roadFrameX = 5;
		_roadFrameY = 1;
	}


	else if (surroundRoad[2])
	{
		_roadFrameX = 6;
		_roadFrameY = 1;
	}


	else if (surroundRoad[3])
	{
		_roadFrameX = 6;
		_roadFrameY = 2;
	}
	else // 그 외
	{
		_roadFrameX = 7;
		_roadFrameY = 0;
	}
}
