#include "image.hpp"

#include <memory>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <stb_image.h>

#include "surface.hpp"

#include "../support/error.hpp"

namespace
{
	struct STBImageRGBA_ : public ImageRGBA
	{
		STBImageRGBA_( Index, Index, std::uint8_t* );
		virtual ~STBImageRGBA_();
	};
}

ImageRGBA::ImageRGBA()
	: mWidth( 0 )
	, mHeight( 0 )
	, mData( nullptr )
{}

ImageRGBA::~ImageRGBA() = default;


std::unique_ptr<ImageRGBA> load_image( char const* aPath )
{
	assert( aPath );

	stbi_set_flip_vertically_on_load( true );

	int w, h, channels;
	stbi_uc* ptr = stbi_load( aPath, &w, &h, &channels, 4 );
	if( !ptr )
		throw Error( "Unable to load image \"%s\"", aPath );

	return std::make_unique<STBImageRGBA_>(
		ImageRGBA::Index(w),
		ImageRGBA::Index(h),
		ptr
	);
}

void blit_masked(Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition)
{
	int startX = static_cast<int>(round(aPosition.x));
	int startY = static_cast<int>(round(aPosition.y));

	for (int y = 0; y < aImage.get_height(); ++y) {
		for (int x = 0; x < aImage.get_width(); ++x) {
			ColorU8_sRGB_Alpha color = aImage.get_pixel(x, y);

			if (color.a >= 128) {
				int targetX = startX + x;
				int targetY = startY + y;

				if (targetX >= 0 && targetX < aSurface.get_width() &&
					targetY >= 0 && targetY < aSurface.get_height()) {
					aSurface.set_pixel_srgb(targetX, targetY, { color.r, color.g, color.b });
				}
			}
		}
	}
}

namespace
{
	STBImageRGBA_::STBImageRGBA_( Index aWidth, Index aHeight, std::uint8_t* aPtr )
	{
		mWidth = aWidth;
		mHeight = aHeight;
		mData = aPtr;
	}

	STBImageRGBA_::~STBImageRGBA_()
	{
		if( mData )
			stbi_image_free( mData );
	}
}
