
#include "stdafx.h"
#include "object.h"
#include "Renderer.h"

Objects::Objects() : m_pos(0,0,0), color(0,0,0,1), m_vector3(0,0,0)
{
	size = 10;
}

Objects::Objects(bool active, float x, float y, float z, float scale, float r, float g, float b, float a, float vectorX , float vectorY , float vectorZ) :
	m_pos(x, y, z), color(r, g, b, a), m_vector3(vectorX, vectorY, vectorZ)
{
	size = scale;
	m_active = active;
}



void Objects::Render(Renderer& g_Renderer)
{
	if (m_active)
	{
		Update();
		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, m_pos.z, size, color.x, color.y, color.z, color.w);
	}
}

void Objects::Update()
{
	ColiderCheck();
	m_pos += m_vector3;
}

void Objects::Setvector(float vectorX, float vectorY, float vectorZ)
{
	m_vector3.x = vectorX;
	m_vector3.y = vectorY;
	m_vector3.z = vectorZ;
}

void Objects::Setposition(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Objects::ColiderCheck()
{
	if (m_vector3.x != 0 && m_pos.x + m_vector3.x + size/2 > 250)
		m_vector3.x = -m_vector3.x;
	else if(m_vector3.x != 0 && m_pos.x + m_vector3.x - size/2 < -250)
		m_vector3.x = -m_vector3.x;

	if (m_vector3.y != 0 && m_pos.y + m_vector3.y + size/2 > 250)
		m_vector3.y = -m_vector3.y;
	else if (m_vector3.y != 0 && m_pos.y + m_vector3.y - size/2 < -250)
		m_vector3.y = -m_vector3.y;
}

void Objects::ActiveOn(bool active)
{
	m_active = active;
}