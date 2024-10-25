#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

void draw_line_solid(Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor)
{
	int startX = round(aBegin.x);
	int startY = round(aBegin.y);
	int endX = round(aEnd.x);
	int endY = round(aEnd.y);

	auto is_within_bound = [&] (int xpos, int ypos) -> bool {
		auto height = aSurface.get_height();
		auto width = aSurface.get_width();
		return (xpos < width) && (xpos >= 0) && (ypos < height) && (ypos >= 0);
		};

	if (startX == endX)
	{
		int delta = (endY > startY) ? 1 : -1;
		for (size_t ypos = startY; delta * (ypos - startY) <= delta * (endY - startY); ypos += delta)
			if(is_within_bound(startX, ypos)) aSurface.set_pixel_srgb(startX, ypos, aColor);

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
		if(is_within_bound(startX, startY))
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
	if (aP0.y > aP1.y) std::swap(aP0, aP1);
	if (aP0.y > aP2.y) std::swap(aP0, aP2);
	if (aP1.y > aP2.y) std::swap(aP1, aP2);
	// aP2.y > aP1.y > aP0.y

	auto is_within_bound = [&](int xpos, int ypos) -> bool {
		auto height = aSurface.get_height();
		auto width = aSurface.get_width();
		return (xpos < width) && (xpos >= 0) && (ypos < height) && (ypos >= 0);
		};

	auto draw_horizontal_line = [&](int y, int xStart, int xEnd) {
		if (xStart > xEnd) std::swap(xStart, xEnd);
		for (int x = xStart; x <= xEnd; ++x) {
			if (is_within_bound(x, y)) aSurface.set_pixel_srgb(x, y, aColor);
		}
		};

	auto interpolate_x = [](Vec2f p1, Vec2f p2, float y) -> int {
		if (p1.y == p2.y) return round(p1.x); // Avoid division by zero
		return round(p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y));
		};

	// Fill bottom flat triangle (aP0, aP1, aP2)
	if (aP1.y == aP2.y) {
		for (int y = round(aP0.y); y <= round(aP1.y); ++y) {
			int xStart = interpolate_x(aP0, aP2, y);
			int xEnd = interpolate_x(aP0, aP1, y);
			draw_horizontal_line(y, xStart, xEnd);
		}
	}
	// Fill top flat triangle (aP0, aP1, aP2)
	else if (aP0.y == aP1.y) {
		for (int y = round(aP0.y); y <= round(aP2.y); ++y) {
			int xStart = interpolate_x(aP0, aP2, y);
			int xEnd = interpolate_x(aP1, aP2, y);
			draw_horizontal_line(y, xStart, xEnd);
		}
	}
	// General case, split the triangle at the y-level of aP1
	else {
		Vec2f aP3 = { interpolate_x(aP0, aP2, aP1.y), aP1.y };
		// Draw bottom part of the triangle (aP0, aP1, aP3)
		for (int y = round(aP0.y); y <= round(aP1.y); ++y) {
			int xStart = interpolate_x(aP0, aP3, y);
			int xEnd = interpolate_x(aP0, aP1, y);
			draw_horizontal_line(y, xStart, xEnd);
		}
		// Draw top part of the triangle (aP1, aP3, aP2)
		for (int y = round(aP1.y); y <= round(aP2.y); ++y) {
			int xStart = interpolate_x(aP1, aP2, y);
			int xEnd = interpolate_x(aP3, aP2, y);
			draw_horizontal_line(y, xStart, xEnd);
		}
	}
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
