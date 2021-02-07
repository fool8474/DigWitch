#include "stdafx.h"
#include "Craft.h"
#include "Inventory.h"

HRESULT Craft::init()
{
	_currentSelectedId = -1;
	int count = 0;
	for (int i = 0; i<DATAMANAGER->GetItemList().size(); i++)
	{
		Item item = DATAMANAGER->GetItem(i);
		if (item._useCraftNumber != 0)
		{
			UIImage* imgFrame = new UIImage();
			imgFrame->init(to_string(i), 20, 20 + count * 120, 573, 114, "UI_CraftSelect", false, 0, 0);

			imgFrame->SetIsViewing(true);
			imgFrame->SetUseOutsideLimit(true);
			UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->AddFrame(imgFrame);

			UIImage* itemImg = new UIImage();
			itemImg->init("image", 5, 5, 96, 96, item.GetImageName(), true, item.GetFrameX(), item.GetFrameY());
			imgFrame->AddFrame(itemImg);

			UIText* itemName = new UIText();
			itemName->init("name", 500, 30, item.GetName(), FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_RIGHT, -4);
			imgFrame->AddFrame(itemName);

			UIText* create = new UIText();
			create->init("create", 500, 60, "CANNOT CREATE", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT, -4);
			imgFrame->AddFrame(create);
			count++;
		}
	}

	UIScroll* scroll = new UIScroll();
	scroll->init("craftScroll", 598, 10, IMAGEMANAGER->findImage("UI_ScrollBar")->getWidth(), IMAGEMANAGER->findImage("UI_ScrollBar")->getHeight(), "UI_ScrollBar");
	scroll->SetTarget(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft"));
	UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->AddFrame(scroll);
	
	UIFrame* rightFrame = new UIFrame();
	rightFrame->init("rightFrame", 650, 10, 550, 500, "");
	rightFrame->SetIsViewing(true);
	UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->AddFrame(rightFrame);

	UIImage* createFrame = new UIImage();
	createFrame->init("create", 40, 340, 442, 112, "UI_CreateButton", false, 0, 0);
	rightFrame->AddFrame(createFrame);

	_canCraft = false;
	_numberItemA = 0;
	_indexA = 0;
	_numberItemB = 0;
	_indexB = 0;
	_numberItemC = 0;
	_indexC = 0;

	return S_OK;
}

void Craft::update()
{
	GoCraftPage();
	CraftItem(_currentSelectedId);
}

void Craft::GoCraftPage()
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft");
	if (frame->GetIsViewing())
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < frame->GetVChildFrames().size() - 1; i++)
			{
				if (PtInRect(&frame->GetVChildFrames()[i]->GetRect(), _ptMouse))
				{
					CraftPageSetting(stoi(frame->GetVChildFrames()[i]->GetName()));
				}
			}
		}
	}
}

void Craft::CraftItem(int id)
{
	if (_currentSelectedId == -1) return;

	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->GetChild("rightFrame");
	
	if (frame->GetIsViewing())
	{
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (PtInRect(&frame->GetChild("create")->GetRect(), _ptMouse))
			{
				if (_canCraft)
				{
					Item* item = new Item(DATAMANAGER->GetItem(id));
					_inven->PushItem(item);

					for (int j = 0; j < item->_useCountOne; j++)
					{
						for (int i = 0; i < _inven->GetItemList().size(); i++)
						{
							Item* curItem = _inven->GetItemList()[i];

							Item it = DATAMANAGER->GetItem(item->_useIdOne);
							if (curItem->GetName() == it.GetName())
							{
								_inven->UseItemOne(i);
							}
						}
					}

					if (item->_useCraftNumber > 1)
					{
						for (int j = 0; j < item->_useCountTwo; j++)
						{
							for (int i = 0; i < _inven->GetItemList().size(); i++)
							{
								Item* curItem = _inven->GetItemList()[i];

								Item it = DATAMANAGER->GetItem(item->_useIdTwo);
								if (curItem->GetName() == it.GetName())
								{
									_inven->UseItemOne(i);
								}
							}
						}
					}
						
					if (item->_useCraftNumber > 2)
					{
						for (int j = 0; j < item->_useCountThree; j++)
						{
							for (int i = 0; i < _inven->GetItemList().size(); i++)
							{
								Item* curItem = _inven->GetItemList()[i];

								Item it = DATAMANAGER->GetItem(item->_useIdThree);
								if (curItem->GetName() == it.GetName())
								{
									_inven->UseItem(i, false);
								}
							}
						}
					}

					CraftPageSetting(id);
					_inven->SetInventoryUI();
					CraftChecker();
				}
			}
		}
		
	}
}

