#include "cypch.h"
#include "Matrix.h"
#include "Quat.h"
#include "Vector.h"
#include "CyEngine/String.h"

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

	String Matrix3x3::ToString() const
	{
		return String::Format("(%f, %f, %f,\n %f, %f, %f,\n %f, %f, %f)", 
			((*this)[0][0]), ((*this)[1][0]), ((*this)[2][0]),
			((*this)[0][1]), ((*this)[1][1]), ((*this)[2][1]),
			((*this)[0][2]), ((*this)[1][2]), ((*this)[2][2]));
	}

	Matrix4x4 Matrix4x4::MatCast(const Quat& rot) { return glm::mat4_cast(rot); }
	Quat Matrix4x4::QuatCast(const Matrix4x4& mat) { return glm::quat_cast(mat); }

	Matrix4x4 Matrix4x4::Translate(const Matrix4x4& mat, const Vector3& vec) { return glm::translate(mat, vec); }
	Matrix4x4 Matrix4x4::Rotate(const Matrix4x4& mat, const float& radians, const Vector3& axis) { return glm::rotate(mat, radians, axis); }
	Matrix4x4 Matrix4x4::Scale(const Matrix4x4& mat, const Vector3& vec) { return glm::scale(mat, vec); }

	String Matrix4x4::ToString() const
	{
		return String::Format("(%f, %f, %f, %f,\n %f, %f, %f, %f,\n %f, %f, %f, %f,\n %f, %f, %f, %f)",
			((*this)[0][0]), ((*this)[1][0]), ((*this)[2][0]), ((*this)[3][0]),
			((*this)[0][1]), ((*this)[1][1]), ((*this)[2][1]), ((*this)[3][1]),
			((*this)[0][2]), ((*this)[1][2]), ((*this)[2][2]), ((*this)[3][2]),
			((*this)[0][3]), ((*this)[1][3]), ((*this)[2][3]), ((*this)[3][3]));
	}

}
