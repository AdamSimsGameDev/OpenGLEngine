#pragma once

#include "CoreMinimal.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "CyEngine/Serialization/Serialization.h"

namespace Cy
{
	struct Vector3;
	struct String;

	struct Quat : public glm::quat
	{
	public:
		Quat(const glm::quat& quat) : glm::quat(quat){ }
		Quat(float _x, float _y, float _z, float _w) : glm::quat(_w, _x, _y, _z) { }
		Quat(const Vector3& _xyz, float _w);

		static Quat Inverse(const Quat& quat);

		inline static Quat Conjugate(const Quat& quat)
		{
			return glm::conjugate(quat);
		}

		String ToString() const;

		inline float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
		}

		inline float SqrMagnitude() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}

		static Vector3 ToEuler(const Quat& quat);
		static Quat FromEuler(const Vector3& euler);

		Vector3 xyz() const;

		static Quat Identity;
	};

	struct SerializableQuat : Serializable<SerializableQuat, Quat>
	{
		virtual String GetType() const { return "Quat"; }
		virtual void Serialize(const Quat val, String& buffer) const override;
		virtual void Deserialize(const String& buffer, Quat& out) const override;
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableQuat)
}