void Craft::CraftPageSetting(int id)
{
	if (id == -1) return;
	_currentSelectedId = id;
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->GetChild("rightFrame");
	frame->GetVChildFrames().erase(frame->GetVChildFrames().begin() + 1, frame->GetVChildFrames().end());

	Item item = DATAMANAGER->GetItem(id);

	UIImage* imgFrame;
	UIText* numberOfIngredient;

	CheckCanCraft(id);

	imgFrame = new UIImage();
	imgFrame->init("Frame1", 212, 22, 112, 112, "UI_Box", false, 0, 0);
	frame->AddFrame(imgFrame);
	imgFrame = new UIImage();
	imgFrame->init("1", 220, 30, 96, 96, item.GetImageName(), true, item.GetFrameX(), item.GetFrameY());
	frame->AddFrame(imgFrame);

	switch (item._useCraftNumber)
	{
	case 1:
		imgFrame = new UIImage();
		imgFrame->init("Frame1", 212, 162, 112, 112, "UI_Box", false, 0, 0);
		frame->AddFrame(imgFrame);
		imgFrame = new UIImage();
		imgFrame->init("1", 220, 170, 96, 96, DATAMANAGER->GetItem(item._useIdOne).GetImageName(), true, DATAMANAGER->GetItem(item._useIdOne).GetFrameX(), DATAMANAGER->GetItem(item._useIdOne).GetFrameY());
		frame->AddFrame(imgFrame);

		numberOfIngredient = new UIText();
		numberOfIngredient->init("ingred1", 285, 276, to_string(_numberItemA) + "/" + to_string(item._useCountOne), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
		frame->AddFrame(numberOfIngredient);
		break;

	case 2:
		imgFrame = new UIImage();
		imgFrame->init("Frame1", 302, 162, 112, 112, "UI_Box", false, 0, 0);
		frame->AddFrame(imgFrame);
		imgFrame = new UIImage();
		imgFrame->init("1", 310, 170, 96, 96, DATAMANAGER->GetItem(item._useIdOne).GetImageName(), true, DATAMANAGER->GetItem(item._useIdOne).GetFrameX(), DATAMANAGER->GetItem(item._useIdOne).GetFrameY());
		frame->AddFrame(imgFrame);
		numberOfIngredient = new UIText();
		numberOfIngredient->init("ingred1", 375, 276, to_string(_numberItemA) + "/" + to_string(item._useCountOne), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
		frame->AddFrame(numberOfIngredient);

		imgFrame = new UIImage();
		imgFrame->init("Frame1", 122, 162, 112, 112, "UI_Box", false, 0, 0);
		frame->AddFrame(imgFrame);
		imgFrame = new UIImage();
		imgFrame->init("2", 130, 170, 96, 96, DATAMANAGER->GetItem(item._useIdTwo).GetImageName(), true, DATAMANAGER->GetItem(item._useIdTwo).GetFrameX(), DATAMANAGER->GetItem(item._useIdTwo).GetFrameY());
		frame->AddFrame(imgFrame);
		numberOfIngredient = new UIText();
		numberOfIngredient->init("ingred2", 195, 276, to_string(_numberItemB) + "/" + to_string(item._useCountTwo), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
		frame->AddFrame(numberOfIngredient);
		break;

	case 3:
		imgFrame = new UIImage();
		imgFrame->init("Frame1", 212, 163, 112, 112, "UI_Box", false, 0, 0);
		frame->AddFrame(imgFrame);
		imgFrame = new UIImage();
		imgFrame->init("1", 220, 170, 96, 96, DATAMANAGER->GetItem(item._useIdOne).GetImageName(), true, DATAMANAGER->GetItem(item._useIdOne).GetFrameX(), DATAMANAGER->GetItem(item._useIdOne).GetFrameY());
		frame->AddFrame(imgFrame);
		numberOfIngredient = new UIText();
		numberOfIngredient->init("ingred1", 285, 276, to_string(_numberItemA) + "/" + to_string(item._useCountOne), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
		frame->AddFrame(numberOfIngredient);

		imgFrame = new UIImage();
		imgFrame->init("Frame1", 62, 162, 112, 112, "UI_Box", false, 0, 0);
		frame->AddFrame(imgFrame);
		imgFrame = new UIImage();
		imgFrame->init("2", 70, 170, 96, 96, DATAMANAGER->GetItem(item._useIdTwo).GetImageName(), true, DATAMANAGER->GetItem(item._useIdTwo).GetFrameX(), DATAMANAGER->GetItem(item._useIdTwo).GetFrameY());
		frame->AddFrame(imgFrame);
		numberOfIngredient = new UIText();
		numberOfIngredient->init("ingred2", 135, 276, to_string(_numberItemB) + "/" + to_string(item._useCountTwo), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
		frame->AddFrame(numberOfIngredient);

		imgFrame = new UIImage();
		imgFrame->init("Frame1", 362, 162, 112, 112, "UI_Box", false, 0, 0);
		frame->AddFrame(imgFrame);
		imgFrame = new UIImage();
		imgFrame->init("3", 370, 170, 96, 96, DATAMANAGER->GetItem(item._useIdThree).GetImageName(), true, DATAMANAGER->GetItem(item._useIdThree).GetFrameX(), DATAMANAGER->GetItem(item._useIdThree).GetFrameY());
		frame->AddFrame(imgFrame);
		numberOfIngredient = new UIText();
		numberOfIngredient->init("ingred3", 435, 276, to_string(_numberItemC) + "/" + to_string(item._useCountThree), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
		frame->AddFrame(numberOfIngredient);
		break;
	}

}

void Craft::CheckCanCraft(int id)
{
	Item item = DATAMANAGER->GetItem(id);
	
	_canCraft = true;

	_numberItemA = 0;
	_indexA = 0;
	_numberItemB = 0;
	_indexB = 0;
	_numberItemC = 0;
	_indexC = 0;

	for (int i = 0; i < _inven->GetItemList().size(); i++)
	{
		Item* curItem = _inven->GetItemList()[i];

		if (item._useCraftNumber > 0)
		{
			Item itA = DATAMANAGER->GetItem(item._useIdOne);
			if (curItem->GetName() == itA.GetName())
			{
				_numberItemA = stoi(dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetVChildFrames()[i]->GetChild("itemCount"))->GetText());
				_indexA = i;
			}
		}

		if (item._useCraftNumber > 1)
		{
			Item itB = DATAMANAGER->GetItem(item._useIdTwo);
			if (curItem->GetName() == itB.GetName())
			{
				_numberItemB = stoi(dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetVChildFrames()[i]->GetChild("itemCount"))->GetText());
				_indexB = i;
			}
		}

		if (item._useCraftNumber > 2)
		{
			Item itC = DATAMANAGER->GetItem(item._useIdThree);
			if (curItem->GetName() == itC.GetName())
			{
				_numberItemC = stoi(dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetVChildFrames()[i]->GetChild("itemCount"))->GetText());
				_indexC = i;
			}
		}
	}

	if (_numberItemA < item._useCountOne) _canCraft = false;
	if (_numberItemB < item._useCountTwo) _canCraft = false;
	if (_numberItemC < item._useCountThree) _canCraft = false;
	
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft")->GetChild("rightFrame");

	if (_canCraft) frame->GetChild("create")->SetIsViewing(true);
	else frame->GetChild("create")->SetIsViewing(false);
}

bool Craft::GetCanCraft(int id)
{
	Item item = DATAMANAGER->GetItem(id);

	int canCraft = true;

	int numberItemA = 0;
	int numberItemB = 0;
	int numberItemC = 0;

	for (int i = 0; i < _inven->GetItemList().size(); i++)
	{
		Item* curItem = _inven->GetItemList()[i];

		if (item._useCraftNumber > 0)
		{
			Item itA = DATAMANAGER->GetItem(item._useIdOne);
			if (curItem->GetName() == itA.GetName())
			{
				numberItemA = stoi(dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetVChildFrames()[i]->GetChild("itemCount"))->GetText());
			}
		}

		if (item._useCraftNumber > 1)
		{
			Item itB = DATAMANAGER->GetItem(item._useIdTwo);
			if (curItem->GetName() == itB.GetName())
			{
				numberItemB = stoi(dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetVChildFrames()[i]->GetChild("itemCount"))->GetText());
			}
		}

		if (item._useCraftNumber > 2)
		{
			Item itC = DATAMANAGER->GetItem(item._useIdThree);
			if (curItem->GetName() == itC.GetName())
			{
				numberItemC = stoi(dynamic_cast<UIText*>(UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->GetVChildFrames()[i]->GetChild("itemCount"))->GetText());
			}
		}
	}

	if (numberItemA < item._useCountOne) canCraft = false;
	if (numberItemB < item._useCountTwo) canCraft = false;
	if (numberItemC < item._useCountThree) canCraft = false;

	return canCraft;
}

void Craft::CraftChecker()
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_craft");
	for (int i = 0; i < frame->GetVChildFrames().size() - 2; i++)
	{
		if (GetCanCraft(stoi(frame->GetVChildFrames()[i]->GetName())))
		{
			dynamic_cast<UIText*>(frame->GetVChildFrames()[i]->GetChild("create"))->SetText("CREATE");
		}

		else
		{
			dynamic_cast<UIText*>(frame->GetVChildFrames()[i]->GetChild("create"))->SetText("CANNOT CREATE");
		}
	}
}
