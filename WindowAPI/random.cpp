#include "stdafx.h"
#include "random.h"

HRESULT random::init()
{
	//�����õ� �ʱ�ȭ
	srand(GetTickCount());

	return S_OK;
}

void random::release()
{
}

int random::range(int num)
{
	if (num == 0) return 0;
	return rand() % num;
}

int random::range(int min, int max)
{
	if (min == max) return min;
	return rand() % (max - min + 1) + min;
}

float random::range(float num)
{
	//3 / 2 = 1 (����)
	//3.0 / 2.0 = 1.5 (�Ǽ�)
	//rand() => 0 ~ 32767
	//RAND_MAX => 32767
	//rand() / RAND_MAX => ���� ���� : 0.0f ~ 1.0f
	if (num == 0) return 0;
	return ((float)rand() / (float)RAND_MAX) * num;
}

float random::range(float min, float max)
{
	if (min == max) return min;
	float rnd = ((float)rand() / (float)RAND_MAX);
	return (rnd * (max - min)) + min;
}
