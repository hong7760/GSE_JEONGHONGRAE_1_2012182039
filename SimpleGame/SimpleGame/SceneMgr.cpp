#include "stdafx.h"
#include "SceneMgr.h"
#include <random>

SceneMgr::SceneMgr(int x, int y)
{
	m_currentCount = 0;
	m_currentbullet = 0;
	m_renderer = new Renderer(x, y);
	m_sound = new Sound();

	character_image[0] = m_renderer->CreatePngTexture(".\\Resorce\\batSpritesheet.png");
	character_image[1] = m_renderer->CreatePngTexture(".\\Resorce\\bird_sprite.png");
	particle_image[0] = m_renderer->CreatePngTexture(".\\Resorce\\particle_puple.png");
	particle_image[1] = m_renderer->CreatePngTexture(".\\Resorce\\particle_red.png");
	background_image = m_renderer->CreatePngTexture(".\\Resorce\\space_background.png");
	for (int i = 0; i < 3; i++) {
		building_image = m_renderer->CreatePngTexture(".\\Resorce\\castle.png");
		Objects * newobject = new Objects(1, OBJECT_BUILDING, true, 200 - i*200, 300, 0, 0, 0, 0, building_image);
		m_objects[m_currentCount] = newobject;
		m_currentCount++;
	}
	for (int i = 0; i < 3; i++) {
		building_image = m_renderer->CreatePngTexture(".\\Resorce\\cube.png");
		Objects * newobject = new Objects(2, OBJECT_BUILDING, true, 200 - i * 200, -300, 0, 0, 0, 0, building_image);
		m_objects[m_currentCount] = newobject;
		m_currentCount++;
	}

	Objects * newobject = new Objects(1, BACKGROUND, true, 0, 0, 0, 0, 0, 0, background_image);
	back_ground = newobject;

	m_explosionsound = m_sound->CreateSoundA(".\\Dependencies\\SoundSamples\\explosion.wav");
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::AddObject(float x, float y, float z)
{
	int vecx, vecy;
	vecx = rand() % CHARACTER_SPEED - CHARACTER_SPEED/2;
	vecy = CHARACTER_SPEED - abs(vecx);
	Objects * newobject = new Objects(2, OBJECT_CHARACTER, true, x, y, z, vecx, vecy, 0, character_image[1]);

	if (y < 0 && teamb_cool/1000 > 1.0f) {
		for (int i = 0; i < MAX_CHARACTER_COUNT; i++)
		{
			if (!m_character[i])
			{
				m_character[i] = newobject;
				break;
			}
			else if (!m_character[i]->m_active)
			{
				m_character[i] = newobject;
				break;
			}
		}
		teamb_cool = 0;
	}
}

void SceneMgr::Collion()
{
	for (int i = 0; i < MAX_CHARACTER_COUNT; i++)
		if (m_character[i] && m_character[i]->m_active)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] && m_objects[j]->m_active)
				{
					if (m_character[i]->GetTeam() == m_objects[j]->GetTeam())
						continue;
					else if (m_character[i]->collision(m_objects[j]->m_pos, m_objects[j]->size))
					{
						//std::cout << "面倒";
						m_objects[j]->m_life -= m_character[i]->m_life;
						m_character[i]->m_life = 0;
						m_sound->PlaySoundA(m_explosionsound, false, 1.0f);
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
			for (int j = 0; j < MAX_CHARACTER_COUNT; j++)
			{
				if (m_character[j] && m_character[j]->m_active)
				{
					if (m_bullets[i]->collision(m_character[j]->m_pos, m_character[j]->size) && m_character[j]->GetTeam() != m_bullets[i]->GetTeam())
					{
						//std::cout << "面倒";
						m_character[j]->m_life -= m_bullets[i]->m_life;
						m_bullets[i]->m_life = 0;
						m_sound->PlaySoundA(m_explosionsound, false, 1.0f);
						break;
					}
					else
						continue;
				}
			}
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_bullets[j] && m_objects[j]->m_active)
				{
					if (m_bullets[i]->GetTeam() == m_objects[j]->GetTeam())
						continue;
					else if (m_bullets[i]->collision(m_objects[j]->m_pos, m_objects[j]->size))
					{
						//std::cout << "面倒";
						m_objects[j]->m_life -= m_bullets[i]->m_life;
						m_bullets[i]->m_life = 0;
						m_sound->PlaySoundA(m_explosionsound, false, 1.0f);
						break;
					}
					else
						continue;
				}
			}
		}

	for (int i = 0; i < MAX_ARROW_COUNT; i++)
	{
		if (m_arrows[i] && m_arrows[i]->m_active)
		{
			for (int j = 0; j < MAX_CHARACTER_COUNT; j++)
			{
				if (m_character[j] && m_character[j]->m_active)
				{
					if (m_arrows[i]->collision(m_character[j]->m_pos, m_character[j]->size) && m_character[j]->GetTeam() != m_arrows[i]->GetTeam())
					{
						//std::cout << "面倒";
						m_character[j]->m_life -= m_arrows[i]->m_life;
						m_arrows[i]->m_life = 0;
						m_sound->PlaySoundA(m_explosionsound, false, 1.0f);
						break;
					}
					else
						continue;
				}
			}
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] && m_objects[j]->m_active)
				{
					if (m_arrows[i]->GetTeam() == m_objects[j]->GetTeam())
						continue;
					else if (m_arrows[i]->collision(m_objects[j]->m_pos, m_objects[j]->size))
					{
						//std::cout << "面倒";
						m_objects[j]->m_life -= m_arrows[i]->m_life;
						m_arrows[i]->m_life = 0;
						m_sound->PlaySoundA(m_explosionsound, false, 1.0f);
						break;
					}
					else
						continue;
					//m_objects[i]->SetColor(1, 1, 1, 1);
				}
			}
		}
	}
}

