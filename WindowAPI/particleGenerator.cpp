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
	_genLiveTime--;	// �������� ����
	_genTime--;		// �������� Ÿ�̸�

	if (_genTime < 0) // Ÿ�̸Ӱ� 0���� �۾����� ��ƼŬ�� �����Ѵ�
	{
		switch (_generateType)
		{
		case REGULARGEN: // ���� �ð� ���� Ÿ��
			_genTime = _initGenTime;
			for (int i = 0; i < _multipleGenerate; i++) // _multipleGenerate�� ��ŭ �����Ѵ�
			{
				initParticle(PARTICLEMANAGER->AddNewParticle());
			}
			break;
		case RANDOMGEN: // ���� �ð� ���� Ÿ��
			_genTime = _initGenTime + RANDOM->range(-_genTimeRandom, _genTimeRandom);
			for (int i = 0; i < _multipleGenerate; i++)
			{
				initParticle(PARTICLEMANAGER->AddNewParticle());
			}
			break;
		case ONETIME: // 1ȸ�� ���� Ÿ��
			if (!_isGenerateOnce)
			{
				for (int i = 0; i < _multipleGenerate; i++)
				{
					initParticle(PARTICLEMANAGER->AddNewParticle());
				}
				_isGenerateOnce = true;	// 1ȸ �����ߴٴ� ���� �˸�
				_genLiveTime = 0; // ������ �ڿ��� �ٷ� ��������� ó���Ѵ�
			}
			break;
		}
	}

}

void particleGenerator::render(HDC hdc)
{
	// ������� ������ ���� ����!
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
	curParticle->initParticle(_particleType,												// ��ƼŬ Ÿ�� ����
		_particleX + RANDOM->range(-_particleXRandom / 2, _particleXRandom / 2),			// X��ǥ�� ������ �߰�
		_particleY + RANDOM->range(-_particleYRandom / 2, _particleYRandom / 2),			// Y��ǥ�� ������ �߰�
		_speedChangerX, _speedChangerY,														// ���ǵ� XY ��ȭ��
		_xSpeed + RANDOM->range(-_xSpeedRandom / 2, _xSpeedRandom / 2),						// X���ǵ� ������ �߰�
		_ySpeed + RANDOM->range(-_ySpeedRandom / 2, _ySpeedRandom / 2),						// Y���ǵ� ������ �߰�
		_angle + RANDOM->range(-_angleRandom / 2, _angleRandom / 2),						// ���� ������ �߰�
		_alphaChanger, _alpha,																// ���Ŀ� ���� ��ȭ��
		_gravity + RANDOM->range(-_gravityRandom / 2, _gravityRandom / 2),					// �߷¿� ������ �߰�
		_particleTime + RANDOM->range(-_particleTimeRandom / 2, _particleTimeRandom / 2),	// ��ƼŬ ���� �ð��� ������ �߰�
		_vImageName[RANDOM->range((int)_vImageName.size())]											// �̹��� �� �ϳ��� ������ ��ƼŬ�� �Է�
	);
}
