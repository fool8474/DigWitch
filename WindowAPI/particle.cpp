#include "stdafx.h"
#include "particle.h"

void particle::init()
{
	_speedChangerX = 0;
	_speedChangerY = 0;
	_xSpeed = 0;
	_ySpeed = 0;
	_angle = 0;
	_x = 0;
	_y = 0;
	_alphaChanger = 0;
	_alpha = 255;
	_time = 0;
	_type = PARTICLETYPE::PT_FOUNTAIN;
}

void particle::initParticle(PARTICLETYPE type, float x, float y, float speedChangerX, float speedChangerY, float xSpeed, float ySpeed, float angle, float alphaChanger, float alpha, float gravity, float time, string name)
{
	_type = type;
	_x = x;
	_y = y;
	_speedChangerX = speedChangerX;
	_speedChangerY = speedChangerY;
	_xSpeed = xSpeed;
	_ySpeed = ySpeed;
	_angle = angle;
	_alphaChanger = alphaChanger;
	_alpha = alpha;
	_time = time;
	_type = type;
	_gravity = gravity;

	_image = IMAGEMANAGER->findImage(name);
}


void particle::release()
{
	SAFE_DELETE(_image);
}

void particle::update()
{
	_time--;

	// 알파 변경
	_alpha -= _alphaChanger;
	if (_alpha < 0) _alpha = 0;

	//스피드 변경
	_xSpeed += _speedChangerX;
	_ySpeed += _speedChangerY;

	// X Y 변경
	switch (_type)
	{
	case PARTICLETYPE::PT_FOUNTAIN: // 중력의 영향도 받음
		_ySpeed -= _gravity;
		_x += cos(_angle) * _xSpeed;
		_y += _ySpeed;

		break;
	case PARTICLETYPE::PT_OPEN:		// 중력의 영향을 받지 않음
		_x += cos(_angle) * _xSpeed;
		_y += -sin(_angle) * _ySpeed;
		break;
	}
}

void particle::render(HDC hdc)
{
	CAMERAMANAGER->AlphaRender(hdc, _image, _x, _y, _alpha);
}

