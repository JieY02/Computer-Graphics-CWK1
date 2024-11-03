#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"


TEST_CASE("Reversing test", "[!mayfail]")
{
	Surface surface(320, 240);
	surface.clear();

	// To Run the test case, please uncomment follow code

	/*SECTION("virtical")
	{
		draw_line_solid(surface,
			{ 160.f, 0.f },
			{ 160.f, 240.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 160.f, 240.f },
			{ 160.f, 0.f },
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
			{ 320.f, 120.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 320.f, 120.f },
			{ 0.f, 120.f },
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
			{ 165.f, 0.f },
			{ 160.f, 240.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 160.f, 240.f },
			{ 165.f, 0.f },
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
			{ 0.f, 125.f },
			{ 320.f, 120.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 320.f, 120.f },
			{ 0.f, 125.f },
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
	}*/
}
