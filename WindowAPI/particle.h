#pragma once

// 파티클의 타입
enum PARTICLETYPE
{
	PT_FOUNTAIN,	// 중력값의 영향을 받는다
	PT_OPEN,		// 중력값의 영향을 받지 않는다
};

// 파티클 하나하나가 되는 클래스
class particle
{
public:
	PARTICLETYPE	_type;			// 파티클 타입
	float			_x;				// 현재 위치 X
	float			_y;				// 현재 위치 Y
	float			_xSpeed;		// 현재 속도 X
	float			_ySpeed;		// 현재 속도 Y
	float			_speedChangerX;	// 속도 증가량 X
	float			_speedChangerY;	// 속도 증가량 Y
	float			_angle;			// 각도
	float			_gravity;		// 중력 (Y값 속도에 영향)
	float			_alpha;			// 알파값
	float			_alphaChanger;	// 알파값 증가량
	int				_time;			// 이 파티클이 살아있는 시간 (이 시간 뒤에 사라짐) 
	image*			_image;			// 선택된 이미지

	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	
	// 실질적인 파티클의 INIT
	void initParticle(PARTICLETYPE type, float x, float y, float speedChangerX, float speedChangerY, float xSpeed, float ySpeed, float angle, float alphaChanger, float alpha, float gravity, float time, string name);
};

