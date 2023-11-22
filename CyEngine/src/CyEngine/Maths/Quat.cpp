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

	Vector3 Quat::xyz() const
	{
		return Vector3(x, y, z);
	}

	void SerializableQuat::Serialize(const Quat val, std::string& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableQuat::Deserialize(const std::string& buffer, Quat& out) const
	{
		String s = buffer.substr(1, buffer.length() - 2);
		std::vector<String> spl = String::Split(s, ',');
		out.x = spl.size() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.size() > 1 ? std::stof(spl[1]) : 0.0f;
		out.z = spl.size() > 2 ? std::stof(spl[2]) : 0.0f;
		out.w = spl.size() > 3 ? std::stof(spl[3]) : 0.0f;
	}
}