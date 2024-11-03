#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


TEST_CASE("Long&Short test", "[Accuracy]")
{
	Surface surface(640, 480);
	surface.clear();

	// To Run the test case, please uncomment follow code

	SECTION("virtical")
	{
		draw_line_solid(surface,
			{ 160.f, 0.f },
			{ 160.f, 120.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 160.f, 0.f },
			{ 160.f, 240.f },
			{ 255, 255, 0 }
		);

		bool flag = 0;
		auto const stride = surface.get_width() << 2;
		for (std::uint32_t x = 0; x < surface.get_width(); ++x)
		{
			for (std::uint32_t y = 0; y < surface.get_height(); ++y)
			{
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[2] == 255)
				{
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		REQUIRE(flag == 0);
	}

	SECTION("horizontal")
	{
		draw_line_solid(surface,
			{ 0.f, 120.f },
			{ 160.f, 120.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 0.f, 120.f },
			{ 320.f, 120.f },
			{ 255, 255, 0 }
		);

		bool flag = 0;
		auto const stride = surface.get_width() << 2;
		for (std::uint32_t x = 0; x < surface.get_width(); ++x)
		{
			for (std::uint32_t y = 0; y < surface.get_height(); ++y)
			{
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[2] == 255)
				{
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		REQUIRE(flag == 0);
	}

	SECTION("steep-virtical")
	{
		draw_line_solid(surface,
			{ 100.f, 0.f },
			{ 101.f, 120.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 100.f, 0.f },
			{ 102.f, 240.f },
			{ 255, 255, 0 }
		);

		bool flag = 0;
		auto const stride = surface.get_width() << 2;
		for (std::uint32_t x = 0; x < surface.get_width(); ++x)
		{
			for (std::uint32_t y = 0; y < surface.get_height(); ++y)
			{
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[2] == 255)
				{
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		REQUIRE(flag == 0);
	}

	SECTION("steep-horizontal")
	{
		draw_line_solid(surface,
			{ 0.f, 120.f },
			{ 160.f, 121.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 0.f, 120.f },
			{ 320.f, 122.f },
			{ 255, 255, 0 }
		);

		bool flag = 0;
		auto const stride = surface.get_width() << 2;
		for (std::uint32_t x = 0; x < surface.get_width(); ++x)
		{
			for (std::uint32_t y = 0; y < surface.get_height(); ++y)
			{
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[2] == 255)
				{
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		REQUIRE(flag == 0);
	}
}
