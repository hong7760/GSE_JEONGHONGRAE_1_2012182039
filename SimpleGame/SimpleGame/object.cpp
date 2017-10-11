
#include "stdafx.h"
#include "object.h"
#include "Renderer.h"

Objects::Objects(float x, float y, float z, float sclae, float r, float g, float b, float a) : 
	pos(x,y,z), color(r,g,b,a)
{
	size = sclae;
}



void Objects::Render(Renderer& g_Renderer)
{
	g_Renderer.DrawSolidRect(pos.x,pos.y,pos.z, size, color.x, color.y, color.z, color.w);
}