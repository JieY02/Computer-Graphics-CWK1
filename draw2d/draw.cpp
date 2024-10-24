#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	if (round(aBegin.x) == round(aEnd.x))
	{
		size_t xpos = aBegin.x;
		int delta = ((int)aEnd.y - aBegin.y) / std::abs((int)aEnd.y - aBegin.y);
		for (size_t ypos = aBegin.y; std::abs((int)ypos - aBegin.y) <= std::abs((int)aEnd.y - aBegin.y); ypos += delta)
			aSurface.set_pixel_srgb(xpos, ypos, aColor);

		return;
	}

	if (aBegin.x > aEnd.x) 
	{
		Vec2f tmp = aBegin;
		aBegin = aEnd, aEnd = tmp;
	}

	float k = (aEnd.y - aBegin.y) / (aEnd.x - aBegin.x);
	float b = aBegin.y - aBegin.x * k;
	size_t lastYPos = round(aBegin.y);

	for (size_t xpos = round(aBegin.x); xpos <= round(aEnd.x); ++xpos)
	{
		size_t ypos = round((float) xpos * k + b);
		
		int delta = k > 0 ? 1 : -1;
		for(size_t tmpYPos = lastYPos; tmpYPos * delta <= ypos * delta; tmpYPos += delta)
			aSurface.set_pixel_srgb(xpos, tmpYPos, aColor);

		lastYPos = ypos;
	}
}

void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}

void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;      // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aC0;
	(void)aC1;
	(void)aC2;
}


void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
}

void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
