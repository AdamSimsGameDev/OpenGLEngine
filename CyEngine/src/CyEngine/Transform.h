#pragma once

#include "Maths/Matrix.h"
#include "Maths/Quat.h"
#include "Maths/Vector.h"

namespace Cy
{
	class Transform
	{
	public:
		Transform() : Position(Vector3::Zero), Rotation(Quat::Identity), Scale(Vector3::One) { }

		void SetPosition(Vector3 position);
		Vector3 GetPosition() const { return Position; }
		void AddPosition(Vector3 position);

		void SetRotation(Quat rotation);
		Quat GetRotation() const { return Rotation; }
		void Rotate(Quat rotation);

		void SetScale(Vector3 scale);
		Vector3 GetScale() const { return Scale; }

		Matrix4x4 GetWorldTransformationMatrix() const;

	private:
		Vector3 Position;
		Quat Rotation;
		Vector3 Scale;
	};
}