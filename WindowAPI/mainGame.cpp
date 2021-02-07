#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	initImage();

	SCENEMANAGER->init();

	SCENEMANAGER->addScene("PLAY", new PlayScene());
	SCENEMANAGER->loadScene("PLAY");

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	SCENEMANAGER->render();
	this->getBackBuffer()->render(getHDC());
}

void mainGame::initImage()
{
	IMAGEMANAGER->addFrameImage("Field_Grass_Deco", "Images/DIG/Grass_Deco.bmp", 766, 93, 8, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Plant_Berry", "Images/DIG/Berry.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ICON_Berry", "Images/DIG/ICON_Berry.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Plant_Flower", "Images/DIG/Flower.bmp", 960, 96, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ICON_Flower", "Images/DIG/ICON_Flower.bmp", 960, 96, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Plant_Hurb", "Images/DIG/Hurb.bmp", 192, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ICON_Hurb", "Images/DIG/ICON_Hurb.bmp", 192, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Plant_Mushroom", "Images/DIG/Mushroom.bmp", 672, 102, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ICON_Mushroom", "Images/DIG/ICON_Mushroom.bmp", 672, 96, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ICON_Craft", "Images/DIG/ICON_Craft.bmp", 1440, 384, 15, 4, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("Monster_Spider", "Images/DIG/Monster_Spider.bmp", 192, 192, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Monster_Dino", "Images/DIG/Monster_Dino.bmp", 192, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Monster_Sasin", "Images/DIG/Monster_Sasin.bmp", 208, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Monster_Spike", "Images/DIG/Monster_Spike.bmp", 192, 96, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Monster_Totem", "Images/DIG/MONSTER_Totem.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("Bullet_Totem", "Images/DIG/Bullet_Totem.bmp", 480, 56, 9, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Tree", "Images/DIG/Tree.bmp", 480, 96, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Stone", "Images/DIG/Stone.bmp", 864, 96, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Dirt", "Images/DIG/Dirt.bmp", 768, 288, 8, 3, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Character", "Images/DIG/Chara.bmp", 103, 84, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Character_Gather", "Images/DIG/Chara_Gather.bmp", 322, 99, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("UI_Bag", "Images/DIG/UI_Bag.bmp", 191, 131, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_BlackOut", "Images/DIG/UI_BlackOut.bmp", 117, 116, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Box", "Images/DIG/UI_Box.bmp", 112, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Craft", "Images/DIG/UI_Craft.bmp", 1219, 512, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_CraftSelect", "Images/DIG/UI_CraftSelect.bmp", 573, 114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_CreateButton", "Images/DIG/UI_CreateButton.bmp", 442, 112, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Inven", "Images/DIG/UI_Inven.bmp", 1219, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Menu", "Images/DIG/UI_Menu.bmp", 1277, 718, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Money", "Images/DIG/UI_Money.bmp", 186, 149, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_MPBar", "Images/DIG/UI_MPBar.bmp", 276, 39, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_MPBarBack", "Images/DIG/UI_MPBarBack.bmp", 276, 39, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_ProgressBar", "Images/DIG/UI_ProgressBar.bmp", 692, 98, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_ProgressBarBack", "Images/DIG/UI_ProgressBarBack.bmp", 692, 98, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_ScrollBar", "Images/DIG/UI_ScrollBar.bmp", 34, 61, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Shop", "Images/DIG/UI_Shop.bmp", 755, 718, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_ShopSelect", "Images/DIG/UI_ShopSelect.bmp", 666, 192, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_Skill", "Images/DIG/UI_Skill.bmp", 941, 165, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_SkillOff", "Images/DIG/UI_SkillOff.bmp", 41, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_SkillOn", "Images/DIG/UI_SkillOn.bmp", 41, 102, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("PARTICLE_Stone1", "Images/DIG/Particle/PARTICLE_Stone1.bmp", 24, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Stone2", "Images/DIG/Particle/PARTICLE_Stone2.bmp", 14, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Stone3", "Images/DIG/Particle/PARTICLE_Stone3.bmp", 13, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Stone4", "Images/DIG/Particle/PARTICLE_Stone4.bmp", 23, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Leave1", "Images/DIG/Particle/PARTICLE_Leave1.bmp", 51, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Leave2", "Images/DIG/Particle/PARTICLE_Leave2.bmp", 35, 53, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Leave3", "Images/DIG/Particle/PARTICLE_Leave2.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Leave4", "Images/DIG/Particle/PARTICLE_Leave2.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Leave5", "Images/DIG/Particle/PARTICLE_Leave4.bmp", 51, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PARTICLE_Leave6", "Images/DIG/Particle/PARTICLE_Leave5.bmp", 51, 40, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("Font_Word_Pix_Big", "Images/DIG/UI/WORD_PIX_BIG.bmp", 702, 81, 26, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Font_Word_Pix_Middle", "Images/DIG/UI/WORD_PIX_MIDDLE.bmp", 494, 57, 26, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Font_Word_Pix_Small", "Images/DIG/UI/WORD_PIX_SMALL.bmp", 338, 39, 26, 3, true, RGB(255, 0, 255));
}
