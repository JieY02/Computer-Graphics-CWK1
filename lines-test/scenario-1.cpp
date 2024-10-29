#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE("No Gap(Lines)", "[Gap]")
{
	Surface surface(640, 480);
	surface.clear();
	const float fbwidth = 640.f;
	const float fbheight = 480.f;

	SECTION("virtical")
	{
		Vec2f p0 = {320.f, 0.f};
		Vec2f p1 = {320.f, 240.f};
		Vec2f p2 = {320.f, 480.f};
		draw_line_solid(surface, p0, p1, {255, 255, 255});
		draw_line_solid(surface, p2, p1, { 255, 255, 255 });
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 2); // Four endpoints with one neighbor each
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("horizontal")
	{
		Vec2f p0 = { 0.f, 240.f };
		Vec2f p1 = { 320.f, 240.f };
		Vec2f p2 = { 640.f, 240.f };
		draw_line_solid(surface, p0, p1, { 255, 255, 255 });
		draw_line_solid(surface, p2, p1, { 255, 255, 255 });

		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 2);
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("90-degree angle")
	{
		Vec2f p0 = { 0.f, 240.f };
		Vec2f p1 = { 320.f, 240.f };
		Vec2f p2 = { 320.f, 480.f };
		
		draw_line_solid(surface, p0, p1, { 255, 255, 255 });
		draw_line_solid(surface, p2, p1, { 255, 255, 255 });

		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(((counts[3] == 2 && counts[1] == 3) || (counts[1] == 2)));
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("30-degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, fbheight / 2.f },
			{ fbwidth / 2.f, fbheight / 2.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(30.f * 3.14 / 180.f) },
			{ fbwidth / 2.f, fbheight / 2.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);

		// if using round() or ceil(), counts[1] should be 2
		// if using floor(), counts[1] will be 3

		REQUIRE(((counts[3] == 2 && counts[1] == 3) || (counts[1] == 2)));
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("10-degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, fbheight / 2.f },
			{ fbwidth / 2.f, fbheight / 2.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(10.f * 3.14 / 180.f) },
			{ fbwidth / 2.f, fbheight / 2.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);

		// if using ceil(), counts[1] should be 2
		// if using round() or floor(), counts[1] should be 3
		REQUIRE(((counts[3] == 2 && counts[1] == 3) || (counts[1] == 2)));
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("1-degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, fbheight / 2.f },
			{ fbwidth / 2.f, fbheight / 2.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 0.f,fbheight / 2.f + fbwidth / 2.f * (float)std::tan(1.f * 3.14 / 180.f) },
			{ fbwidth / 2.f, fbheight / 2.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);

		// if using ceil(), counts[1] should be 2
		// if using round() or floor(), counts[1] should be 3
		REQUIRE(((counts[3] == 2 && counts[1] == 3) || (counts[1] == 2)));
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}
}

TEST_CASE("Intersection Point", "[Intersection]")
{
	Surface surface(640, 480);
	surface.clear();
	const float fbwidth = 640.f;
	const float fbheight = 480.f;

	SECTION("1 - degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, 0.f },
			{ fbwidth * 1.f, fbheight * 1.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(1.f * 3.1415 / 180.0f)), 0.f },
			{ fbwidth - (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(1.f * 3.1415 / 180.0f)), fbheight * 1.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 4); // Four endpoints with one neighbor each
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(((counts[3] >= 2 && counts[4] == 0) || (counts[4] == 1)));
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("10 - degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, 0.f },
			{ fbwidth * 1.f, fbheight * 1.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(10.f * 3.1415 / 180.0f)), 0.f },
			{ fbwidth - (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(10.f * 3.1415 / 180.0f)), fbheight * 1.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 4); // Four endpoints with one neighbor each
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(((counts[3] >= 2 && counts[4] == 0) || (counts[4] == 1)));
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("15 - degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, 0.f },
			{ fbwidth * 1.f, fbheight * 1.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(15.f * 3.1415 / 180.0f)), 0.f },
			{ fbwidth - (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(15.f * 3.1415 / 180.0f)), fbheight * 1.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 4); // Four endpoints with one neighbor each
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(((counts[3] >= 2 && counts[4] == 0) || (counts[4] == 1)));
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("30 - degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, 0.f },
			{ fbwidth * 1.f, fbheight * 1.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(30.f * 3.1415 / 180.0f)), 0.f },
			{ fbwidth - (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(30.f * 3.1415 / 180.0f)), fbheight * 1.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 4); // Four endpoints with one neighbor each
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(((counts[3] >= 2 && counts[4] == 0) || (counts[4] == 1)));
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("45 - degree angle")
	{
		draw_line_solid(surface,
			{ 0.f, 0.f },
			{ fbwidth * 1.f, fbheight * 1.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(45.f * 3.1415 / 180.0f)), 0.f },
			{ fbwidth - (std::sqrt((fbwidth / 2.0f) * (fbwidth / 2.0f) + (fbheight / 2.0f) * (fbheight / 2.0f)) * (float)std::sin(45.f * 3.1415 / 180.0f)), fbheight * 1.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(counts[1] == 4); // Four endpoints with one neighbor each
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(((counts[3] >= 2 && counts[4] == 0) || (counts[4] == 1)));
		REQUIRE(0 == counts[0]); // No isolated pixels
	}

	SECTION("90 - degree angle")
	{
		draw_line_solid(surface,
			{ 50.f, 50.f },
			{ 150.f, 150.f },
			{ 255, 255, 255 }
		);
		draw_line_solid(surface,
			{ 50.f, 150.f },
			{ 150.f, 50.f },
			{ 255, 255, 255 }
		);
		auto const counts = count_pixel_neighbours(surface);
		REQUIRE(4 == counts[1]); // Four endpoints with one neighbor each
		REQUIRE(((counts[3] >= 2 && counts[4] == 0) || (counts[4] == 1)));
		REQUIRE(counts[2] > 0);  // Pixels along the lines with two neighbors
		REQUIRE(0 == counts[0]); // No isolated pixels
	}
}
