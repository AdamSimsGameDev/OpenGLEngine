#include "cypch.h"
#include "Quat.h"
#include "Vector.h"

namespace Cy
{
	Quat Quat::Identity = Quat(0.0f, 0.0f, 0.0f, 1.0f);

	Quat::Quat(const Vector3& _xyz, float _w)
		: glm::quat(_w, _xyz.x, _xyz.y, _xyz.z) { }

	Quat Quat::Inverse(const Quat& quat)
	{
		return glm::inverse(quat);
	}

	Vector3 Quat::xyz() const
	{
		return Vector3(x, y, z);
	}
}