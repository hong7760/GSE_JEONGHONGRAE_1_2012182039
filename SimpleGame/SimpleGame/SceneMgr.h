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
	//elapsed time == rendersecen 1번째 불렸다 = time get time 으로 하나 받아옴 => A renderSecen 두번째 B  => B-A  = elapsed time
public:
	SceneMgr(int x, int y);

	~SceneMgr();

	void Collion(); // 오브잭트간의 충돌 체크를 해주는 부분 -> 다른 오브잭트의 사각형 충돌박스를 기준으로 검사 size값과 x, y 좌표 사용

	void Update(); // 오브잭트를 update 해주는 함수 (Renderer 포함)

	void AddObject(float x, float y, float z, float size); // 추가할 오브잭트(속도는 -10~10사이의 랜덤값으로 설정해놓음)

};