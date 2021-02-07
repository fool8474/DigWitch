#include "stdafx.h"
#include "ParticleManager.h"

void particleManager::init()
{
	_opParticle.SetSize(4000); // ObjectPooler �ʱ�ȭ (4000���� �̸� �����س���)
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
	for (int i = 0; i < _vGenerators.size(); i++) // ��������� ������Ʈ
	{
		_vGenerators[i]->update();

		if (_vGenerators[i]->_genLiveTime < 0) // ������ ���� �����⸦ �����Ѵ�
		{
			_vGenerators.erase(_vGenerators.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < _vParticles.size(); i++) // ��ƼŬ���� ������Ʈ
	{
		_vParticles[i]->update();

		if (_vParticles[i]->_time < 0) // ������ ���� ��ƼŬ�� �����Ѵ�
		{
			_opParticle.ReturnObject(_vParticles[i]);	// ObjectPooler�� �ٽ� ��ƼŬ�� ����ִ´�
			_vParticles.erase(_vParticles.begin() + i);	// �ش� ��ƼŬ�� ���ͷκ��� �����Ѵ�
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
	_vGenerators.push_back(pg); // ��ƼŬ ������ ��Ͽ� pg �߰�
	pg->initGenerator(particleType, particleXRandom, particleYRandom, speedChangerX, speedChangerY, xSpeed, ySpeed, xSpeedRandom, ySpeedRandom, angle, angleRandom, gravity, gravityRandom,
		alphaChanger, alpha, particleTime, particleTimeRandom, imageName, genType, genX, genY, genTime, genLiveTime, multipleGenerate);
	// ��ƼŬ ������ �ʱ�ȭ

}

void particleManager::render(HDC hdc)
{
	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->render(hdc); // ��ƼŬ���� �����ϵ��� �Ѵ�
	}
}

particle* particleManager::AddNewParticle()
{
	_vParticles.push_back(_opParticle.PopObject()); // ObjectPooler�κ��� ��ƼŬ�� �ϳ� �޾ƿ� ��ƼŬ ��Ͽ� �ִ´�
	return _vParticles[_vParticles.size() - 1];		// ��� ���� �ָ� �������ش�
}
