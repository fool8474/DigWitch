#include "stdafx.h"
#include "PlayScene.h"
#include "Inventory.h"
#include "Craft.h"
#include "stdafx.h"

HRESULT PlayScene::init()
{
	DATAMANAGER->init();
	UIMANAGER->init();
	GRIDMANAGER->init();
	GRIDMANAGER->GetPlayer()->init();
	PARTICLEMANAGER->init();
	
	CAMERAMANAGER->init(GRIDMANAGER->GetPlayer()->GetX(), GRIDMANAGER->GetPlayer()->GetY(), 96 * 3000, 96 * 100, 0, 0, WINSIZEX / 2 - 96 * 5, WINSIZEY / 2);


	_progress.init();
	_progress._p = GRIDMANAGER->GetPlayer();

	return S_OK;
}

void PlayScene::release()
{
	GRIDMANAGER->release();
	UIMANAGER->release();
	PARTICLEMANAGER->release();
}

void PlayScene::update()
{
	INPUT->update();
	GRIDMANAGER->update();
	GRIDMANAGER->GetPlayer()->update();
	GRIDMANAGER->GetSasin()->update();
	UIMANAGER->update();
	PARTICLEMANAGER->update();

	ManageUI();
}

void PlayScene::render()
{
	GRIDMANAGER->render(getMemDC());
	GRIDMANAGER->GetPlayer()->render(getMemDC());
	GRIDMANAGER->GetSasin()->render(getMemDC());
	PARTICLEMANAGER->render(getMemDC());
	
	_progress.render(getMemDC());
	UIMANAGER->render(getMemDC());

}

void PlayScene::ManageUI()
{
	for (int i = 0; i < UIMANAGER->_vItemToBag.size(); i++)
	{
		UIFrame* uiFrame = UIMANAGER->_vItemToBag[i];

		uiFrame->SetX(uiFrame->GetX() + (UIMANAGER->_GameFrame->GetChild("mainFrame_backpack")->GetX() - uiFrame->GetX()) * 0.05f);
		uiFrame->SetY(uiFrame->GetY() + (UIMANAGER->_GameFrame->GetChild("mainFrame_backpack")->GetY() - uiFrame->GetY()) * 0.05f);
	
		if (getDistance(uiFrame->GetX(), uiFrame->GetY(), UIMANAGER->_GameFrame->GetChild("mainFrame_backpack")->GetX(), UIMANAGER->_GameFrame->GetChild("mainFrame_backpack")->GetY()) < 50)
		{
			GRIDMANAGER->GetPlayer()->GetInven()->PushItem(new Item(DATAMANAGER->GetItem(uiFrame->GetName())));
			GRIDMANAGER->GetPlayer()->GetInven()->SetInventoryUI();

			UIMANAGER->_vItemToBag.erase(UIMANAGER->_vItemToBag.begin() + i);
			i--;
		}
	}

	if (INPUT->GetKeyDown('I'))
	{
		if (UIMANAGER->GetPlayerFrame()->GetIsViewing() == true)
		{
			if (UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetIsViewing() == true)
			{
				UIMANAGER->GetPlayerFrame()->SetIsViewing(!UIMANAGER->GetPlayerFrame()->GetIsViewing());
			}

			else
			{
				UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->SetIsViewing(false);
				UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->SetIsViewing(true);
			}
		}

		else
		{
			UIMANAGER->GetPlayerFrame()->SetIsViewing(!UIMANAGER->GetPlayerFrame()->GetIsViewing());
			UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->SetIsViewing(false);
			UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->SetIsViewing(true);
		}
	}

	if (INPUT->GetKeyDown('C'))
	{
		if (UIMANAGER->GetPlayerFrame()->GetIsViewing() == true)
		{
			if (UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->GetIsViewing() == true)
			{
				UIMANAGER->GetPlayerFrame()->SetIsViewing(!UIMANAGER->GetPlayerFrame()->GetIsViewing());
			}

			else
			{
				UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->SetIsViewing(true);
				UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->SetIsViewing(false);
				GRIDMANAGER->GetPlayer()->GetCraft()->CraftPageSetting(GRIDMANAGER->GetPlayer()->GetCraft()->getCurrentSelectedId());
				GRIDMANAGER->GetPlayer()->GetCraft()->CraftChecker();
			}
		}

		else
		{
			UIMANAGER->GetPlayerFrame()->SetIsViewing(!UIMANAGER->GetPlayerFrame()->GetIsViewing());
			UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->SetIsViewing(true);
			UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->SetIsViewing(false);
			GRIDMANAGER->GetPlayer()->GetCraft()->CraftPageSetting(GRIDMANAGER->GetPlayer()->GetCraft()->getCurrentSelectedId());
			GRIDMANAGER->GetPlayer()->GetCraft()->CraftChecker();
		}
	}
}