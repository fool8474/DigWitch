#pragma once
#include "gameNode.h"
#include "player.h"
#include "PlayScene.h"

class mainGame : public gameNode
{
private:
	player* _player;				//�÷��̾� Ŭ����
	
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void initImage();
};