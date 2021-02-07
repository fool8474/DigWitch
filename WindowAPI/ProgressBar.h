#pragma once

class player;
class Plant;
class ProgressBar
{
public : 
	player* _p;
	image* img;
	image* imgBack;

	virtual	HRESULT init();
	virtual void render(HDC hdc);

};

