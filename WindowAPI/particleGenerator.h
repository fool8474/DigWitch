#pragma once
#include "particle.h"

// ��ƼŬ�� Ÿ��
enum GENERATETYPE 
{
	REGULARGEN,	// ������ �ֱ⸶�� ���������� �����ȴ�
	RANDOMGEN,	// ������ �ֱ⸶�� ���������� �����ȴ�
	ONETIME		// �ѹ��� ���ÿ� �����ȴ�
};

// ���� �ð����� Ÿ�Կ� ���� ��ƼŬ�� ������Ű�� ��ƼŬ ������
class particleGenerator
{
public:
	// PARTICLE //
	PARTICLETYPE	_particleType;

	// Speed
	float			_xSpeed;
	float			_ySpeed;
	float			_xSpeedRandom;
	float			_ySpeedRandom; 
	float			_speedChangerX;
	float			_speedChangerY;
	
	// Angle
	float			_angle;
	float			_angleRandom;
	
	// XY ��ǥ
	float			_particleX;
	float			_particleY;
	float			_particleXRandom;
	float			_particleYRandom;
	
	// ALPHA
	float			_alpha;
	float			_alphaChanger;
	
	// �߷�
	float			_gravity;
	float			_gravityRandom;
	
	// ��ƼŬ ���� �ð�
	int				_particleTime;
	int				_particleTimeRandom;

	// PARTICLE GENERATOR
	GENERATETYPE	_generateType;		// ��ƼŬ�� ���� Ÿ��
	int				_initGenTime;		// �ʱ� ���� �ð�
	int				_genTime;			// �ʱ� ���� �ð��� �������� �ΰ��� �� (�������� �����ð�)
	int				_genTimeRandom;		// �����Ǵ� �ð��� ������ ����
	float			_genX;				// ��ƼŬ �������� ��ġ X
	float			_genY;				// ��ƼŬ �������� ��ġ Y
	int				_genLiveTime;		// ��ƼŬ �����Ⱑ ����ִ� �ð�
	int				_multipleGenerate;	// �ѹ��� ��� ��ƼŬ�� �����ɰ�����
	vector<string>	_vImageName;		// ��ƼŬ�� ���� �̹��� ���

	bool			_isGenerateOnce;	// �ѹ� �����Ǿ����� ���� (ONETIME TYPE���� ���)

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// �������� ��ƼŬ �������� �ʱ�ȭ
	void initGenerator(PARTICLETYPE particleType, float particleXRandom, float particleYRandom, float speedChangerX, float speedChangerY,
		float xSpeed, float ySpeed, float xSpeedRandom, float ySpeedRandom, float angle, float angleRandom, float gravity, float gravityRandom,
		float alphaChanger, float alpha, int particleTime, int particleTimeRandom, vector<string> imageName,
		GENERATETYPE genType, float genX, float genY, float genTime, int genLiveTime, int multipleGenerate);

	void SetGenTimeRandom(int genTimeRandom) { _genTimeRandom = genTimeRandom; }

	// ��ƼŬ �����⿡�� ������ ��ƼŬ�� �ʱ�ȭ
	void initParticle(particle* curParticle);
};

