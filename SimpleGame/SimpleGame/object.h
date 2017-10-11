#pragma once
class Renderer;

struct float3
{
	float x, y, z;
	float3(float a, float b, float c) {
		x = a; y = b; z = c;
	}

};

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
	float3 pos;
	float4 color;
	float size;

	Objects(float x, float y,float z, float scale, float r, float g, float b, float a);
	~Objects();

	void Render(Renderer& g_Renderer);
};