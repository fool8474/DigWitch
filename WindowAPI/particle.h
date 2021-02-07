#pragma once

// ��ƼŬ�� Ÿ��
enum PARTICLETYPE
{
	PT_FOUNTAIN,	// �߷°��� ������ �޴´�
	PT_OPEN,		// �߷°��� ������ ���� �ʴ´�
};

// ��ƼŬ �ϳ��ϳ��� �Ǵ� Ŭ����
class particle
{
public:
	PARTICLETYPE	_type;			// ��ƼŬ Ÿ��
	float			_x;				// ���� ��ġ X
	float			_y;				// ���� ��ġ Y
	float			_xSpeed;		// ���� �ӵ� X
	float			_ySpeed;		// ���� �ӵ� Y
	float			_speedChangerX;	// �ӵ� ������ X
	float			_speedChangerY;	// �ӵ� ������ Y
	float			_angle;			// ����
	float			_gravity;		// �߷� (Y�� �ӵ��� ����)
	float			_alpha;			// ���İ�
	float			_alphaChanger;	// ���İ� ������
	int				_time;			// �� ��ƼŬ�� ����ִ� �ð� (�� �ð� �ڿ� �����) 
	image*			_image;			// ���õ� �̹���

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	// �������� ��ƼŬ�� INIT
	void initParticle(PARTICLETYPE type, float x, float y, float speedChangerX, float speedChangerY, float xSpeed, float ySpeed, float angle, float alphaChanger, float alpha, float gravity, float time, string name);
};

