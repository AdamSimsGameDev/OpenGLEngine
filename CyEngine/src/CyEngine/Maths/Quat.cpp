#include "cypch.h"
#include "Quat.h"
#include "Vector.h"

namespace Cy
{
	Quat Quat::Identity = Quat(0.0f, 0.0f, 0.0f, 1.0f);

	Quat::Quat(const Vector3& _xyz, float _w)
		: x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) { }

	Quat Quat::Inverse(const Quat& quat)
	{
		const float lengthSq = quat.SqrMagnitude();
		if (lengthSq != 0.0)
		{
			float i = 1.0f / lengthSq;
			return Quat(quat.xyz() * -i, quat.w * i);
		}
		return quat;
	}

	Vector3 Quat::xyz() const
	{
		return Vector3(x, y, z);
	}
}