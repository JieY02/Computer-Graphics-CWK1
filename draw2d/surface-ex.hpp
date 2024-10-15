#ifndef SURFACE_EX_HPP_7F360986_9DA7_4883_BFE2_055D3E07EF98
#define SURFACE_EX_HPP_7F360986_9DA7_4883_BFE2_055D3E07EF98

// IMPORTANT: DO NOT CHANGE THIS FILE WHEN YOU ARE SOLVING COURSEWORK 1!
//
// This file is only used in the two benchmarking tasks. Other tasks should not
// attempt to utilize it or its contents.

#include "surface.hpp"


class SurfaceEx : public Surface
{
	public:
		SurfaceEx( Index aWidth, Index aHeight );

	public: 
		// SurfaceEx lets you access the surface image data through a mutable
		// pointer. You can change the surface contents more directly through
		// this and bypass the need for set_pixel_srgb().
		//
		// This is required for some of the benchmarking tasks.
		std::uint8_t* get_surface_ptr() noexcept;
};

#include "surface-ex.inl"
#endif // SURFACE_EX_HPP_7F360986_9DA7_4883_BFE2_055D3E07EF98
