#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <sstream>

namespace Cy
{
	struct Vector3;


	struct Quat
	{
	public:
		Quat(const glm::quat& quat) : x(quat.x), y(quat.y), z(quat.z), w(quat.w) { }
		Quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }
		Quat(const Vector3& _xyz, float _w);

		operator glm::quat() const { return glm::quat(w, x, y, z); }

		inline Quat operator*(const Quat& other) const { return (glm::quat)*this * (glm::quat)other; }
		inline Quat operator*=(const Quat& other)
		{
			glm::quat o = (glm::quat)*this * (glm::quat)other;
			x = o.x;
			y = o.y;
			z = o.z;
			w = o.w;
		}

		inline bool operator==(const Quat& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }

		static Quat Inverse(const Quat& quat);

		inline static Quat Conjugate(const Quat& quat)
		{
			return Quat(-quat.x, -quat.y, -quat.z, quat.w);
		}

		const float& operator[](int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}
		float& operator[](int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
			return ss.str();
		}

		inline float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
		}

		inline float SqrMagnitude() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		Vector3 xyz() const;

		float x;
		float y;
		float z;
		float w;

		static Quat Identity;
	};
}