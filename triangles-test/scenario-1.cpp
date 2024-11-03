#include <catch2/catch_amalgamated.hpp>

#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

bool is_filled(Surface const& aSurface)
{
	static constexpr int kNeighbourOffsets[][2] = {
		{ -1, -1 }, {  0,  -1 }, { +1, -1 },
		{ -1,  0 },              { +1,  0 },
		{ -1, +1 }, {  0,  +1 }, { +1, +1 }
	};
	auto const stride = aSurface.get_width() << 2;
	for (std::uint32_t yp = 0; yp < aSurface.get_height(); ++yp)
	{
		for (std::uint32_t xp = 0; xp < aSurface.get_width(); ++xp)
		{
			// Skip empty pixels
			auto const idx = yp * stride + (xp << 2);
			auto const ptr = aSurface.get_surface_ptr() + idx;

			if (0 == ptr[0] && 0 == ptr[1] && 0 == ptr[2])
				continue;

			// Count non-empty neighbours
			std::size_t nearBackgroundCount = 0;
			for (auto const neighbour : kNeighbourOffsets)
			{
				auto const x = xp + neighbour[0];
				auto const y = yp + neighbour[1];

				// Outside? Note that this check is enough because uint32_t
				// is guaranteed to wrap on overflow.
				if (x >= aSurface.get_width() || y >= aSurface.get_height())
				{
					++nearBackgroundCount;
					continue;
				}

				auto const jdx = y * stride + (x << 2);
				auto const qtr = aSurface.get_surface_ptr() + jdx;

				if (qtr[0] == 255 && qtr[1] == 255 && qtr[2] == 255)
					++nearBackgroundCount;
			}
			if (nearBackgroundCount <= 3)
				return false;
		}
	}

	return true;
}

bool line_detect(std::vector<std::pair<int, int> > edgePoints, Vec2f p0, Vec2f p1)
{
	if (p0.y > p1.y) std::swap(p0, p1);

	std::vector<std::pair<int, int> > linePoints;

	auto startIndex = lower_bound(edgePoints.begin(), edgePoints.end(), std::pair{ round(p0.x), round(p0.y)}) - edgePoints.begin();
	auto endIndex = lower_bound(edgePoints.begin(), edgePoints.end(), std::pair{ round(p1.x), round(p1.y) }) - edgePoints.begin();
	for (startIndex; startIndex <= endIndex; ++startIndex)
	{
		if (edgePoints[startIndex].second >= round(p0.y) && edgePoints[startIndex].second <= round(p1.y))
			linePoints.push_back(edgePoints[startIndex]);
	}

	bool is_x_monotonic = std::is_sorted(linePoints.begin(), linePoints.end(),
		[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.first < b.first;
		});

	bool is_y_monotonic = std::is_sorted(linePoints.begin(), linePoints.end(),
		[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second < b.second;
		});

	return ((is_x_monotonic && is_y_monotonic));
}

bool edge_detect(Surface const& aSurface, Vec2f p0, Vec2f p1, Vec2f p2)
{
	std::vector<std::pair<int, int> > edgePoints;
	static constexpr int kNeighbourOffsets[][2] = {
		{ -1, -1 }, {  0,  -1 }, { +1, -1 },
		{ -1,  0 },              { +1,  0 },
		{ -1, +1 }, {  0,  +1 }, { +1, +1 }
	};
	auto const stride = aSurface.get_width() << 2;
	for (std::uint32_t yp = 0; yp < aSurface.get_height(); ++yp)
	{
		for (std::uint32_t xp = 0; xp < aSurface.get_width(); ++xp)
		{
			auto const idx = yp * stride + (xp << 2);
			auto const ptr = aSurface.get_surface_ptr() + idx;

			if (0 < ptr[0] && 0 < ptr[1] && 0 < ptr[2])
				continue;

			std::size_t nearCount = 0;
			for (auto const neighbour : kNeighbourOffsets)
			{
				auto const x = xp + neighbour[0];
				auto const y = yp + neighbour[1];

				// Outside? Note that this check is enough because uint32_t
				// is guaranteed to wrap on overflow.
				if (x >= aSurface.get_width() || y >= aSurface.get_height())
				{
					++nearCount;
					continue;
				}

				auto const jdx = y * stride + (x << 2);
				auto const qtr = aSurface.get_surface_ptr() + jdx;

				if (qtr[0] == 255 && qtr[1] == 255 && qtr[2] == 255)
					++nearCount;
			}
			if (nearCount)
				edgePoints.push_back(std::make_pair(xp, yp));
		}
	}
	sort(edgePoints.begin(), edgePoints.end());

	bool flag0 = line_detect(edgePoints, p0, p1);
	bool flag1 = line_detect(edgePoints, p2, p1);
	bool flag2 = line_detect(edgePoints, p0, p2);

	return flag0 && flag1 && flag2;
}

// fulfillment detect

TEST_CASE("Filling", "[Filling]")
{
	Surface surface(640, 480);
	surface.fill({ 255, 255, 255 });
	const float fbwidth = 640.f;
	const float fbheight = 480.f;

	SECTION("2 flat-bottom 30-degree")
	{
		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(30.f * 3.14 / 180.f) };

		draw_triangle_interp(surface, p0, p1, p2, {0.f, 0.f, 0.f}, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		REQUIRE((is_filled(surface) == true));
	}

	SECTION("2 flat-bottom 15-degree")
	{
		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(15.f * 3.14 / 180.f) };

		draw_triangle_interp(surface, p0, p1, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		REQUIRE((is_filled(surface) == true));
	}

	SECTION("2 flat-bottom 1-degree")
	{

		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(1.f * 3.14 / 180.f) };

		draw_triangle_interp(surface, p0, p1, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		REQUIRE((is_filled(surface) == true));
	}

	SECTION("1 flat-bottom 30-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(30.f * 3.1415 / 180.0f)), 0.f };

		draw_triangle_interp(surface, p0, p1, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		REQUIRE((is_filled(surface) == true));
	}

	SECTION("1 flat-bottom 15-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(15.f * 3.1415 / 180.0f)), 0.f };

		draw_triangle_interp(surface, p0, p1, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		REQUIRE((is_filled(surface) == true));
	}

	SECTION("1 flat-bottom 1-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(1.f * 3.1415 / 180.0f)), 0.f };

		draw_triangle_interp(surface, p0, p1, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		REQUIRE((is_filled(surface) == true));
	}
}

// edge detect and straight line detect

TEST_CASE("Edge Detect", "[Edge]")
{
	Surface surface(640, 480);
	surface.fill({ 255, 255, 255 });
	const float fbwidth = 640.f;
	const float fbheight = 480.f;

	SECTION("2 flat-bottom 30-degree")
	{
		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(30.f * 3.14 / 180.f) };


	}

	SECTION("2 flat-bottom 15-degree")
	{
		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(15.f * 3.14 / 180.f) };

	}

	SECTION("2 flat-bottom 1-degree")
	{

		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(1.f * 3.14 / 180.f) };

	}

	SECTION("1 flat-bottom 30-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(30.f * 3.1415 / 180.0f)), 0.f };

	}

	SECTION("1 flat-bottom 15-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(15.f * 3.1415 / 180.0f)), 0.f };

	}

	SECTION("1 flat-bottom 1-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(1.f * 3.1415 / 180.0f)), 0.f };

	}
}