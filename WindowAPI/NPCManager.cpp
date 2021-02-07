#include "stdafx.h"
#include "NPCManager.h"

HRESULT NPCManager::init()
{
	vector<vector<string>> shopData = DATAEXTRACTOR->txtLoad("Database/ShopSet.csv");

	for (int i = 0; i < shopData.size(); i++)
	{
		Shop* shop = new Shop();
		shop->init(
			stoi(shopData[i][0]),		// id
			stoi(shopData[i][1]),		// x
			stoi(shopData[i][2]),		// y
			shopData[i][3]				// imageName
		);

		if (shopData[i][4] == "TRUE")
		{
			shop->SetNpcVariable(
				stoi(shopData[i][5]),	// x
				stoi(shopData[i][6]),	// y
				shopData[i][7]			// ImageName
			);
		}

		for (int j = 8; j < shopData[i].size(); j++)
		{
			if (shopData[i][j] == "") break;
			shop->AddItem(Item(DATAMANAGER->GetItem(stoi(shopData[i][j]))));
		}

		_vShops.push_back(shop);
	}

	return S_OK;
}

void NPCManager::release()
{
}

void NPCManager::update()
{
	for (int i = 0; i < _vShops.size(); i++)
	{
		_vShops[i]->update();
	}
}

void NPCManager::render(HDC hdc)
{
	for (int i = 0; i < _vShops.size(); i++)
	{
		_vShops[i]->render(hdc);
	}
}
