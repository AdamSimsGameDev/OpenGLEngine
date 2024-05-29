#include "cypch.h"
#include "Vector.h"
#include "CyEngine/String.h"

namespace Cy
{
	Vector2 Vector2::Up			= Vector2(0.0f, 1.0f);
	Vector2 Vector2::Right		= Vector2(1.0f, 0.0f);
	Vector2 Vector2::Zero		= Vector2(0.0f, 0.0f);
	Vector2 Vector2::One		= Vector2(1.0f, 1.0f);

	Vector3 Vector3::Forward	= Vector3(0.0f, 0.0f, 1.0f);
	Vector3 Vector3::Up			= Vector3(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::Right		= Vector3(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Zero		= Vector3(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::One		= Vector3(1.0f, 1.0f, 1.0f);

	Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4 Vector4::One = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	String Vector2::ToString() const
	{
		return String::Format("(%f, %f)", x, y);
	}

	String Vector3::ToString() const
	{
		return String::Format("(%f, %f, %f)", x, y, z);
	}

	String Vector4::ToString() const
	{
		return String::Format("(%f, %f, %f, %f)", x, y, z, w);
	}

	void SerializableVector2::Serialize(const Vector2 val, String& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableVector2::Deserialize(const String& buffer, Vector2& out) const
	{
		String s = buffer.Substring(1, buffer.Length() - 2);
		Array<String> spl = String::Split(s, ',');
		out.x = spl.Count() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.Count() > 1 ? std::stof(spl[1]) : 0.0f;
	}

	void SerializableVector3::Serialize(const Vector3 val, String& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableVector3::Deserialize(const String& buffer, Vector3& out) const
	{
		String s = buffer.Substring(1, buffer.Length() - 2);
		Array<String> spl = String::Split(s, ',');
		out.x = spl.Count() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.Count() > 1 ? std::stof(spl[1]) : 0.0f;
		out.z = spl.Count() > 2 ? std::stof(spl[2]) : 0.0f;
	}

	void SerializableVector4::Serialize(const Vector4 val, String& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableVector4::Deserialize(const String& buffer, Vector4& out) const
	{
		String s = buffer.Substring(1, buffer.Length() - 2);
		Array<String> spl = String::Split(s, ',');
		out.x = spl.Count() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.Count() > 1 ? std::stof(spl[1]) : 0.0f;
		out.z = spl.Count() > 2 ? std::stof(spl[2]) : 0.0f;
		out.w = spl.Count() > 3 ? std::stof(spl[3]) : 0.0f;
	}
}
