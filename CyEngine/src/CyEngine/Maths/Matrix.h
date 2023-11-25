#pragma once

#include "CoreMinimal.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Cy
{
	struct Quat;
	struct Vector3;
	struct String;

	struct Matrix3x3 : public glm::mat3
	{
	public:
		Matrix3x3(float val) : glm::mat3(val) { }
		Matrix3x3(const glm::mat3& mat) : glm::mat3(mat) { }

		String ToString() const;

		inline static Matrix3x3 Inverse(const Matrix3x3& mat) { return glm::inverse(mat); }
		static Matrix3x3 MatCast(const Quat& rot);
		static Quat QuatCast(const Matrix3x3& mat);
	};

	struct Matrix4x4 : public glm::mat4
	{
	public:		
		Matrix4x4(float val) : glm::mat4(val) { }
		Matrix4x4(const glm::mat4& mat) : glm::mat4(mat) { }

		String ToString() const;

		inline static Matrix4x4 Inverse(const Matrix4x4& mat) { return glm::inverse(mat); }
		static Matrix4x4 MatCast(const Quat& rot);
		static Quat QuatCast(const Matrix4x4& mat);

		static Matrix4x4 Translate(const Matrix4x4& mat, const Vector3& vec);
		static Matrix4x4 Rotate(const Matrix4x4& mat, const float& radians, const Vector3& axis);
	};
}
