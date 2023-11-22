#include "cypch.h"
#include "Vector.h"
#include "CyEngine/String.h"

namespace Cy
{
	Vector3 Vector3::Forward	= Vector3(0.0f, 0.0f, 1.0f);
	Vector3 Vector3::Up			= Vector3(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::Right		= Vector3(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Zero		= Vector3(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::One		= Vector3(1.0f, 1.0f, 1.0f);

	void SerializableVector2::Serialize(const Vector2 val, std::string& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableVector2::Deserialize(const std::string& buffer, Vector2& out) const
	{
		String s = buffer.substr(1, buffer.length() - 2);
		std::vector<String> spl = String::Split(s, ',');
		out.x = spl.size() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.size() > 1 ? std::stof(spl[1]) : 0.0f;
	}

	void SerializableVector3::Serialize(const Vector3 val, std::string& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableVector3::Deserialize(const std::string& buffer, Vector3& out) const
	{
		String s = buffer.substr(1, buffer.length() - 2);
		std::vector<String> spl = String::Split(s, ',');
		out.x = spl.size() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.size() > 1 ? std::stof(spl[1]) : 0.0f;
		out.z = spl.size() > 2 ? std::stof(spl[2]) : 0.0f;
	}

	void SerializableVector4::Serialize(const Vector4 val, std::string& buffer) const
	{
		buffer += val.ToString();
	}
	void SerializableVector4::Deserialize(const std::string& buffer, Vector4& out) const
	{
		String s = buffer.substr(1, buffer.length() - 2);
		std::vector<String> spl = String::Split(s, ',');
		out.x = spl.size() > 0 ? std::stof(spl[0]) : 0.0f;
		out.y = spl.size() > 1 ? std::stof(spl[1]) : 0.0f;
		out.z = spl.size() > 2 ? std::stof(spl[2]) : 0.0f;
		out.w = spl.size() > 3 ? std::stof(spl[3]) : 0.0f;
	}
}
