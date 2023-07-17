#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <sstream>

namespace Cy
{
	struct Quat;
	struct Vector3;

	struct Matrix3x3 : public glm::mat3
	{
	public:
		Matrix3x3(float val) : glm::mat3(val) { }
		Matrix3x3(const glm::mat3& mat) : glm::mat3(mat) { }

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "("	<< std::to_string((*this)[0][0]) << ", " << std::to_string((*this)[1][0]) << std::to_string((*this)[2][0]) << std::endl 
						<< std::to_string((*this)[0][1]) << ", " << std::to_string((*this)[1][1]) << std::to_string((*this)[2][1]) << std::endl
						<< std::to_string((*this)[0][2]) << ", " << std::to_string((*this)[1][2]) << std::to_string((*this)[2][2]) << std::endl
						<< ")";
			return ss.str();
		}

		inline static Matrix3x3 Inverse(const Matrix3x3& mat) { return glm::inverse(mat); }
		static Matrix3x3 MatCast(const Quat& rot);
		static Quat QuatCast(const Matrix3x3& mat);
	};

	struct Matrix4x4 : public glm::mat4
	{
	public:		
		Matrix4x4(float val) : glm::mat4(val) { }
		Matrix4x4(const glm::mat4& mat) : glm::mat4(mat) { }

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "("	<< std::to_string((*this)[0][0]) << ", " << std::to_string((*this)[1][0]) << std::to_string((*this)[2][0]) << std::to_string((*this)[3][0]) << std::endl 
						<< std::to_string((*this)[0][1]) << ", " << std::to_string((*this)[1][1]) << std::to_string((*this)[2][1]) << std::to_string((*this)[3][1]) << std::endl 
						<< std::to_string((*this)[0][2]) << ", " << std::to_string((*this)[1][2]) << std::to_string((*this)[2][2]) << std::to_string((*this)[3][2]) << std::endl 
						<< std::to_string((*this)[0][3]) << ", " << std::to_string((*this)[1][3]) << std::to_string((*this)[2][3]) << std::to_string((*this)[3][3]) << std::endl 
						<< ")";
			return ss.str();
		}

		inline static Matrix4x4 Inverse(const Matrix4x4& mat) { return glm::inverse(mat); }
		static Matrix4x4 MatCast(const Quat& rot);
		static Quat QuatCast(const Matrix4x4& mat);

		static Matrix4x4 Translate(const Matrix4x4& mat, const Vector3& vec);
		static Matrix4x4 Rotate(const Matrix4x4& mat, const float& radians, const Vector3& axis);
	};
}
