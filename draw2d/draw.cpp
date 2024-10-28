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

	draw_line_solid(aSurface, aP0, aP1, aColor);
	draw_line_solid(aSurface, aP0, aP2, aColor);
	draw_line_solid(aSurface, aP2, aP1, aColor);

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

void draw_triangle_interp(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2)
{
	if (aP0.y > aP1.y) std::swap(aP0, aP1), std::swap(aC0, aC1);
	if (aP0.y > aP2.y) std::swap(aP0, aP2), std::swap(aC0, aC2);
	if (aP1.y > aP2.y) std::swap(aP1, aP2), std::swap(aC1, aC2);

	auto is_within_bound = [&](int xpos, int ypos) -> bool {
		auto height = aSurface.get_height();
		auto width = aSurface.get_width();
		return (xpos < width) && (xpos >= 0) && (ypos < height) && (ypos >= 0);
		};

	auto barycentric_weights = [](Vec2f p, Vec2f v0, Vec2f v1, Vec2f v2) -> std::tuple<float, float, float> {
		float denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
		float lambda0 = ((v1.y - v2.y) * (p.x - v2.x) + (v2.x - v1.x) * (p.y - v2.y)) / denom;
		float lambda1 = ((v2.y - v0.y) * (p.x - v2.x) + (v0.x - v2.x) * (p.y - v2.y)) / denom;
		float lambda2 = 1.0f - lambda0 - lambda1;
		return { lambda0, lambda1, lambda2 };
		};

	auto convert_to_srgb = [](ColorF color) -> ColorU8_sRGB {
		auto to_srgb = [](float linear) {
			return linear <= 0.0031308f ? linear * 12.92f : 1.055f * pow(linear, 1 / 2.4f) - 0.055f;
			};
		return ColorU8_sRGB{
			static_cast<uint8_t>(std::round(std::clamp(to_srgb(color.r) * 255.f, 0.f, 255.f))),
			static_cast<uint8_t>(std::round(std::clamp(to_srgb(color.g) * 255.f, 0.f, 255.f))),
			static_cast<uint8_t>(std::round(std::clamp(to_srgb(color.b) * 255.f, 0.f, 255.f)))
		};
		};

	for (int y = std::floor(aP0.y); y <= std::ceil(aP2.y); ++y) {
		for (int x = std::floor(std::min({ aP0.x, aP1.x, aP2.x })); x <= std::ceil(std::max({ aP0.x, aP1.x, aP2.x })); ++x) {
			Vec2f p = { static_cast<float>(x), static_cast<float>(y) };
			auto [lambda0, lambda1, lambda2] = barycentric_weights(p, aP0, aP1, aP2);

			// If point is inside triangle
			if (lambda0 >= 0 && lambda1 >= 0 && lambda2 >= 0) {
				ColorF interpolated_color = {
					lambda0 * aC0.r + lambda1 * aC1.r + lambda2 * aC2.r,
					lambda0 * aC0.g + lambda1 * aC1.g + lambda2 * aC2.g,
					lambda0 * aC0.b + lambda1 * aC1.b + lambda2 * aC2.b
				};
				if (is_within_bound(x, y)) aSurface.set_pixel_srgb(x, y, convert_to_srgb(interpolated_color));
			}
		}
	}
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
