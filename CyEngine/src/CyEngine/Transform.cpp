#include "cypch.h"
#include "Transform.h"

namespace Cy
{
	void Transform::SetPosition(Vector3 position)
	{ 
		LocalPosition = InverseTransformPoint(position);
	}

	void Transform::AddPosition(Vector3 position)
	{
		SetPosition(GetPosition() + position);
	}

	void Transform::SetRotation(Quat rotation)
	{
		LocalRotation = rotation;
	}

	void Transform::Rotate(Quat rotation)
	{
		LocalRotation = LocalRotation * rotation;
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
		Vector3 pos_rel = LocalPosition - point;
		// rotate both the relative position and rot
		LocalRotation = LocalRotation * Quat::Inverse(act_rot);
		LocalPosition = (pos_rel * act_rot) + point;
	}

	Matrix4x4 Transform::GetWorldTransformationMatrix() const
	{
		glm::mat4 mat(1.f);
		mat = glm::translate(mat, GetPosition());
		mat *= glm::mat4_cast(GetRotation());
		mat = glm::scale(mat, GetScale());
		return mat;
	}

	void Transform::SetParent(Transform* parent)
	{
		if (Parent != nullptr)
		{
			Parent->Children.Remove(this);
		}
		Parent = parent;
		if (Parent)
		{
			Parent->Children.Add(this);
		}
		SetDirty();
	}

	void Transform::SetDirty()
	{
		// only update dirty boolean if it isn't already dirty 
		if (!isDirty)
		{
			isDirty = true;
			isInverseDirty = true;
			for (Transform* child : Children)
			{
				child->SetDirty();
			}
		}
	}

	Matrix4x4 Transform::GetLocalToWorldMatrix() const
	{
		// if the dirty flag is set, the the 
		// localToWorldMatrix is out of date 
		// and needs to be reclaculated 
		if (isDirty)
		{
			if (Parent == nullptr)
			{
				// if the parent is null then the parent is 
				// the world so the localToWorldMatrix 
				// is the same as local to parent matrix 
				localToWorldMatrix = CalculateLocalToParentMatrix();
			}
			else
			{
				// if there is a parent, then the localToWorldMatrix 
				// is calcualted recursively using the parent's localToWorldMatrix 
				// concatenated with the local to parent matrix 
				localToWorldMatrix = Parent->GetLocalToWorldMatrix() * CalculateLocalToParentMatrix();
			}

			// clear the dirty flag since the 
			// matrix is now up to date 
			isDirty = false;
		}

		return localToWorldMatrix;
	}
	Matrix4x4 Transform::GetWorldToLocalMatrix() const
	{
		if (isInverseDirty)
		{
			// the inverse is out of date 
			// so it needs to be updated 
			// the worldToLocalMatrix is the inverse of 
			// the localToWorldMatrix 
			worldToLocalMatrix = Matrix4x4::Inverse(GetLocalToWorldMatrix());
			// clear the dirty flag since the 
			// matrix is now up to date
			isInverseDirty = false;
		}
		return worldToLocalMatrix;
	}
}
