#pragma once
#include "singletonBase.h"
#include "particleGenerator.h"
#include "ObjectPooler.h"

class particleManager : public singletonBase <particleManager> // 싱글톤 매니저
{
public:
	objectPool<particle>		_opParticle;	// 파티클들을 ObjectPool을 이용해 관리한다
	vector<particleGenerator*>	_vGenerators;	// 파티클 생성기의 목록
	vector<particle*>			_vParticles;	// 파티클의 목록

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// 생성기를 만든다
	void AddGenerator(PARTICLETYPE particleType, float particleXRandom, float particleYRandom, float speedChangerX, float speedChangerY,
		float xSpeed, float ySpeed, float xSpeedRandom, float ySpeedRandom, float angle, float angleRandom, float gravity, float gravityRandom,
		float alphaChanger, float alpha, int particleTime, int particleTimeRandom, vector<string> imageName,
		GENERATETYPE genType, float genX, float genY, float genTime, int genLiveTime, int multipleGenerate);

	// 파티클을 ObjectPooler로부터 받아온다
	particle* AddNewParticle();
};