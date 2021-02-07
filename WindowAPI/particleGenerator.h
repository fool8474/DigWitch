#pragma once
#include "particle.h"

// 파티클의 타입
enum GENERATETYPE 
{
	REGULARGEN,	// 일정한 주기마다 지속적으로 생성된다
	RANDOMGEN,	// 랜덤한 주기마다 지속적으로 생성된다
	ONETIME		// 한번만 동시에 생성된다
};

// 일정 시간마다 타입에 맞춰 파티클을 생성시키는 파티클 생성기
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
	
	// XY 좌표
	float			_particleX;
	float			_particleY;
	float			_particleXRandom;
	float			_particleYRandom;
	
	// ALPHA
	float			_alpha;
	float			_alphaChanger;
	
	// 중력
	float			_gravity;
	float			_gravityRandom;
	
	// 파티클 생존 시간
	int				_particleTime;
	int				_particleTimeRandom;

	// PARTICLE GENERATOR
	GENERATETYPE	_generateType;		// 파티클의 생성 타입
	int				_initGenTime;		// 초기 생성 시간
	int				_genTime;			// 초기 생성 시간에 랜덤성이 부가된 것 (실질적인 생성시간)
	int				_genTimeRandom;		// 생성되는 시간의 랜덤성 정도
	float			_genX;				// 파티클 생성기의 위치 X
	float			_genY;				// 파티클 생성기의 위치 Y
	int				_genLiveTime;		// 파티클 생성기가 살아있는 시간
	int				_multipleGenerate;	// 한번에 몇개씩 파티클이 생성될것인지
	vector<string>	_vImageName;		// 파티클에 사용될 이미지 목록

	bool			_isGenerateOnce;	// 한번 생성되었는지 여부 (ONETIME TYPE에서 사용)

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// 실질적인 파티클 생성기의 초기화
	void initGenerator(PARTICLETYPE particleType, float particleXRandom, float particleYRandom, float speedChangerX, float speedChangerY,
		float xSpeed, float ySpeed, float xSpeedRandom, float ySpeedRandom, float angle, float angleRandom, float gravity, float gravityRandom,
		float alphaChanger, float alpha, int particleTime, int particleTimeRandom, vector<string> imageName,
		GENERATETYPE genType, float genX, float genY, float genTime, int genLiveTime, int multipleGenerate);

	void SetGenTimeRandom(int genTimeRandom) { _genTimeRandom = genTimeRandom; }

	// 파티클 생성기에서 생성된 파티클의 초기화
	void initParticle(particle* curParticle);
};

