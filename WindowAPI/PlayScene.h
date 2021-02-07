#pragma once
#include "Scene.h"
#include "Field.h"
#include "player.h"
#include "ProgressBar.h"

class Craft;
class Inventory;
class PlayScene : public Scene
{
private:
	ProgressBar _progress;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void ManageUI();
};

