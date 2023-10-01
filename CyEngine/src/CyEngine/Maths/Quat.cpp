#include "cypch.h"
#include "Quat.h"
#include "Vector.h"
#include "Maths.h"

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
}