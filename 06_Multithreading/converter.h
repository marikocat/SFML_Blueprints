#pragma once

namespace book
{
	namespace converter
	{
		constexpr double PIXELS_PER_METER = 32.0;
		constexpr double PI = 3.14159265358979323846;

		template<typename T>
		constexpr T pixelsToMeters(const T& x)
		{
			return x / PIXELS_PER_METER;
		};

		template<typename T>
		constexpr T metersToPixels(const T& x)
		{
			return x * PIXELS_PER_METER;
		};

		template<typename T>
		constexpr T degToRad(const T& x)
		{
			return PI * x / 180;
		};

		template<typename T>
		constexpr T radToDeg(const T& x)
		{
			return 180.0 * x / PI;
		};
	}
}