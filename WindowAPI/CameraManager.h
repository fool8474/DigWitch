#pragma once
#include "singletonBase.h"
#include "image.h"
#include "Object.h"

class cameraManager : public singletonBase<cameraManager>
{
private:

	RECT _cameraRect;
	float _pivotX, _pivotY;
	float _maxX, _maxY;
	float _minX, _minY;
	float _distanceX, _distanceY;
	float _absDistanceX, _absDistanceY;
	bool _isControl;
	Object* _target;

public:
	cameraManager() {
		_cameraRect = { 0,0,0,0 };
		_pivotX = 0.f;
		_pivotY = 0.f;
		_maxX = 0.f;
		_maxY = 0.f;
		_minX = 0.f;
		_minY = 0.f;
		_distanceX = 0.f;
		_distanceY = 0.f;
		_isControl = false;
	}
	~cameraManager() {}

	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY);

	void Rectangle(HDC hdc, RECT rc);
	void Rectangle(HDC hdc, int left, int top, int width, int height);

	void Render(HDC hdc, image* ig, int destX, int destY);
	void FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY);
	void TextDraw(HDC hdc, int destX, int destY, LPCSTR lpstring, int c);
	void AlphaRender(HDC hdc, image * ig, int destX, int destY, BYTE alpha);
	void frameAlphaRender(HDC hdc, image* ig, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	void movePivot(float& x, float& y);
	int getRelativeX(float x);
	int getRelativeY(float y);
	float getPivotX() { return _pivotX; }
	float getPivotY() { return _pivotY; }
	float getDistanceX() { return _distanceX; }
	float getDistanceY() { return _distanceY; }
	RECT getRect() { return _cameraRect; }
	void setCon(bool as) { _isControl = as; }
	bool getCon() { return _isControl; }
	void SetTarget(Object* obj) { _target = obj; }
};