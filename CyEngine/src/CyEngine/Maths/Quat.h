#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <sstream>

namespace Cy
{
	struct Vector3;


	struct Quat : public glm::quat
	{
	public:
		Quat(const glm::quat& quat) : glm::quat(quat){ }
		Quat(float _x, float _y, float _z, float _w) : glm::quat(_w, _x, _y, _z) { }
		Quat(const Vector3& _xyz, float _w);

		static Quat Inverse(const Quat& quat);

		inline static Quat Conjugate(const Quat& quat)
		{
			return glm::conjugate(quat);
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

		static Quat Identity;
	};
}