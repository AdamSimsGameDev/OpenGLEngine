#include "cypch.h"
#include "Transform.h"

namespace Cy
{
	void Transform::SetPosition(Vector3 position)
	{ 
		Position = position;
	}

	void Transform::AddPosition(Vector3 position)
	{
		Position = Position + position;
	}

	void Transform::SetRotation(Quat rotation)
	{
		Rotation = rotation;
	}

	void Transform::Rotate(Quat rotation)
	{
		Rotation = Rotation * rotation;
	}

	void Transform::SetScale(Vector3 scale)
	{
		Scale = scale;
	}

	Matrix4x4 Transform::GetWorldTransformationMatrix() const
	{
		glm::mat4 mat;
		mat = glm::translate(mat, Position);
		mat = glm::scale(mat, Scale);
		mat *= glm::mat4_cast(Rotation);
		return mat;
	}

	void Transform::RotateAround(const Vector3& point, float degs, const Vector3& axis)
	{
		RotateAroundRads(point, DEG_TO_RAD * degs, axis);
	}

	void Transform::RotateAroundRads(const Vector3& point, float rad, const Vector3& axis)
	{
		// create the rotation matrix
		Matrix4x4 rot_mat = Matrix4x4::Rotate(Matrix4x4(1.f), rad, axis);
		// get the rotation quat
		Quat act_rot = Matrix4x4::QuatCast(rot_mat);
		// get the position relative to the point
		Vector3 pos_rel = Position - point;
		// rotate both the relative position and rot
		Rotation = Rotation * Quat::Inverse(act_rot);
		Position = (pos_rel * act_rot) + point;
	}
}
