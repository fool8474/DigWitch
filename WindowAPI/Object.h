#pragma once

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_TREE, OT_ROCK, OT_PLANT, OT_BULLET
};

class Object
{
protected :
	int			_level;
	int			_xIndex;
	int			_yIndex;
	float		_x;
	float		_y;

	int			_frameX;
	int			_frameY;
	int			_frameTimer;
	int			_frameDirection;
	image*		_image;
	RECT		_body;

	float		_moveSpeed;
	bool		_isMove;
	bool		_canCrushing;
	bool		_isInteractable;
	bool        _isDeath;
	bool        _blockPlayer;
	float		_alpha;
	OBJECTTYPE	_objectType;

public :

	virtual HRESULT init();
	virtual HRESULT init(int x, int y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void Move();
	virtual bool Interaction();
	virtual void SetBody();
	virtual void SetDeath() { _isDeath = true; }
	virtual void DeathAnim();
	virtual void Death();

	bool GetIsDeath() { return _isDeath; }
	int GetLevel() { return _level; }
	int GetXIndex() { return _xIndex; }
	int GetYIndex() { return _yIndex; }
	float GetX() { return _x; }
	float GetY() { return _y; }
	int GetFrameX() { return _frameX; }
	int GetFrameY() { return _frameY; }
	bool GetIsMove() { return _isMove; }
	float GetMoveSpeed() { return _moveSpeed; }
	bool GetIsInteractable() { return _isInteractable; }
	bool GetBlockPlayer() { return _blockPlayer; }
	RECT GetBody() { return _body; }
	image* GetImage() { return _image; }
	OBJECTTYPE GetObjectType() { return _objectType; }
	virtual void SetLevel(int level) { _level = level; }
	void SetImage(image* image) { _image = image; }
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
	void SetMoveSpeed(float speed) { _moveSpeed = speed; }
	void SetIsMove(bool move) { _isMove = move; }
	void SetBlockPlayer(bool block) { _blockPlayer = block; }
	void SetIsinteractable(bool interact) { _isInteractable = interact; }
	void SetObjectType(OBJECTTYPE objType) { _objectType = objType; }
	void SetXIndex(int x) { _xIndex = x; }
	void SetYIndex(int y) { _yIndex = y; }
};