#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


// counts background pixels(tot1), and draw a triangle, [1, 2, 3]
// after that, counts again(tot2) 
// then, draw another triangle, counrs background pixels(tot3) [1, 3, 2 (with empty color)]
// draw again, counts again(tot4) [3, 1, 2] 
// draw again, counts again(tot5) [3, 2, 1 (with empty color)]
// draw again, counts again(tot6) [2, 3, 1]
// draw again, counts again(tot7) [2, 1, 3 (with empty color)]
// finally, tot1, tot3, tot5, tot7 should be in same value
//          tot2, tot4, tot6 should be in same value

std::size_t count_black_pixels(Surface const& aSurface)
{
	std::size_t res = 0;

	auto const stride = aSurface.get_width() << 2;
	for (std::uint32_t x = 0; x < aSurface.get_width(); ++x)
	{
		for (std::uint32_t y = 0; y < aSurface.get_height(); ++y)
		{
			auto const idx = y * stride + (x << 2);
			auto const ptr = aSurface.get_surface_ptr() + idx;

			if (ptr[0] == 0 && ptr[1] == 0 && ptr[2] == 0)
				++res;
		}
	}

	return res;
}

TEST_CASE("Order", "[Order]")
{

	Surface surface(640, 480);
	surface.fill({ 0, 0, 0 });
	const float fbwidth = 640.f;
	const float fbheight = 480.f;

	SECTION("2 flat-bottom 30-degree")
	{
		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(30.f * 3.14 / 180.f) };

		int tot1 = count_black_pixels(surface);

		// Draw triangle [p0, p1, p2] and count again
		draw_triangle_interp(surface, p0, p1, p2, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot2 = count_black_pixels(surface);

		// Draw triangle [p0, p2, p1] with an empty color and count again
		draw_triangle_interp(surface, p0, p2, p1, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot3 = count_black_pixels(surface);

		// Draw triangle [p2, p0, p1] and count again
		draw_triangle_interp(surface, p2, p0, p1, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot4 = count_black_pixels(surface);

		// Draw triangle [p2, p1, p0] with an empty color and count again
		draw_triangle_interp(surface, p2, p1, p0, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot5 = count_black_pixels(surface);

		// Draw triangle [p1, p2, p0] and count again
		draw_triangle_interp(surface, p1, p2, p0, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot6 = count_black_pixels(surface);

		// Draw triangle [p1, p0, p2] with an empty color and count again
		draw_triangle_interp(surface, p1, p0, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot7 = count_black_pixels(surface);

		// Assertions
		REQUIRE(tot1 == tot3);
		REQUIRE(tot1 == tot5);
		REQUIRE(tot1 == tot7);

		REQUIRE(tot2 == tot4);
		REQUIRE(tot2 == tot6);
	}

	SECTION("2 flat-bottom 15-degree")
	{
		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(15.f * 3.14 / 180.f) };

		int tot1 = count_black_pixels(surface);

		// Draw triangle [p0, p1, p2] and count again
		draw_triangle_interp(surface, p0, p1, p2, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot2 = count_black_pixels(surface);

		// Draw triangle [p0, p2, p1] with an empty color and count again
		draw_triangle_interp(surface, p0, p2, p1, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot3 = count_black_pixels(surface);

		// Draw triangle [p2, p0, p1] and count again
		draw_triangle_interp(surface, p2, p0, p1, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot4 = count_black_pixels(surface);

		// Draw triangle [p2, p1, p0] with an empty color and count again
		draw_triangle_interp(surface, p2, p1, p0, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot5 = count_black_pixels(surface);

		// Draw triangle [p1, p2, p0] and count again
		draw_triangle_interp(surface, p1, p2, p0, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot6 = count_black_pixels(surface);

		// Draw triangle [p1, p0, p2] with an empty color and count again
		draw_triangle_interp(surface, p1, p0, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot7 = count_black_pixels(surface);

		// Assertions
		REQUIRE(tot1 == tot3);
		REQUIRE(tot1 == tot5);
		REQUIRE(tot1 == tot7);

		REQUIRE(tot2 == tot4);
		REQUIRE(tot2 == tot6);
	}

	SECTION("2 flat-bottom 1-degree")
	{

		Vec2f p0 = { 0.f, fbheight / 2.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(1.f * 3.14 / 180.f) };

		int tot1 = count_black_pixels(surface);

		// Draw triangle [p0, p1, p2] and count again
		draw_triangle_interp(surface, p0, p1, p2, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot2 = count_black_pixels(surface);

		// Draw triangle [p0, p2, p1] with an empty color and count again
		draw_triangle_interp(surface, p0, p2, p1, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot3 = count_black_pixels(surface);

		// Draw triangle [p2, p0, p1] and count again
		draw_triangle_interp(surface, p2, p0, p1, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot4 = count_black_pixels(surface);

		// Draw triangle [p2, p1, p0] with an empty color and count again
		draw_triangle_interp(surface, p2, p1, p0, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot5 = count_black_pixels(surface);

		// Draw triangle [p1, p2, p0] and count again
		draw_triangle_interp(surface, p1, p2, p0, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot6 = count_black_pixels(surface);

		// Draw triangle [p1, p0, p2] with an empty color and count again
		draw_triangle_interp(surface, p1, p0, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot7 = count_black_pixels(surface);

		// Assertions
		REQUIRE(tot1 == tot3);
		REQUIRE(tot1 == tot5);
		REQUIRE(tot1 == tot7);

		REQUIRE(tot2 == tot4);
		REQUIRE(tot2 == tot6);
	}

	SECTION("1 flat-bottom 30-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(30.f * 3.1415 / 180.0f)), 0.f };

		int tot1 = count_black_pixels(surface);

		// Draw triangle [p0, p1, p2] and count again
		draw_triangle_interp(surface, p0, p1, p2, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot2 = count_black_pixels(surface);

		// Draw triangle [p0, p2, p1] with an empty color and count again
		draw_triangle_interp(surface, p0, p2, p1, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot3 = count_black_pixels(surface);

		// Draw triangle [p2, p0, p1] and count again
		draw_triangle_interp(surface, p2, p0, p1, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot4 = count_black_pixels(surface);

		// Draw triangle [p2, p1, p0] with an empty color and count again
		draw_triangle_interp(surface, p2, p1, p0, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot5 = count_black_pixels(surface);

		// Draw triangle [p1, p2, p0] and count again
		draw_triangle_interp(surface, p1, p2, p0, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot6 = count_black_pixels(surface);

		// Draw triangle [p1, p0, p2] with an empty color and count again
		draw_triangle_interp(surface, p1, p0, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot7 = count_black_pixels(surface);

		// Assertions
		REQUIRE(tot1 == tot3);
		REQUIRE(tot1 == tot5);
		REQUIRE(tot1 == tot7);

		REQUIRE(tot2 == tot4);
		REQUIRE(tot2 == tot6);
	}

	SECTION("1 flat-bottom 15-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(15.f * 3.1415 / 180.0f)), 0.f };

		int tot1 = count_black_pixels(surface);

		// Draw triangle [p0, p1, p2] and count again
		draw_triangle_interp(surface, p0, p1, p2, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot2 = count_black_pixels(surface);

		// Draw triangle [p0, p2, p1] with an empty color and count again
		draw_triangle_interp(surface, p0, p2, p1, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot3 = count_black_pixels(surface);

		// Draw triangle [p2, p0, p1] and count again
		draw_triangle_interp(surface, p2, p0, p1, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot4 = count_black_pixels(surface);

		// Draw triangle [p2, p1, p0] with an empty color and count again
		draw_triangle_interp(surface, p2, p1, p0, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot5 = count_black_pixels(surface);

		// Draw triangle [p1, p2, p0] and count again
		draw_triangle_interp(surface, p1, p2, p0, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot6 = count_black_pixels(surface);

		// Draw triangle [p1, p0, p2] with an empty color and count again
		draw_triangle_interp(surface, p1, p0, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot7 = count_black_pixels(surface);

		// Assertions
		REQUIRE(tot1 == tot3);
		REQUIRE(tot1 == tot5);
		REQUIRE(tot1 == tot7);

		REQUIRE(tot2 == tot4);
		REQUIRE(tot2 == tot6);
	}

	SECTION("1 flat-bottom 1-degree")
	{
		Vec2f p0 = { 0.f, 0.f };
		Vec2f p1 = { fbwidth / 2.f, fbheight / 2.f };
		Vec2f p2 = { (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(1.f * 3.1415 / 180.0f)), 0.f };

		int tot1 = count_black_pixels(surface);

		// Draw triangle [p0, p1, p2] and count again
		draw_triangle_interp(surface, p0, p1, p2, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot2 = count_black_pixels(surface);

		// Draw triangle [p0, p2, p1] with an empty color and count again
		draw_triangle_interp(surface, p0, p2, p1, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot3 = count_black_pixels(surface);

		// Draw triangle [p2, p0, p1] and count again
		draw_triangle_interp(surface, p2, p0, p1, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot4 = count_black_pixels(surface);

		// Draw triangle [p2, p1, p0] with an empty color and count again
		draw_triangle_interp(surface, p2, p1, p0, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot5 = count_black_pixels(surface);

		// Draw triangle [p1, p2, p0] and count again
		draw_triangle_interp(surface, p1, p2, p0, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f }, { 1.f, 1.f, 1.f });
		int tot6 = count_black_pixels(surface);

		// Draw triangle [p1, p0, p2] with an empty color and count again
		draw_triangle_interp(surface, p1, p0, p2, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f });
		int tot7 = count_black_pixels(surface);

		// Assertions
		REQUIRE(tot1 == tot3);
		REQUIRE(tot1 == tot5);
		REQUIRE(tot1 == tot7);

		REQUIRE(tot2 == tot4);
		REQUIRE(tot2 == tot6);
	}
}