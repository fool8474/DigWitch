#include "stdafx.h"
#include "GridManager.h"

HRESULT GridManager::init()
{
	_p = new player();
	GetNewField();
	return S_OK;
}

void GridManager::release()
{
}

void GridManager::update()
{
	for (int i = _p->GetXIndex() - 8; i < _p->GetXIndex() + 20; i++)
	{
		if (i < 0 || i >= _curLine) continue;
		for (int j = _p->GetYIndex() - 12; j < _p->GetYIndex() + 12; j++)
		{
			if (j < 0 || j >= FIELDSIZEY) continue;
			_field.at(i).at(j)->update();
		}
	}

	for (int i = 0; i < _objs.size(); i++)
	{
		Object* curObj = _objs[i];
		int x = curObj->GetXIndex();
		int y = curObj->GetYIndex();

		if (x > _p->GetXIndex() - 8 && x < _p->GetXIndex() + 20 &&
			y > _p->GetYIndex() - 12 && y < _p->GetYIndex() + 12)
		{
			curObj->update();
		}
	}

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->update();
	}
}

void GridManager::render(HDC hdc)
{
	for (int i = _p->GetXIndex() - 8; i < _p->GetXIndex() + 20; i++)
	{
		if (i < 0 || i >= GRIDMANAGER->GetCurLine()) continue;
		for (int j = _p->GetYIndex() - 12; j < _p->GetYIndex() + 12; j++)
		{
			if (j < 0 || j >= FIELDSIZEY) continue;
			_field.at(i).at(j)->render(hdc);
		}
	}

	for (int i = 0; i < _objs.size(); i++)
	{
		Object* curObj = _objs[i];
		int x = curObj->GetXIndex();
		int y = curObj->GetYIndex();

		if (x > _p->GetXIndex() - 8 && x < _p->GetXIndex() + 20 &&
			y > _p->GetYIndex() - 12 && y < _p->GetYIndex() + 12)
		{
			curObj->render(hdc);
		}
	}

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->render(hdc);
	}
}

void GridManager::GetNewField()
{
	_curLine = 0;
	for (int i = 0; i < 50; i++)
	{
		GenerateNewLine();
	}
}

