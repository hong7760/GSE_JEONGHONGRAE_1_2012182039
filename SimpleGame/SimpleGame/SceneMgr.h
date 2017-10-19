#pragma once
#include "object.h"

const int MAX_OBJECTS_COUNT = 500;

class SceneMgr
{
private:
	Objects *m_objects[MAX_OBJECTS_COUNT];
	int m_currentCount;

public:
	SceneMgr();

	void Collion(); // ������Ʈ���� �浹 üũ�� ���ִ� �κ� -> �ٸ� ������Ʈ�� �簢�� �浹�ڽ��� �������� �˻� size���� x, y ��ǥ ���

	void Update(Renderer *m_renderer); // ������Ʈ�� update ���ִ� �Լ� (Renderer ����)

	void AddObject(float x, float y, float z, float size); // �߰��� ������Ʈ(�ӵ��� -10~10������ ���������� �����س���)

};