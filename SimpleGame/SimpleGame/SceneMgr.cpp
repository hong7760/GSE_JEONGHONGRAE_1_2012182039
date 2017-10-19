#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr() 
{
	m_currentCount = 0;
}

void SceneMgr::AddObject(float x, float y, float z, float size)
{
	if (m_currentCount < MAX_OBJECTS_COUNT)
	{
		Objects * newobject = new Objects(true, x, y, z, size, 1, 1, 1, 1, rand() % 20 - 10, rand() % 20 - 10, 0);

		m_objects[m_currentCount] = newobject;
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

void SceneMgr::Update(Renderer *m_renderer)
{
	for (int i = 0; i < m_currentCount; i++)
		if (m_objects[i])
			m_objects[i]->Render(*m_renderer);
	Collion();
}