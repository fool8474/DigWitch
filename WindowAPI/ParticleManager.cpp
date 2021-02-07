#include "stdafx.h"
#include "ParticleManager.h"

void particleManager::init()
{
	_opParticle.SetSize(4000); // ObjectPooler 초기화 (4000개를 미리 생성해놓음)
}

void particleManager::release()
{
	for (int i = 0; i < _vGenerators.size(); i++)
	{
		_vGenerators[i]->release();
		SAFE_DELETE(_vGenerators[i]);
	}

	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->release();
		SAFE_DELETE(_vParticles[i]);
	}

	releaseSingleton();
}

void particleManager::update()
{
	for (int i = 0; i < _vGenerators.size(); i++) // 생성기들의 업데이트
	{
		_vGenerators[i]->update();

		if (_vGenerators[i]->_genLiveTime < 0) // 수명이 지난 생성기를 제거한다
		{
			_vGenerators.erase(_vGenerators.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < _vParticles.size(); i++) // 파티클들의 업데이트
	{
		_vParticles[i]->update();

		if (_vParticles[i]->_time < 0) // 수명이 지난 파티클을 제거한다
		{
			_opParticle.ReturnObject(_vParticles[i]);	// ObjectPooler에 다시 파티클을 집어넣는다
			_vParticles.erase(_vParticles.begin() + i);	// 해당 파티클을 벡터로부터 제거한다
			i--;
		}
	}
}

void particleManager::AddGenerator(PARTICLETYPE particleType, float particleXRandom, float particleYRandom, float speedChangerX, float speedChangerY,
	float xSpeed, float ySpeed, float xSpeedRandom, float ySpeedRandom, float angle, float angleRandom, float gravity, float gravityRandom,
	float alphaChanger, float alpha, int particleTime, int particleTimeRandom, vector<string> imageName,
	GENERATETYPE genType, float genX, float genY, float genTime, int genLiveTime, int multipleGenerate)
{
	particleGenerator* pg = new particleGenerator();
	_vGenerators.push_back(pg); // 파티클 생성기 목록에 pg 추가
	pg->initGenerator(particleType, particleXRandom, particleYRandom, speedChangerX, speedChangerY, xSpeed, ySpeed, xSpeedRandom, ySpeedRandom, angle, angleRandom, gravity, gravityRandom,
		alphaChanger, alpha, particleTime, particleTimeRandom, imageName, genType, genX, genY, genTime, genLiveTime, multipleGenerate);
	// 파티클 생성기 초기화

}

void particleManager::render(HDC hdc)
{
	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->render(hdc); // 파티클만을 렌더하도록 한다
	}
}

particle* particleManager::AddNewParticle()
{
	_vParticles.push_back(_opParticle.PopObject()); // ObjectPooler로부터 파티클을 하나 받아와 파티클 목록에 넣는다
	return _vParticles[_vParticles.size() - 1];		// 방금 넣은 애를 리턴해준다
}
