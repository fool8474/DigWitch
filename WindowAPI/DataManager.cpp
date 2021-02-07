#include "stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init()
{
	SetItemData();
	SetPlantData();
	return S_OK;
}

void DataManager::SetItemData()
{
	vector<vector<string>> itemData = DATAEXTRACTOR->txtLoad("Database/ItemSet.csv");

	Item item;
	
	for (int i = 0; i < itemData.size(); i++)
	{
		item.init(
			stoi(itemData[i][0]),	// id
			itemData[i][1],			// name
			stoi(itemData[i][2]),	// price
			stoi(itemData[i][3]),	// frameX
			stoi(itemData[i][4]),	// frameY
			itemData[i][5]			// imageName
		);

		item.InitCraftIngredient(
			stoi(itemData[i][6]),	// UseCraft
			stoi(itemData[i][7]),	// Use1
			stoi(itemData[i][8]),	// number
			stoi(itemData[i][9]),	// Use2
			stoi(itemData[i][10]),	// number
			stoi(itemData[i][11]),	// Use3
			stoi(itemData[i][12])	// number
		);

		_mItem[stoi(itemData[i][0])] = item;
		_mItemString[itemData[i][1]] = item;
	}
}

void DataManager::SetPlantData()
{
	vector<vector<string>> plantData = DATAEXTRACTOR->txtLoad("Database/PlantSet.csv");

	Plant plant;

	for (int i = 0; i < plantData.size(); i++)
	{
		plant.init(0,0);

		// ID	NAME	TYPE	LEVEL	HP	ITEMID	COUNT	RANDOMCOUNT	frameX	frameY	Image
		plant.SetId(stoi(plantData[i][0]));
		plant.SetName(plantData[i][1]);
		
		if (plantData[i][2] == "BERRY") plant.SetPlantType(PLANTTYPE::PT_BERRY);
		else if (plantData[i][2] == "FLOWER") plant.SetPlantType(PLANTTYPE::PT_FLOWER);
		else if (plantData[i][2] == "HURB") plant.SetPlantType(PLANTTYPE::PT_HURB);
		else if (plantData[i][2] == "MUSHROOM") plant.SetPlantType(PLANTTYPE::PT_MUSHROOM);

		plant.SetLevel(stoi(plantData[i][3]));
		plant.SetHp(stoi(plantData[i][4]));
		plant.SetItem(new Item(_mItem[stoi(plantData[i][5])]));
		plant.SetCount(stoi(plantData[i][6]));
		plant.SetCountRandom(stoi(plantData[i][7]));
		plant.SetFrameX(stoi(plantData[i][8]));
		plant.SetFrameY(stoi(plantData[i][9]));
		plant.SetImage(IMAGEMANAGER->findImage(plantData[i][10]));
		plant.SetIsinteractable(true);

		_mPlant[stoi(plantData[i][0])] = plant;
		
	}
}
