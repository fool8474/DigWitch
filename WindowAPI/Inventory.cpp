#include "stdafx.h"
#include "Inventory.h"
#include "player.h"

HRESULT Inventory::init()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			UIImage* imgFrame = new UIImage();
			imgFrame->init("invenPage" + (i * 10 + j),
				20 + j * 120, 20 + i * 120,
				96, 96, "", true, 0, 0
			);
			
			UIText* uiText = new UIText();
			uiText->init("itemCount", 70, 70, "0", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_RIGHT);
			
			imgFrame->SetIsViewing(true);
			UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory")->AddFrame(imgFrame);
			imgFrame->AddFrame(uiText);
		}
	}
	return S_OK;
}

void Inventory::update()
{
	CheckItemDoubleClick();
}

void Inventory::PushItem(Item* item)
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory");
	bool findItem = false;

	for (int i = 0; i < _itemList.size(); i++)
	{
		if (item->GetId() == _itemList[i]->GetId())
		{
			UIText* text = dynamic_cast<UIText*>(frame->GetVChildFrames()[i]->GetChild("itemCount"));
			text->SetText(to_string(stoi(text->GetText()) + 1));
			text->SetIsViewing(true);
			findItem = true;
		}
	}

	if (!findItem)
	{
		_itemList.push_back(item);
		UIText* text = dynamic_cast<UIText*>(frame->GetVChildFrames()[_itemList.size()-1]->GetChild("itemCount"));
		text->SetText("1");
		text->SetIsViewing(true);
	}

	SetInventoryUI();
}

void Inventory::UseItem(int index, bool isSell)
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory");
	Item* item = _itemList[index];
	if(isSell) _p->SetMoney(_p->GetMoney() + item->GetPrice() * stoi(dynamic_cast<UIText*>(frame->GetVChildFrames()[index]->GetChild("itemCount"))->GetText()));
	
	for (int i = index; i < _itemList.size()-1; i++)
	{
		UIText* text = dynamic_cast<UIText*>(frame->GetVChildFrames()[i]->GetChild("itemCount"));
		UIText* textNext = dynamic_cast<UIText*>(frame->GetVChildFrames()[i+1]->GetChild("itemCount"));
		
		text->SetText(textNext->GetText());
	}

	dynamic_cast<UIText*>(frame->GetVChildFrames()[_itemList.size() - 1]->GetChild("itemCount"))->SetText("0");

	removeItem(index);
	SetInventoryUI();
}

void Inventory::UseItemOne(int index)
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory");
	Item* item = _itemList[index];

	UIText* text = dynamic_cast<UIText*>(frame->GetVChildFrames()[index]->GetChild("itemCount"));

	if (text->GetText() != "1")
	{
		text->SetText(to_string(stoi(text->GetText()) - 1));
	}

	else
	{
		for (int i = index; i < _itemList.size() - 1; i++)
		{
			text = dynamic_cast<UIText*>(frame->GetVChildFrames()[i]->GetChild("itemCount"));
			UIText* textNext = dynamic_cast<UIText*>(frame->GetVChildFrames()[i + 1]->GetChild("itemCount"));

			text->SetText(textNext->GetText());
		}

		dynamic_cast<UIText*>(frame->GetVChildFrames()[_itemList.size() - 1]->GetChild("itemCount"))->SetText("0");

		removeItem(index);
	}

	
	SetInventoryUI();
}

void Inventory::removeItem(int index)
{
	_itemList.erase(_itemList.begin() + index);
}

void Inventory::CheckItemDoubleClick()
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory");
	if (frame->GetIsViewing())
	{
		vector<UIFrame*> uiFrames = frame->GetVChildFrames();

		for (int i = 0; i < uiFrames.size(); i++)
		{
			if (PtInRect(&uiFrames[i]->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
			{
				if (uiFrames[i]->GetImage() != nullptr)
				{
					if (INPUT->GetIsOnceClicked())
					{
						INPUT->SetClickTimer(0);
						INPUT->SetIsOnceClicked(false);

						UseItem(i, true);
					}

					else
					{
						INPUT->SetIsOnceClicked(true);
					}
				}
				break;
			}
		}
	}
}

void Inventory::SetInventoryUI()
{
	UIFrame* frame = UIMANAGER->GetPlayerFrame()->GetChild("playerFrame_inventory");

	for (int i = 0; i < frame->GetVChildFrames().size(); i++)
	{
		if (i < _itemList.size())
		{
			frame->GetVChildFrames()[i]->SetImage(_itemList[i]->GetImage());
			dynamic_cast<UIImage*>(frame->GetVChildFrames()[i])->SetFrameX(_itemList[i]->GetFrameX());
			dynamic_cast<UIImage*>(frame->GetVChildFrames()[i])->SetFrameY(_itemList[i]->GetFrameY());
		}

		else
		{
			frame->GetVChildFrames()[i]->SetImage(nullptr);
			dynamic_cast<UIImage*>(frame->GetVChildFrames()[i])->SetFrameX(0);
			dynamic_cast<UIImage*>(frame->GetVChildFrames()[i])->SetFrameY(0);
		}

		if (dynamic_cast<UIText*>(frame->GetVChildFrames()[i]->GetChild("itemCount"))->GetText() == "0")
		{
			frame->GetVChildFrames()[i]->GetChild("itemCount")->SetIsViewing(false);
		}

		else
		{
			frame->GetVChildFrames()[i]->GetChild("itemCount")->SetIsViewing(true);
		}
	}
}