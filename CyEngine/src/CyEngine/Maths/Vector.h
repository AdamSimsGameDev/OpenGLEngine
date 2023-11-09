#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <sstream>
#include "CyEngine/Serialization/Serialization.h"

namespace Cy
{
	struct Quat;
	struct Vector2;
	struct Vector3;
	struct Vector4;

	struct Vector2 : public glm::vec2
	{
	public:
		Vector2(const glm::vec2& vec) : glm::vec2(vec) { }
		Vector2(float _x, float _y) : glm::vec2(_x, _y) { }

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "(" << x << ", " << y << ")";
			return ss.str();
		}

		static inline Vector2 Cross(const Vector2& a, const Vector2& b) { return { a.x * b.x, a.y * b.y }; }

		inline Vector2 Normalized(const Vector2& inVector) const
		{
			const float l = Magnitude();
			return { x / l, y / l };
		}

		inline Vector2& Normalize()
		{
			const float l = Magnitude();
			x /= l;
			y /= l;
			return *this;
		}

		inline float Magnitude() const
		{
			return sqrtf((x * x) + (y * y));
		}

		inline float SqrMagnitude() const
		{
			return (x * x) + (y * y);
		}

		static Vector2 Forward;
		static Vector2 Up;
		static Vector2 Right;
		static Vector2 Zero;
		static Vector2 One;
	};

	struct Vector3 : public glm::vec3
	{
	public:
		Vector3() : glm::vec3(0.f, 0.f, 0.f) { }
		Vector3(const glm::vec3& vec) : glm::vec3(vec) { }
		Vector3(float _x, float _y, float _z) : glm::vec3(_x, _y, _z) { }

		inline std::string ToString() const 
		{ 
			std::ostringstream ss; 
			ss << "(" << x << ", " << y << ", " << z << ")"; 
			return ss.str(); 
		}
		static inline Vector3 Cross(const Vector3& a, const Vector3& b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }

		inline Vector3 Normalized(const Vector3& inVector) const
		{
			const float l = Magnitude();
			return { x / l, y / l, z / l };
		}	
		
		inline Vector3& Normalize()
		{
			const float l = Magnitude();
			x /= l;
			y /= l;
			z /= l;
			return *this;
		}

		inline float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z));
		}

		inline float SqrMagnitude() const
		{
			return (x * x) + (y * y) + (z * z);
		}

		operator glm::vec3() const { return glm::vec3(x, y, z); }

		static Vector3 Forward;
		static Vector3 Up;
		static Vector3 Right;
		static Vector3 Zero;
		static Vector3 One;
	};

	struct Vector4 : public glm::vec4
	{
	public:
		Vector4(const glm::vec4& vec) : glm::vec4(vec) { }
		Vector4(float _x, float _y, float _z, float _w) : glm::vec4(_x, _y, _z, _w) { }

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
			return ss.str();
		}

		inline float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
		}

		inline float SqrMagnitude() const
		{
			return (x * x) + (y * y) + (z * z) + (w * w);
		}
	};

	struct SerializableVector2 : Serializable<SerializableVector2>
	{
		virtual std::string GetType() const { return "Vector2"; }
		virtual void Serialize(const void* obj, SerializationBufferWrite& buffer) const override 
		{
			const Vector2* data = reinterpret_cast<const Vector2*>(obj);
			buffer.Write(data->ToString());
		}
		virtual void Deserialize(void* obj, const SerializationBufferRead& buffer) const override
		{

		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableVector2)

	struct SerializableVector3 : Serializable<SerializableVector3>
	{
		virtual std::string GetType() const { return "Vector3"; }
		virtual void Serialize(const void* obj, SerializationBufferWrite& buffer) const override
		{
			const Vector3* data = reinterpret_cast<const Vector3*>(obj);
			buffer.Write(data->ToString());
		}
		virtual void Deserialize(void* obj, const SerializationBufferRead& buffer) const override
		{

		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableVector3)

	struct SerializableVector4 : Serializable<SerializableVector4>
	{
		virtual std::string GetType() const { return "Vector4"; }
		virtual void Serialize(const void* obj, SerializationBufferWrite& buffer) const override
		{
			const Vector4* data = reinterpret_cast<const Vector4*>(obj);
			buffer.Write(data->ToString());
		}
		virtual void Deserialize(void* obj, const SerializationBufferRead& buffer) const override
		{

		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableVector4)
}