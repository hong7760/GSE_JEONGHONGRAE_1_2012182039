
#include "stdafx.h"
#include "object.h"
#include "Renderer.h"

Objects::Objects() : m_pos(0,0,0), color(1,1,1,1), m_vector3(0,0,0)
{
	m_active = false;
	size = 10;
}

Objects::Objects(bool active, float x, float y, float z, float scale, float r, float g, float b, float a, float vectorX , float vectorY , float vectorZ) :
	m_pos(x, y, z), color(r, g, b, a), m_vector3(vectorX, vectorY, vectorZ)
{
	m_life = 10.0f;
	size = scale;
	m_active = active;
}

Objects::~Objects()
{

}

void Objects::Render(Renderer& g_Renderer)
{
	if (m_active)
		g_Renderer.DrawSolidRect(m_pos.x, m_pos.y, m_pos.z, size, color.x, color.y, color.z, color.w);
}

void Objects::Update(float time)
{
	if (m_active)
	{
		ColiderCheck(time);
		/*m_pos += m_vector3 * (time * 0.001f);*/
		m_pos.x = m_pos.x + (m_vector3.x * time * 0.001f);
		m_pos.y = m_pos.y + (m_vector3.y * time * 0.001f);

		m_life -= time * 0.001f;
	}
	if (m_life <= 0)
		ActiveOn(false);
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

void Objects::ColiderCheck(float time)
{
	if (m_vector3.x != 0 && m_pos.x + (m_vector3.x * time * 0.001f) + size/2 > 250)
		m_vector3.x = -m_vector3.x;
	else if(m_vector3.x != 0 && m_pos.x + (m_vector3.x * time * 0.001f) - size/2 < -250)
		m_vector3.x = -m_vector3.x;

	if (m_vector3.y != 0 && m_pos.y + (m_vector3.y * time * 0.001f) + size/2 > 250)
		m_vector3.y = -m_vector3.y;
	else if (m_vector3.y != 0 && m_pos.y + (m_vector3.y * time * 0.001f) - size/2 < -250)
		m_vector3.y = -m_vector3.y;
}

void Objects::ActiveOn(bool active)
{
	m_active = active;
}

bool Objects::collision(float3 target, float scale)
{
	if (m_pos.x + size / 2 > target.x - scale / 2 && m_pos.x - size / 2 < target.x + scale / 2 &&
		m_pos.y + size / 2 > target.y - scale / 2 && m_pos.y - size / 2 < target.y + scale / 2)
		return true;
	else
		return false;
}

void Objects::SetColor(float r, float g, float b, float a)
{
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}