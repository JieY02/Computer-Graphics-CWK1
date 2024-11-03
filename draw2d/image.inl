inline
ColorU8_sRGB_Alpha ImageRGBA::get_pixel( Index aX, Index aY ) const
{
	assert( aX < mWidth && aY < mHeight ); // Leave this at the top of the function.

	Index linearIndex = get_linear_index(aX, aY);

	std::uint8_t r = mData[linearIndex];
	std::uint8_t g = mData[linearIndex + 1];
	std::uint8_t b = mData[linearIndex + 2];
	std::uint8_t a = mData[linearIndex + 3];

	return { r, g, b, a };
}

inline
auto ImageRGBA::get_width() const noexcept -> Index
{
	return mWidth;
}
inline
auto ImageRGBA::get_height() const noexcept -> Index
{
	return mHeight;
}

inline
std::uint8_t* ImageRGBA::get_image_ptr() noexcept
{
	return mData;
}
inline
std::uint8_t const* ImageRGBA::get_image_ptr() const noexcept
{
	return mData;
}

inline
ImageRGBA::Index ImageRGBA::get_linear_index( Index aX, Index aY ) const noexcept
{
	return (aY * mWidth + aX) * 4;
}
