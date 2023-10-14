#include "cypch.h"
#include "Matrix.h"
#include "Quat.h"
#include "Vector.h"

namespace Cy
{
	Matrix3x3 Matrix3x3::MatCast(const Quat& rot)
	{
		return glm::mat3_cast(rot);
	}

	Quat Matrix3x3::QuatCast(const Matrix3x3& mat)
	{
		return glm::quat_cast(mat);
	}

	Matrix4x4 Matrix4x4::MatCast(const Quat& rot) { return glm::mat4_cast(rot); }
	Quat Matrix4x4::QuatCast(const Matrix4x4& mat) { return glm::quat_cast(mat); }

	Matrix4x4 Matrix4x4::Translate(const Matrix4x4& mat, const Vector3& vec) { return glm::translate(mat, vec); }
	Matrix4x4 Matrix4x4::Rotate(const Matrix4x4& mat, const float& radians, const Vector3& axis) { return glm::rotate(mat, radians, axis); }
}
