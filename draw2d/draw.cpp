#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	/*std::fprintf(stderr, "\naBegin: %.3f %.3f\n", aBegin.x, aBegin.y);
	std::fprintf(stderr, "aEnd: %.3f %.3f\n", aEnd.x, aEnd.y);*/
	int startX = round(aBegin.x);
	int startY = round(aBegin.y);
	int endX = round(aEnd.x);
	int endY = round(aEnd.y);

	if (startX == endX)
	{
		int delta = (endY > startY) ? 1 : -1;
		for (size_t ypos = startY; delta * (ypos - startY) <= delta * (endY - startY); ypos += delta)
			aSurface.set_pixel_srgb(startX, ypos, aColor);

		return;
	}

	// Bresenham's line algorithm implementation
	// Reference: 
	int dx = abs(endX - startX);
	int dy = abs(endY - startY);
	int sx = (startX < endX) ? 1 : -1;
	int sy = (startY < endY) ? 1 : -1;
	int e_xy = dx - dy;

	while (startX != endX || startY != endY) {
		// Set the pixel at the current point
		aSurface.set_pixel_srgb(startX, startY, aColor);

		// Calculate error term and adjust coordinates
		int e2 = 2 * e_xy;
		if (e2 > -dy) {
			e_xy -= dy;
			startX += sx;
		}
		if (e2 < dx) {
			e_xy += dx;
			startY += sy;
		}
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
