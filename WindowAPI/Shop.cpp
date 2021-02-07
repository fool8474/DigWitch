#include "stdafx.h"
#include "Shop.h"
#include "player.h"
#include "Inventory.h"

HRESULT Shop::init(int id, int x, int y, string imageName)
{
	_id = id;
	_shopX = x;
	_shopY = y;
	_shopImage = IMAGEMANAGER->findImage(imageName);
	_shopRect = RectMake(_shopX, _shopY, _shopImage->getWidth(), _shopImage->getHeight());
	_isSelected = false;
	_scrollPercent = 0.f;

	return S_OK;
}

void Shop::SetNpcVariable(int x, int y, string imageName)
{
	_npcX = x;
	_npcY = y;
	_npcImage = IMAGEMANAGER->findImage(imageName);
}

void Shop::release()
{
}

void Shop::update()
{
	CheckBuyItem();
}

void Shop::render(HDC hdc)
{
	CAMERAMANAGER->Render(hdc, _shopImage, _shopX, _shopY);

	if (_npcImage != nullptr)
	{
		CAMERAMANAGER->Render(hdc, _npcImage, _npcX, _npcY);
	}
}

void Shop::SetShopUIOn()
{
	/*
	UIMANAGER->GetShopFrame()->SetIsViewing(true);
	UIMANAGER->GetCharacterFrame()->SetIsViewing(true);
	UIMANAGER->GetInvenFrame()->SetIsViewing(true);
	UIMANAGER->GetShopFrame()->GetChildFrames()[0]->GetChildFrames().clear();

	for (int i = 0; i < _vItemList.size(); i++)
	{
		UIFrame* frame = new UIFrame();
		frame->init(UIMANAGER->GetShopFrame()->GetX() + 17,
			UIMANAGER->GetShopFrame()->GetY() + i * IMAGEMANAGER->findImage("UI_ShopItem")->getHeight() + 17,
			IMAGEMANAGER->findImage("UI_ShopItem")->getWidth() - 5,
			IMAGEMANAGER->findImage("UI_ShopItem")->getHeight() - 5,
			"UI_ShopItem");
		frame->SetIsViewing(true);

		UIText* textFrame = new UIText();
		textFrame->init(frame->GetX() + 50, frame->GetY() + 3, _vItemList[i].GetName(), FONT::PIX, WORDSIZE::WS_BIG, false, WORDANIMATIONSPEED::WAS_SLOW);
		textFrame->SetIsViewing(true);
		frame->AddFrame(textFrame);

		textFrame = new UIText();
		textFrame->init(frame->GetX() + 300, frame->GetY() + 15, to_string(_vItemList[i].GetPrice()), FONT::PIX, WORDSIZE::WS_BIG, false, WORDANIMATIONSPEED::WAS_SLOW);
		textFrame->SetIsViewing(true);
		frame->AddFrame(textFrame);

		image* itemImage = _vItemList[i].GetImage();
		UIImage* imageFrame = new UIImage();
		imageFrame->init(frame->GetX() + 5, frame->GetY() + 5,
			itemImage->getFrameWidth(), itemImage->getFrameHeight(),
			_vItemList[i].GetImageName(), true, _vItemList[i].GetFrameX(), _vItemList[i].GetFrameY());
		imageFrame->SetIsViewing(true);
		frame->AddFrame(imageFrame);
		UIMANAGER->GetShopFrame()->GetChildFrames()[0]->AddFrame(frame);
	}

	UIScroll* scroll = new UIScroll();
	scroll->init(UIMANAGER->GetShopFrame()->GetX() + 377,
		UIMANAGER->GetShopFrame()->GetY() + 19,
		IMAGEMANAGER->findImage("UI_ShopBar")->getWidth(),
		IMAGEMANAGER->findImage("UI_ShopBar")->getHeight(),
		"UI_ShopBar");
	scroll->SetIsViewing(true);
	scroll->SetTarget(UIMANAGER->GetShopFrame()->GetChildFrames()[0]);
	UIMANAGER->GetShopFrame()->GetChildFrames()[0]->AddFrame(scroll);
	*/
}

void Shop::AddItem(Item item)
{
	_vItemList.push_back(item);
}

void Shop::BuyItem(int index)
{
}

void Shop::CheckBuyItem()
{
	/*
	if (_isSelected)
	{
		UIFrame* frame = UIMANAGER->GetShopFrame();
		vector<UIFrame*> uiFrames = frame->GetVChildFrames()[0]->GetVChildFrames();

		for (int i = 0; i < uiFrames.size() - 1; i++)
		{
			if (!uiFrames[i]->GetIsOutside())
			{
				if (PtInRect(&uiFrames[i]->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
				{
					if (INPUT->GetIsOnceClicked())
					{
						INPUT->SetClickTimer(0);
						INPUT->SetIsOnceClicked(false);
						BuyItem(i);
					}

					else
					{
						INPUT->SetIsOnceClicked(true);
					}

					break;
				}
			}
		}
	}
	*/
}