void SceneMgr::Update()
{
	m_time_b = timeGetTime();
	m_deltime = m_time_b - m_time_a;
	teama_cool+= m_deltime;
	teamb_cool += m_deltime;
	CreatBullet();
	//std::cout << m_deltime;

	back_ground->Render(*m_renderer);
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

	for (int i = 0; i < MAX_CHARACTER_COUNT; i++)
		if (m_character[i])
		{
			m_character[i]->Update(m_deltime);
			m_character[i]->Render(*m_renderer);
			if (!m_character[i]->m_active)
				m_character[i]->~Objects();
		}

	for (int i = 0; i < MAX_ARROW_COUNT; i++)
		if (m_arrows[i])
		{
			m_arrows[i]->Update(m_deltime);
			m_arrows[i]->Render(*m_renderer);
			if (!m_arrows[i]->m_active)
				m_arrows[i]->~Objects();
		}

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
		if (m_objects[i])
		{
			m_objects[i]->Update(m_deltime);
			m_objects[i]->Render(*m_renderer);
			if (m_objects[i]->m_active == false)
				m_objects[i]->~Objects();
		}

	//for (int i = 0; i< MAX_OBJECTS_COUNT; i++)
	//	for (int j = 0; j < MAX_ARROW_COUNT; j++)
	//	{
	//		if (m_arrows[i][j])
	//		{
	//			m_arrows[i][j]->Update(m_deltime);
	//			m_arrows[i][j]->Render(*m_renderer);
	//			if (m_arrows[i][j]->m_active == false)
	//			{
	//				m_arrows[i][j]->~Objects();
	//			}
	//		}
	//	}

	m_bullet_timer += m_deltime;
	m_time_a = m_time_b;
	Collion();
	m_renderer->DrawText(-50, 370, GLUT_BITMAP_9_BY_15, 1, 1, 1, "Test Text!!!!");
}

void SceneMgr::CreatBullet()
{
	int vecx, vecy;
	Objects * newobject;
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++) {
		if (m_objects[i] && m_objects[i]->m_active)
		{
			if (m_objects[i]->GetCooltime() > 0.5f)
			{
				vecx = rand() % BULLET_SPEED - BULLET_SPEED / 2;
				vecy = BULLET_SPEED - abs(vecx);

				if (m_objects[i]->GetTeam() == 1)
					vecy = -vecy;

				m_objects[i]->SetCooltime();
				if(m_objects[i]->GetTeam() == 1)
					newobject = new Objects(m_objects[i]->GetTeam(), OBJECT_BULLET, true, m_objects[i]->m_pos.x, m_objects[i]->m_pos.y, m_objects[i]->m_pos.z, vecx, vecy, 0, particle_image[1]);
				else 
					newobject = new Objects(m_objects[i]->GetTeam(), OBJECT_BULLET, true, m_objects[i]->m_pos.x, m_objects[i]->m_pos.y, m_objects[i]->m_pos.z, vecx, vecy, 0, particle_image[0]);
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
	}
	if (teama_cool/1000 > 1)
	{
		vecx = rand() % CHARACTER_SPEED - CHARACTER_SPEED/2;
		vecy = CHARACTER_SPEED - abs(vecx);
		Objects * newobject = new Objects(1, OBJECT_CHARACTER, true, rand()%500 - 250, rand()%400, 0, vecx, -vecy, 0, character_image[0]);

		for (int i = 0; i < MAX_CHARACTER_COUNT; i++)
		{
			if (!m_character[i])
			{
				m_character[i] = newobject;
				break;
			}
			else if (!m_character[i]->m_active)
			{
				m_character[i] = newobject;
				break;
			}
		}
		teama_cool = 0;
	}

	for(int i = 0; i < MAX_CHARACTER_COUNT; i++)
		if (m_character[i] && m_character[i]->m_active)
		{
			if (m_character[i]->GetCooltime() > 1.0f)
			{
				vecx = rand() % ARROW_SPEED;
				vecy = ARROW_SPEED - vecx;
				m_character[i]->SetCooltime();
				Objects * newobject = new Objects(m_character[i]->GetTeam(), OBJECT_ARROW, true, m_character[i]->m_pos.x, m_character[i]->m_pos.y, m_character[i]->m_pos.z, vecx, vecy, 0, building_image);
				for (int j = 0; j < MAX_ARROW_COUNT; j++)
				{
					if (!m_arrows[j])
					{
						m_arrows[j] = newobject;
						break;
					}
					else if (!m_arrows[j]->m_active)
					{
						m_arrows[j] = newobject;
						break;
					}
				}
			}
		}
}