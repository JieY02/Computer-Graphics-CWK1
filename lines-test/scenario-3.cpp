#include <catch2/catch_amalgamated.hpp>

#include <algorithm>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE("Straight Line", "[Straight]")
{
	Surface surface(640, 480);
	surface.clear();

	SECTION("virtical")
	{
		draw_line_solid(surface,
			{ 100.f, 100.f },
			{ 100.f, 400.f },
			{ 255, 255, 255 }
		);

		std::vector<std::pair<int, int>> line_pixels;

		auto const stride = surface.get_width() << 2;
		for (std::uint32_t y = 0; y < surface.get_height(); ++y) {
			for (std::uint32_t x = 0; x < surface.get_width(); ++x) {
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[0] > 0 && ptr[1] > 0 && ptr[2] > 0) {
					line_pixels.emplace_back(x, y);
				}
			}
		}

		bool is_x_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.first < b.first;
			});

		bool is_y_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.second < b.second;
			});

		REQUIRE((is_x_monotonic && is_y_monotonic));
	}

	SECTION("horizontal")
	{
		draw_line_solid(surface,
			{ 100.f, 100.f },
			{ 400.f, 100.f },
			{ 255, 255, 255 }
		);

		std::vector<std::pair<int, int>> line_pixels;

		auto const stride = surface.get_width() << 2;
		for (std::uint32_t y = 0; y < surface.get_height(); ++y) {
			for (std::uint32_t x = 0; x < surface.get_width(); ++x) {
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[0] > 0 && ptr[1] > 0 && ptr[2] > 0) {
					line_pixels.emplace_back(x, y);
				}
			}
		}

		bool is_x_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.first < b.first;
			});

		bool is_y_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.second < b.second;
			});

		REQUIRE((is_x_monotonic && is_y_monotonic));
	}

	SECTION("steep-virtical")
	{
		draw_line_solid(surface,
			{ 100.f, 100.f },
			{ 110.f, 400.f },
			{ 255, 255, 255 }
		);

		std::vector<std::pair<int, int>> line_pixels;

		auto const stride = surface.get_width() << 2;
		for (std::uint32_t y = 0; y < surface.get_height(); ++y) {
			for (std::uint32_t x = 0; x < surface.get_width(); ++x) {
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[0] > 0 && ptr[1] > 0 && ptr[2] > 0) {
					line_pixels.emplace_back(x, y);
				}
			}
		}

		bool is_x_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.first < b.first;
			});

		bool is_y_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.second < b.second;
			});

		REQUIRE((is_x_monotonic && is_y_monotonic));
	}

	SECTION("steep-horizontal")
	{
		draw_line_solid(surface,
			{ 100.f, 100.f },
			{ 400.f, 110.f },
			{ 255, 255, 255 }
		);

		std::vector<std::pair<int, int>> line_pixels;

		auto const stride = surface.get_width() << 2;
		for (std::uint32_t y = 0; y < surface.get_height(); ++y) {
			for (std::uint32_t x = 0; x < surface.get_width(); ++x) {
				auto const idx = y * stride + (x << 2);
				auto const ptr = surface.get_surface_ptr() + idx;

				if (ptr[0] > 0 && ptr[1] > 0 && ptr[2] > 0) {
					line_pixels.emplace_back(x, y);
				}
			}
		}

		bool is_x_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.first < b.first;
			});

		bool is_y_monotonic = std::is_sorted(line_pixels.begin(), line_pixels.end(),
			[](const std::pair<int, int>& a, const std::pair<int, int>& b) {
				return a.second < b.second;
			});

		REQUIRE((is_x_monotonic && is_y_monotonic));
	}
}