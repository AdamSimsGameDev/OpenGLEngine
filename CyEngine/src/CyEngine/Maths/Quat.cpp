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

	Vector3 Quat::ToEuler(const Quat& quat)
	{
        float sqw = quat.w * quat.w;
        float sqx = quat.x * quat.x;
        float sqy = quat.y * quat.y;
        float sqz = quat.z * quat.z;
        float unit = sqx + sqy + sqz + sqw;
        float test = quat.x * quat.w - quat.y * quat.z;
        Vector3 v;
        if (test > 0.4995f * unit)
        {
            v.y = 2.f * atan2f(quat.y, quat.x);
            v.x = PI() / 2;
            v.z = 0;
            return NormaliseAngles(v * RAD_TO_DEG);
        }
        if (test < -0.4995f * unit)
        {
            v.y = -2.f * atan2f(quat.y, quat.x);
            v.x = -PI() / 2;
            v.z = 0;
            return NormaliseAngles(v * RAD_TO_DEG);
        }
        Quat q = Quat(quat.w, quat.z, quat.x, quat.y);
        v.y = (float)atan2f(2.f * q.x * q.w + 2.f * q.y * q.z, 1 - 2.f * (q.z * q.z + q.w * q.w));
        v.x = (float)asinf(2.f * (q.x * q.z - q.w * q.y));
        v.z = (float)atan2f(2.f * q.x * q.y + 2.f * q.z * q.w, 1 - 2.f * (q.y * q.y + q.z * q.z));
        return NormaliseAngles(v * RAD_TO_DEG);
    }

	Quat Quat::FromEuler(const Vector3& euler)
	{
        float yaw = euler.x;
        float pitch = euler.y;
        float roll = euler.z;
        float rollOver2 = roll * 0.5f;
        float sinRollOver2 = sinf(rollOver2);
        float cosRollOver2 = cosf(rollOver2);
        float pitchOver2 = pitch * 0.5f;
        float sinPitchOver2 = sinf(pitchOver2);
        float cosPitchOver2 = cosf(pitchOver2);
        float yawOver2 = yaw * 0.5f;
        float sinYawOver2 = sinf(yawOver2);
        float cosYawOver2 = cosf(yawOver2);
        Quat result = Quat::Identity;
        result.x = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
        result.y = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
        result.z = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
        result.w = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
        return result;
    }

	Vector3 Quat::xyz() const
	{
		return Vector3(x, y, z);
	}
}