void GridManager::GenerateNewLine()
{
	Field* field;

	if (_curLine < 10)
	{
		_field.push_back(vector<Field*>());
		for (int j = 0; j < FIELDSIZEY; j++)
		{
			field = new Field();
			field->init();
			field->SetX(_curLine * 96);
			field->SetY(j * 96);
			if (_curLine == 9) field->SetBuildedRoad(false);
			else field->SetBuildedRoad(true);
			_field[_curLine].push_back(field);
		}
	}

	else
	{
		int level = _curLine / FIELDLEVEL;

		Plant* pt;
		Rock* r;
		Tree* t;
		Spider* mobSpider;
		Dino* mobDino;
		Totem* mobTotem;
		Spike* mobSpike;
		int monsterType = 0;

		_field.push_back(vector<Field*>());

		for (int j = 0; j < FIELDSIZEY; j++)
		{
			field = new Field();
			field->init();
			field->SetX(_curLine * 96);
			field->SetY(j * 96);

			int type = RANDOM->range(levelRandom[level][7]);
			if (type > 17) field->SetBuildedRoad(RANDOM->range(10) < 7 ? 0 : 1);

			if (type < levelRandom[level][0])
			{
				if (level == 0) break;
				pt = new Plant(DATAMANAGER->GetPlant(RANDOM->range(levelBerryIndex[level]) + 0));
				pt->SetX(_curLine * 96);
				pt->SetY(j * 96);
				pt->SetXIndex(_curLine);
				pt->SetYIndex(j);
				pt->SetBody();
				field->SetFieldObject(pt);
				_objs.push_back(pt);
			}

			else if (type < levelRandom[level][1])
			{
				pt = new Plant(DATAMANAGER->GetPlant(RANDOM->range(levelFlowerIndex[level]) + 4));
				pt->SetX(_curLine * 96);
				pt->SetY(j * 96);
				pt->SetXIndex(_curLine);
				pt->SetYIndex(j);
				pt->SetBody();
				field->SetFieldObject(pt);
				_objs.push_back(pt);
			}

			else if (type < levelRandom[level][2])
			{
				if (level == 0) break;
				pt = new Plant(DATAMANAGER->GetPlant(RANDOM->range(levelHurbIndex[level]) + 14));
				pt->SetX(_curLine * 96);
				pt->SetY(j * 96);
				pt->SetXIndex(_curLine);
				pt->SetYIndex(j);
				pt->SetBody();
				field->SetFieldObject(pt);
				_objs.push_back(pt);
			}

			else if (type < levelRandom[level][3])
			{
				pt = new Plant(DATAMANAGER->GetPlant(RANDOM->range(levelMushroomIndex[level]) + 16));
				pt->SetX(_curLine * 96);
				pt->SetY(j * 96);
				pt->SetXIndex(_curLine);
				pt->SetYIndex(j);
				pt->SetBody();
				field->SetFieldObject(pt);
				_objs.push_back(pt);
			}

			else if (type < levelRandom[level][4])
			{
				t = new Tree();
				t->init(_curLine, j);

				t->SetImage(IMAGEMANAGER->findImage("Tree"));
				t->SetBody();
				t->SetFrameX(RANDOM->range(levelTreeIndex[level]));
				t->SetFrameY(0);
				switch (t->GetFrameX())
				{
				case 0: t->SetLevel(0); break;
				case 1: t->SetLevel(1); break;
				case 2: t->SetLevel(2); break;
				case 3: t->SetLevel(3); break;
				case 4: t->SetLevel(4); break;
				}
				t->SetIsinteractable(true);
				field->SetFieldObject(t);
				_objs.push_back(t);
			}

			else if (type < levelRandom[level][5])
			{
				r = new Rock();
				r->init(_curLine, j);

				r->SetImage(IMAGEMANAGER->findImage("Stone"));
				r->SetBody();
				if (levelRock[level])
				{
					r->SetIsMove(RANDOM->range(2));
				}
				else
				{
					r->SetIsMove(false);
				}
				r->SetFrameX(r->GetIsMove() ? 1 : 0);
				r->SetFrameY(0);
				r->SetIsinteractable(false);
				r->SetBlockPlayer(r->GetIsMove() ? 0 : 1);
				field->SetFieldObject(r);
				field->SetBuildedRoad(true);
				_objs.push_back(r);
			}

			else if (type < levelRandom[level][6])
			{
				monsterType = RANDOM->range(levelMonster[level]);
				switch (monsterType)
				{
				case MONSTERTYPE::MT_DINO:
					mobDino = new Dino();
					mobDino->init(_curLine, j);
					mobDino->SetBody();
					field->SetFieldObject(mobDino);
					_objs.push_back(mobDino);
					break;

				case MONSTERTYPE::MT_SPIDER:
					mobSpider = new Spider();
					mobSpider->init(_curLine, j);
					mobSpider->SetBody();
					field->SetFieldObject(mobSpider);
					_objs.push_back(mobSpider);
					break;

				case MONSTERTYPE::MT_SPIKE:
					mobSpike = new Spike();
					mobSpike->init(_curLine, j);
					mobSpike->SetBody();
					field->SetFieldObject(mobSpike);
					_objs.push_back(mobSpike);
					break;

				case MONSTERTYPE::MT_TOTEM:
					mobTotem = new Totem();
					mobTotem->init(_curLine, j);
					mobTotem->SetBody();
					mobTotem->SetDirection((DIRECTION)RANDOM->range(4));
					field->SetFieldObject(mobTotem);
					_objs.push_back(mobTotem);
					break;
				}

				field->SetBuildedRoad(true);
			}

			else {}

			_field[_curLine].push_back(field);
		}
	}

	DrawRoad();

	if (_curLine == 0)
	{
		_sasin = new Sasin();
		_sasin->init(0, 50);
		_sasin->SetPlayer(_p);
	}
	_curLine++;
}

void GridManager::DrawRoad()
{
	Field* field;
	for (int i = _curLine - 30; i < _curLine; i++)
	{
		if (i < 0) continue;
		for (int j = 0; j < FIELDSIZEY; j++)
		{
			field = GetField(i, j);
			field->DrawRoad();
			if (i > 0) GRIDMANAGER->GetField(i - 1, j)->DrawRoad();
			if (j > 0) GRIDMANAGER->GetField(i, j - 1)->DrawRoad();
		}
	}
}
void GridManager::MoveToRight()
{
	GenerateNewLine();

	if (abs(_sasin->GetX() - _p->GetX()) > 700) _sasin->SetX(_p->GetX() - 550);

	if (_curLine > 57)
	{
		for (int i = 0; i < _objs.size(); i++)
		{
			if (_objs[i]->GetXIndex() <= _field[_curLine - 56][0]->GetXIndex())
			{
				_objs.erase(_objs.begin() + i);
				i--;
			}
		}
	}	
}
