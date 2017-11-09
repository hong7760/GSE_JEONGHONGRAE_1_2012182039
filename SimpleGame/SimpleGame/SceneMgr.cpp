#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr(int x, int y)
{
	m_currentCount = 1;
	m_currentbullet = 0;
	m_renderer = new Renderer(x, y);

	Objects * newobject = new Objects(OBJECT_BUILDING, true, 0,0,0, 0, 0, 0);
	m_objects[0] = newobject;

}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::AddObject(float x, float y, float z)
{
	if (m_currentCount < MAX_OBJECTS_COUNT)
	{
		Objects * newobject = new Objects(OBJECT_CHARACTER, true, x, y, z, rand() % 50 - 2, rand() % 50 - 2, 0);

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
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		if (m_objects[i] && m_objects[i]->m_active)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] && m_objects[j]->m_active)
				{
					if (i == j)
						continue;
					else if (m_objects[i]->collision(m_objects[j]->m_pos, m_objects[j]->size) && m_objects[j]->m_type == OBJECT_BUILDING)
					{
						std::cout << "충돌";
						m_objects[j]->m_life -= m_objects[i]->m_life;
						m_objects[i]->m_life = 0;
						break;
					}
					else
						continue;
					//m_objects[i]->SetColor(1, 1, 1, 1);
				}
			}
		}

	for (int i = 0; i < MAX_BULLET_COUNT; i++)
		if (m_bullets[i] && m_bullets[i]->m_active)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] && m_objects[j]->m_active)
				{
					if (m_bullets[i]->collision(m_objects[j]->m_pos, m_objects[j]->size) && m_objects[j]->m_type == OBJECT_CHARACTER)
					{
						std::cout << "충돌";
						m_objects[j]->m_life -= m_bullets[i]->m_life;
						m_bullets[i]->m_life = 0;
						break;
					}
					else
						continue;
					//m_objects[i]->SetColor(1, 1, 1, 1);
				}
			}
		}

	for (int i = 0; i< MAX_OBJECTS_COUNT; i++)
		for (int j = 0; j < MAX_ARROW_COUNT; j++)
			for (int k = 0; k<MAX_OBJECTS_COUNT; k++)
			{
				if (m_arrows[i][j] && m_arrows[i][j]->m_active)
				{
					if (m_objects[k] && m_objects[k]->m_active)
					{
						if (i == k)
							continue;
						else if (m_arrows[i][j]->collision(m_objects[k]->m_pos, m_objects[k]->size))
						{
							std::cout << "충돌";
							m_objects[k]->m_life -= m_arrows[i][j]->m_life;
							m_arrows[i][j]->m_life = 0;
							break;
						}
						else
							continue;
					}
				}
			}
}

void SceneMgr::Update()
{
	m_time_b = timeGetTime();
	m_deltime = m_time_b - m_time_a;
	CreatBullet();
	//std::cout << m_deltime;

	for (int i = 0; i < MAX_BULLET_COUNT; i++)
		if (m_bullets[i])
		{
			m_bullets[i]->Update(m_deltime);
			m_bullets[i]->Render(*m_renderer);
			if (!m_bullets[i]->m_active)
			{
				m_bullets[i]->~Objects();
				m_currentbullet--;
			}
		}

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

	for (int i = 0; i< MAX_OBJECTS_COUNT; i++)
		for (int j = 0; j < MAX_ARROW_COUNT; j++)
		{
			if (m_arrows[i][j])
			{
				m_arrows[i][j]->Update(m_deltime);
				m_arrows[i][j]->Render(*m_renderer);
				if (m_arrows[i][j]->m_active == false)
				{
					m_arrows[i][j]->~Objects();
				}
			}
		}

	m_bullet_timer += m_deltime;
	m_time_a = m_time_b;
	Collion();
}

void SceneMgr::CreatBullet()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_objects[i] && m_objects[i]->m_active && m_objects[i]->m_type == OBJECT_BUILDING)
		{
			if (m_objects[i]->GetCooltime() > 0.5f)
			{
				m_objects[i]->SetCooltime();
				Objects * newobject = new Objects(OBJECT_BULLET, true, m_objects[i]->m_pos.x, m_objects[i]->m_pos.y, m_objects[i]->m_pos.z, rand() % 200 - 100, rand() % 200 - 100, 0);
				for (int j = 0; j < MAX_BULLET_COUNT; j++)
				{
					if (!m_bullets[j])
					{
						m_bullets[j] = newobject;
						break;
					}
					else if (!m_bullets[j]->m_active)
					{
						m_bullets[j] = newobject;
						break;
					}
				}
			}
		}
		else if (m_objects[i] && m_objects[i]->m_active && m_objects[i]->m_type == OBJECT_CHARACTER)
		{
			if (m_objects[i]->GetCooltime() > 0.5f)
			{
				m_objects[i]->SetCooltime();
				Objects * newobject = new Objects(OBJECT_ARROW, true, m_objects[i]->m_pos.x, m_objects[i]->m_pos.y, m_objects[i]->m_pos.z, rand() % 200 - 100, rand() % 200 - 100, 0);
				for (int j = 0; j < MAX_ARROW_COUNT; j++)
				{
					if (!m_arrows[i][j])
					{
						m_arrows[i][j] = newobject;
						break;
					}
					else if (!m_arrows[i][j]->m_active)
					{
						m_arrows[i][j] = newobject;
						break;
					}
				}
			}
		}
	}
}