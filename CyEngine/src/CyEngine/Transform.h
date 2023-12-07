#pragma once
#include "CyEngine/Core.h"
#include "Maths/Matrix.h"
#include "Maths/Quat.h"
#include "Maths/Vector.h"
#include "generated/Transform.gen.h"

namespace Cy
{
	CLASS()
	class Transform
	{
		GENERATED_CLASS(Transform)

		friend class InspectorTab;

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

		void RotateAround(const Vector3& point, float degs, const Vector3& axis);
		void RotateAroundRads(const Vector3& point, float rad, const Vector3& axis);

		Vector3 GetForwardVector() const { return Rotation * Vector3::Forward; }
		Vector3 GetRightVector() const { return Rotation * Vector3::Right; }
		Vector3 GetUpVector() const { return Rotation * Vector3::Up; }

		PROPERTY()
		Vector3 Position;
		PROPERTY()
		Quat Rotation;
		PROPERTY()
		Vector3 Scale;
	};
}