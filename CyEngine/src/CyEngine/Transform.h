#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Components/Component.h"
#include "Maths/Matrix.h"
#include "Maths/Quat.h"
#include "Maths/Vector.h"
#include "generated/Transform.gen.h"

namespace Cy
{
	CLASS()
	class Transform : public Component
	{
		GENERATED_CLASS(Transform)

		friend class InspectorTab;

	public:
		Transform() : LocalPosition(Vector3::Zero), LocalRotation(Quat::Identity), LocalScale(Vector3::One), Parent(nullptr) { }

#if CY_EDITOR
		virtual void EditorTick(float deltaTime) override;
#endif

		void SetPosition(Vector3 position);
		Vector3 GetPosition() const { return Parent ? Parent->TransformPoint(LocalPosition) : LocalPosition; }
		void AddPosition(Vector3 position);

		void SetRotation(Quat rotation);
		Quat GetRotation() const { return Parent ? Parent->GetRotation() * LocalRotation : LocalRotation; }
		void Rotate(Quat rotation);

		Vector3 GetScale() const { return Parent ? Parent->GetScale() * LocalScale : LocalScale; }
		void SetScale(Vector3 scale) { LocalScale = scale; SetDirty(); }

		void RotateAround(const Vector3& point, float degs, const Vector3& axis);
		void RotateAroundRads(const Vector3& point, float rad, const Vector3& axis);

		Vector3 GetForwardVector() const { return InverseTransformDirection(Vector3::Forward); }
		Vector3 GetRightVector() const { return InverseTransformDirection(Vector3::Right); }
		Vector3 GetUpVector() const { return InverseTransformDirection(Vector3::Up); }

		Matrix4x4 GetWorldTransformationMatrix() const;

		void SetParent(Transform* parent, bool keepTransform);
		Transform* GetParent() const { return Parent; }
		const Array<Transform*>& GetChildren() const { return Children; }

		Matrix4x4 CalculateLocalToParentMatrix() const
		{
			return Matrix4x4::Scale(Matrix4x4::Translate(Matrix4x4(1.f), LocalPosition) * glm::mat4_cast(LocalRotation), LocalScale);
		}
		Matrix4x4 GetLocalToWorldMatrix() const;
		Matrix4x4 GetWorldToLocalMatrix() const;

		Vector3 GetLocalPosition() const { return LocalPosition; }
		void SetLocalPosition(Vector3 value)
		{
			LocalPosition = value;
			SetDirty();
		}		
		
		Vector3 GetLocalScale() const { return LocalScale; }
		void SetLocalScale(Vector3 value)
		{
			LocalScale = value;
			SetDirty();
		}		
		
		Quat GetLocalRotation() const { return LocalRotation; }
		void SetLocalRotation(Quat value)
		{
			LocalRotation = value;
			SetDirty();
		}

		Vector3 TransformPoint(Vector3 point) const
		{
			return GetLocalToWorldMatrix() * Vector4(point.x, point.y, point.z, 1.f);
		}

		Vector3 TransformDirection(Vector3 point) const
		{
			return Vector4(point.x, point.y, point.z, 1.f) * GetRotation();
		}

		Vector3 InverseTransformPoint(Vector3 point) const
		{
			return GetWorldToLocalMatrix() * Vector4(point.x, point.y, point.z, 1.f);
		}

		Vector3 InverseTransformDirection(Vector3 point) const
		{
			return Vector4(point.x, point.y, point.z, 1.f) * Quat::Inverse(GetRotation());
		}

	private:
		void SetDirty();

		PROPERTY(DisplayName = "Position")
		Vector3 LocalPosition;
		PROPERTY(DisplayName = "Rotation")
		Vector3 EulerAngles;
		PROPERTY(Hidden)
		Quat LocalRotation;
		PROPERTY(DisplayName = "Scale")
		Vector3 LocalScale;

	private:
		PROPERTY(Hidden)
		Transform* Parent;

		PROPERTY(Hidden)
		Array<Transform*> Children;

		mutable bool isDirty = false;
		mutable Matrix4x4 localToWorldMatrix = Matrix4x4(1.f);

		mutable bool isInverseDirty = false;
		mutable Matrix4x4 worldToLocalMatrix = Matrix4x4(1.f);
	};
}