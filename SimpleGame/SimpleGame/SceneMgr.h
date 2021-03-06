#pragma once
#pragma comment(lib, "winmm.lib")
#include "object.h"
#include "Renderer.h"
#include <Windows.h>
#include "Sound.h"
#include <math.h>
#include <mmsystem.h>

const int MAX_OBJECTS_COUNT = 6;
const int MAX_BULLET_COUNT = 100;
const int MAX_CHARACTER_COUNT = 50;
const int MAX_ARROW_COUNT = 100;

const int OBJECT_BUILDING = 1;
const int OBJECT_CHARACTER = 2;
const int OBJECT_BULLET = 3;
const int OBJECT_ARROW = 4;
const int BACKGROUND = 5;

const int ARROW_SPEED = 100;
const int BULLET_SPEED = 200;
const int CHARACTER_SPEED = 300;

class Objects;

class SceneMgr
{
private:
	Objects *back_ground;
	Objects *m_objects[MAX_OBJECTS_COUNT];
	Objects *m_character[MAX_CHARACTER_COUNT];
	Objects *m_bullets[MAX_BULLET_COUNT];
	Objects *m_arrows[MAX_ARROW_COUNT];
	Sound *m_sound;
	int m_currentCount;
	int m_currentbullet;
	Renderer *m_renderer;
	int m_explosionsound;

	float teama_cool, teamb_cool;
	int building_image, character_image[2], background_image, particle_image[2];
	int wheather_image;
	float m_bullet_timer;
	DWORD m_time_a, m_time_b;
	float total_frames;
	float m_deltime;

public:
	SceneMgr(int x, int y);

	~SceneMgr();

	void Collion(); // 오브잭트간의 충돌 체크를 해주는 부분 -> 다른 오브잭트의 사각형 충돌박스를 기준으로 검사 size값과 x, y 좌표 사용

	void Update(); // 오브잭트를 update 해주는 함수 (Renderer 포함)

	void AddObject(float x, float y, float z); // 추가할 오브잭트(속도는 -10~10사이의 랜덤값으로 설정해놓음)

	void renderer();

	void CreatBullet();
};