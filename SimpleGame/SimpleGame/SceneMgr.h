#pragma once
#pragma comment(lib, "winmm.lib")
#include "object.h"
#include "Renderer.h"
#include <Windows.h>
#include <math.h>

const int MAX_OBJECTS_COUNT = 6;
const int MAX_BULLET_COUNT = 100;
const int MAX_CHARACTER_COUNT = 50;
const int MAX_ARROW_COUNT = 100;

const int OBJECT_BUILDING = 1;
const int OBJECT_CHARACTER = 2;
const int OBJECT_BULLET = 3;
const int OBJECT_ARROW = 4;

const int ARROW_SPEED = 100;
const int BULLET_SPEED = 600;
const int CHARACTER_SPEED = 300;

class Objects;

class SceneMgr
{
private:
	Objects *m_objects[MAX_OBJECTS_COUNT];
	Objects *m_character[MAX_CHARACTER_COUNT];
	Objects *m_bullets[MAX_BULLET_COUNT];
	Objects *m_arrows[MAX_ARROW_COUNT];
	int m_currentCount;
	int m_currentbullet;
	Renderer *m_renderer;

	float teama_cool, teamb_cool;
	int building_image, character_image[2];
	float m_bullet_timer;
	DWORD m_time_a, m_time_b;
	float m_deltime;

public:
	SceneMgr(int x, int y);

	~SceneMgr();

	void Collion(); // ������Ʈ���� �浹 üũ�� ���ִ� �κ� -> �ٸ� ������Ʈ�� �簢�� �浹�ڽ��� �������� �˻� size���� x, y ��ǥ ���

	void Update(); // ������Ʈ�� update ���ִ� �Լ� (Renderer ����)

	void AddObject(float x, float y, float z); // �߰��� ������Ʈ(�ӵ��� -10~10������ ���������� �����س���)

	void CreatBullet();
};