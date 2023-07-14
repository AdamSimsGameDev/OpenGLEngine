#pragma once

#include <glm/glm.hpp>

namespace Cy
{
	struct Colour
	{
	public:
		Colour(const glm::vec3& vec) : r(vec.x), g(vec.y), b(vec.z), a(1.0f) { }
		Colour(const glm::vec4& vec) : r(vec.x), g(vec.y), b(vec.z), a(vec.w) { }

		Colour(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1.0f) { }
		Colour(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) { }

		Colour(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r * _c32m), g(_g * _c32m), b(_b * _c32m), a(1.0f) { }
		Colour(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r * _c32m), g(_g* _c32m), b(_b* _c32m), a(_a* _c32m) { }

		const float& operator[](int index) const
		{
			switch (index)
			{
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			case 3:
				return a;
			}
		}
		float& operator[](int index)
		{
			switch (index)
			{
			case 0:
				return r;
			case 1:
				return g;
			case 2:
				return b;
			case 3:
				return a;
			}
		}

		operator glm::vec4() const { return glm::vec4(r, g, b, a); }

		static Colour White;
		static Colour Black;
		static Colour Red;
		static Colour Green;
		static Colour Blue;
		static Colour Yellow;
		static Colour Magenta;
		static Colour Cyan;
		static Colour Orange;
		static Colour Grey;
		static Colour LightGrey;

		float r, g, b, a;

	private:
		static constexpr float _c32m = 1.0f / 256.0f;
	};
}