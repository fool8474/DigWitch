#pragma once
#include "singletonBase.h"
#include "particleGenerator.h"
#include "ObjectPooler.h"

class particleManager : public singletonBase <particleManager> // �̱��� �Ŵ���
{
public:
	objectPool<particle>		_opParticle;	// ��ƼŬ���� ObjectPool�� �̿��� �����Ѵ�
	vector<particleGenerator*>	_vGenerators;	// ��ƼŬ �������� ���
	vector<particle*>			_vParticles;	// ��ƼŬ�� ���

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// �����⸦ �����
	void AddGenerator(PARTICLETYPE particleType, float particleXRandom, float particleYRandom, float speedChangerX, float speedChangerY,
		float xSpeed, float ySpeed, float xSpeedRandom, float ySpeedRandom, float angle, float angleRandom, float gravity, float gravityRandom,
		float alphaChanger, float alpha, int particleTime, int particleTimeRandom, vector<string> imageName,
		GENERATETYPE genType, float genX, float genY, float genTime, int genLiveTime, int multipleGenerate);

	// ��ƼŬ�� ObjectPooler�κ��� �޾ƿ´�
	particle* AddNewParticle();
};