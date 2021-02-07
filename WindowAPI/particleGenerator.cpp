#include "stdafx.h"
#include "particleGenerator.h"

void particleGenerator::init()
{
}

void particleGenerator::release()
{
}

void particleGenerator::update()
{
	_genLiveTime--;	// 생성기의 수명
	_genTime--;		// 생성기의 타이머

	if (_genTime < 0) // 타이머가 0보다 작아지면 파티클을 생성한다
	{
		switch (_generateType)
		{
		case REGULARGEN: // 일정 시간 생성 타입
			_genTime = _initGenTime;
			for (int i = 0; i < _multipleGenerate; i++) // _multipleGenerate개 만큼 생성한다
			{
				initParticle(PARTICLEMANAGER->AddNewParticle());
			}
			break;
		case RANDOMGEN: // 랜덤 시간 생성 타입
			_genTime = _initGenTime + RANDOM->range(-_genTimeRandom, _genTimeRandom);
			for (int i = 0; i < _multipleGenerate; i++)
			{
				initParticle(PARTICLEMANAGER->AddNewParticle());
			}
			break;
		case ONETIME: // 1회성 생성 타입
			if (!_isGenerateOnce)
			{
				for (int i = 0; i < _multipleGenerate; i++)
				{
					initParticle(PARTICLEMANAGER->AddNewParticle());
				}
				_isGenerateOnce = true;	// 1회 생성했다는 것을 알림
				_genLiveTime = 0; // 생성한 뒤에는 바로 사라지도록 처리한다
			}
			break;
		}
	}

}

void particleGenerator::render(HDC hdc)
{
	// 생성기는 렌더될 일이 없다!
}


void particleGenerator::initGenerator(PARTICLETYPE particleType, float particleXRandom, float particleYRandom, float speedChangerX, float speedChangerY,
	float xSpeed, float ySpeed, float xSpeedRandom, float ySpeedRandom, float angle, float angleRandom, float gravity, float gravityRandom,
	float alphaChanger, float alpha, int particleTime, int particleTimeRandom, vector<string> imageName,
	GENERATETYPE genType, float genX, float genY, float genTime, int genLiveTime, int multipleGenerate)
{
	_speedChangerX = speedChangerX;
	_speedChangerY = speedChangerY;
	_xSpeedRandom = xSpeedRandom;
	_ySpeedRandom = ySpeedRandom;
	_xSpeed = xSpeed;
	_ySpeed = ySpeed;
	_angleRandom = angleRandom;
	_angle = angle;
	_particleXRandom = particleXRandom;
	_particleYRandom = particleYRandom;
	_particleX = _genX = genX;
	_particleY = _genY = genY;
	_alphaChanger = alphaChanger;
	_gravityRandom = gravityRandom;
	_gravity = gravity;
	_alpha = alpha;
	_particleType = particleType;
	_particleTimeRandom = particleTimeRandom;
	_particleTime = particleTime;
	_vImageName = imageName;

	_generateType = genType;
	_initGenTime = _genTime = genTime;
	_genLiveTime = genLiveTime;
	_multipleGenerate = multipleGenerate;

	_genTimeRandom = 3;
	_isGenerateOnce = false;
}

void particleGenerator::initParticle(particle* curParticle)
{
	curParticle->initParticle(_particleType,												// 파티클 타입 선택
		_particleX + RANDOM->range(-_particleXRandom / 2, _particleXRandom / 2),			// X좌표에 랜덤성 추가
		_particleY + RANDOM->range(-_particleYRandom / 2, _particleYRandom / 2),			// Y좌표에 랜덤성 추가
		_speedChangerX, _speedChangerY,														// 스피드 XY 변화량
		_xSpeed + RANDOM->range(-_xSpeedRandom / 2, _xSpeedRandom / 2),						// X스피드 랜덤성 추가
		_ySpeed + RANDOM->range(-_ySpeedRandom / 2, _ySpeedRandom / 2),						// Y스피드 랜덤성 추가
		_angle + RANDOM->range(-_angleRandom / 2, _angleRandom / 2),						// 각도 랜덤성 추가
		_alphaChanger, _alpha,																// 알파와 알파 변화량
		_gravity + RANDOM->range(-_gravityRandom / 2, _gravityRandom / 2),					// 중력에 랜덤성 추가
		_particleTime + RANDOM->range(-_particleTimeRandom / 2, _particleTimeRandom / 2),	// 파티클 생존 시간에 랜덤성 추가
		_vImageName[RANDOM->range((int)_vImageName.size())]											// 이미지 중 하나를 선택해 파티클에 입력
	);
}
