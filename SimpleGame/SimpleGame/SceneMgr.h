#pragma once
#pragma comment(lib, "winmm.lib")
#include "object.h"
#include "Renderer.h"
#include <Windows.h>

const int MAX_OBJECTS_COUNT = 10;

class SceneMgr
{
private:
	Objects *m_objects[MAX_OBJECTS_COUNT];
	int m_currentCount;
	Renderer *m_renderer;

	float m_time_a, m_time_b, m_deltime;
	//elapsed time == rendersecen 1��° �ҷȴ� = time get time ���� �ϳ� �޾ƿ� => A renderSecen �ι�° B  => B-A  = elapsed time
public:
	SceneMgr(int x, int y);

	~SceneMgr();

	void Collion(); // ������Ʈ���� �浹 üũ�� ���ִ� �κ� -> �ٸ� ������Ʈ�� �簢�� �浹�ڽ��� �������� �˻� size���� x, y ��ǥ ���

	void Update(); // ������Ʈ�� update ���ִ� �Լ� (Renderer ����)

	void AddObject(float x, float y, float z, float size); // �߰��� ������Ʈ(�ӵ��� -10~10������ ���������� �����س���)

};