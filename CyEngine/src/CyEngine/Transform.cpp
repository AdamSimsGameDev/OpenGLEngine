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
}
