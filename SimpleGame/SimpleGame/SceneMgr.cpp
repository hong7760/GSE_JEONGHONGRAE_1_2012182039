#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr(int x, int y) 
{
	m_currentCount = 0;
	m_renderer = new Renderer(x, y);
	m_time_a = (float)timeGetTime();
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::AddObject(float x, float y, float z, float size)
{
	if (m_currentCount < MAX_OBJECTS_COUNT)
	{
		Objects * newobject = new Objects(true, x, y, z, size, 1, 1, 1, 1, rand() % 50 - 2, rand() % 50 - 2, 0);

		for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		{
			if (!m_objects[i])
			{
				m_objects[i] = newobject;
				break;
			}
			else if (!m_objects[i]->m_active)
			{
				m_objects[i] = newobject;
				break;
			}
		}
		m_currentCount += 1;
	}
}

void SceneMgr::Collion()
{
	for(int i = 0; i < m_currentCount; i++)
		for (int j = 0; j < m_currentCount; j++)
		{
			if (i == j)
				continue;
			else if (m_objects[i]->collision(m_objects[j]->m_pos, m_objects[j]->size))
			{
				m_objects[i]->SetColor(1, 0, 0, 1);
				break;
			}
			else
				m_objects[i]->SetColor(1, 1, 1, 1);
		}
}

void SceneMgr::Update()
{
	m_time_b = (float)timeGetTime();
	m_deltime = m_time_b - m_time_a;
	std::cout<< m_deltime;


	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		if (m_objects[i])
		{
			m_objects[i]->Update(m_deltime);
			m_objects[i]->Render(*m_renderer);
			if (m_objects[i]->m_active == false)
			{
				m_objects[i]->~Objects();
				m_currentCount -= 1;
			}
		}

	m_time_a = m_time_b;
	Collion();
}