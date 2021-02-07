#include "stdafx.h"
#include "Object.h"

HRESULT Object::init()
{
	return S_OK;
}

HRESULT Object::init(int xIndex, int yIndex)
{
	return S_OK;
}

void Object::release()
{
}

void Object::update()
{
}

void Object::render(HDC hdc)
{
}

void Object::Move()
{
}

bool Object::Interaction()
{
	return false;
}

void Object::SetBody()
{
}

void Object::DeathAnim()
{

}

void Object::Death()
{
}
