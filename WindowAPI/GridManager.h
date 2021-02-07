#pragma once
#include "singletonBase.h"
#include "Field.h"
#include "Plant.h"
#include "Rock.h"
#include "Spider.h"
#include "Dino.h"
#include "Spike.h"
#include "Totem.h"
#include "Sasin.h"
#include "Tree.h"
#include "TotemBullet.h"
#include "Player.h"

#define FIELDSIZEX 499
#define FIELDSIZEY 100
#define FIELDLEVEL 100
class GridManager : public singletonBase<GridManager>
{
private:
	vector<vector<Field*>>	_field;
	player* _p;
	vector<Object*> _objs;
	vector<TotemBullet*> _bullets;
	Sasin* _sasin;

	int levelBerryIndex[5] = { 0,1,2,3,4 };
	int levelFlowerIndex[5] = { 2,4,6,8,10 };
	int levelHurbIndex[5] = { 0,1,1,2,2 };
	int levelMushroomIndex[5] = { 1,2,4,6,7 };
	int levelTreeIndex[5] = { 1,2,3,4,5 };
	bool levelRock[5] = { true, true, true, true, true };
	int levelMonster[5] = {2,3,4,4,4};
	
	int levelRandom[5][8] = {
		{0,3,3,6,8,10,12,35},
		{2,5,6,9,11,13,16,35},
		{2,5,6,9,11,14,18,35},
		{2,5,6,9,11,14,18,35},
		{2,5,6,9,11,15,19,35}
	};

	int _curLine;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void GetNewField();
	void GenerateNewLine();
	void DrawRoad();
	void MoveToRight();

	int GetCurLine() { return _curLine; }
	player* GetPlayer() { return _p; }
	Field* GetField(int x, int y) { return _field[x][y]; }
	Sasin* GetSasin() { return _sasin; }
	vector<vector<Field*>>& GetFieldVv() { return _field; }
	vector<TotemBullet*>& GetBullet() { return _bullets; }
	vector<Object*>& GetObjects() { return _objs; }
	void SetCurLine(int line) { _curLine = line; }
};