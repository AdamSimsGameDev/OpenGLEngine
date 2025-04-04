#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define PI() glm::pi<float>()
#define RAD_TO_DEG 180.f/PI()
#define DEG_TO_RAD PI()/180.f

namespace Cy
{
	class Math
	{
	public:
		static float Min( float a, float b )
		{
			return a > b ? b : a;
		}

		static float Max( float a, float b )
		{
			return a < b ? b : a;
		}

		static float Lerp( float a, float b, float alpha )
		{
			return Max( Min( a + ( b - a ) * alpha, a ), b );
		}

		static float LerpUnclamped( float a, float b, float alpha )
		{
			return a + ( b - a ) * alpha;
		}
	};
}
