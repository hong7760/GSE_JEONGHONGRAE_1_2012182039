#pragma once
class Renderer;

typedef struct float3
{
	float x, y, z;
	float3(float a, float b, float c) {
		x = a; y = b; z = c;
	}

	float3 operator+=(const float3& number)
	{
		x = x + number.x;
		y = y + number.y;
		z = z + number.z;
		return float3(x, y, z);
	}
}float3, vector3;

struct float4
{
	float x, y, z, w;
	float4(float a, float b, float c, float d) {
		x = a; y = b; z = c; w = d;
	}
};

class Objects
{
public:
	bool m_active;
	float3 m_pos;
	vector3 m_vector3;
	float4 color;
	float size;

	Objects();
	Objects(bool active, float x, float y, float z, float scale, float r, float g, float b, float a, float vectorX = 0, float vectorY = 0, float vectorZ = 0);
	/*Objects(float x, float y,float z, float scale, float r, float g, float b, float a);*/
	~Objects();

	void Render(Renderer& g_Renderer);

	void Update();

	void Setvector(float vectorX, float vectorY, float vectorZ);

	void Setposition(float x, float y, float z);

	void ColiderCheck();

	void ActiveOn(bool active);
};