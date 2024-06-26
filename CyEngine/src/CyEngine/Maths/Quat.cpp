#include "cypch.h"
#include "Quat.h"
#include "Vector.h"
#include "Maths.h"
#include "CyEngine/String.h"

namespace Cy
{
	Quat Quat::Identity = Quat(0.0f, 0.0f, 0.0f, 1.0f);

	Quat::Quat(const Vector3& _xyz, float _w)
		: glm::quat(_w, _xyz.x, _xyz.y, _xyz.z) { }

	Quat Quat::Inverse(const Quat& quat)
	{
		return glm::inverse(quat);
	}

	String Quat::ToString() const
	{
		return String::Format("(%f, %f, %f, %f)", x, y, z, w);
	}

    Vector3 NormaliseAngles(Vector3 euler)
    {
        euler.x = fmod(euler.x + 360.0f, 360.0f);
        euler.y = fmod(euler.y + 360.0f, 360.0f);
        euler.z = fmod(euler.z + 360.0f, 360.0f);
        return euler;
    }

	Vector3 Quat::ToEuler(const Quat& q)
	{
        return glm::eulerAngles(q) * RAD_TO_DEG;
    }

	Quat Quat::FromEuler(const Vector3& euler)
	{
        return glm::quat(euler * DEG_TO_RAD);
    }

	Quat Quat::FromEuler(float x, float y, float z)
	{
		return FromEuler(Vector3(x, y, z));
	}

	Vector3 Quat::xyz() const
	{
		return Vector3(x, y, z);
	}

	void SerializableQuat::Serialize(const Quat val, String& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableQuat::Deserialize(const String& buffer, Quat& out) const
	{
		String s = buffer.Substring(1, buffer.Length() - 2);
		Array<String> spl = String::Split(s, ',');
		out.x = spl.Count() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.Count() > 1 ? std::stof(spl[1]) : 0.0f;
		out.z = spl.Count() > 2 ? std::stof(spl[2]) : 0.0f;
		out.w = spl.Count() > 3 ? std::stof(spl[3]) : 0.0f;
	}
}