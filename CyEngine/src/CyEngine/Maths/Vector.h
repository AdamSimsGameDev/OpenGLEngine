#pragma once

#include <glm/glm.hpp>
#include <string>
#include <sstream>

namespace Cy
{
	struct Vector2
	{
	public:
		Vector2(const glm::vec2& vec) : x(vec.x), y(vec.y) { }
		Vector2(float _x, float _y) : x(_x), y(_y) { }

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "(" << x << ", " << y << ")";
			return ss.str();
		}

		inline bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }

		inline Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
		inline Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

		inline void operator+=(const Vector2& other) { x += other.x; y += other.y; }
		inline void operator-=(const Vector2& other) { x -= other.x; y -= other.y; }

		inline Vector2 operator*(float multiplier) const { return Vector2(x * multiplier, y * multiplier); }
		inline void operator*=(float multiplier) { x *= multiplier; y *= multiplier; }

		inline Vector2 operator/(float divisor) const { return Vector2(x / divisor, y / divisor); }
		inline void operator/=(float divisor) { x /= divisor; y /= divisor; }

		const float& operator[](int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			}
		}
		float& operator[](int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			}
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

		operator glm::vec2() const { return glm::vec2(x, y); }

		static Vector2 Forward;
		static Vector2 Up;
		static Vector2 Right;
		static Vector2 Zero;
		static Vector2 One;

		float x;
		float y;
	};

	struct Vector3
	{
	public:
		Vector3(const glm::vec3& vec) : x(vec.x), y(vec.y), z(vec.z) { }
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

		inline std::string ToString() const 
		{ 
			std::ostringstream ss; 
			ss << "(" << x << ", " << y << ", " << z << ")"; 
			return ss.str(); 
		}

		inline bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }

		inline Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
		inline Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }

		inline void operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; }
		inline void operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; }

		inline Vector3 operator*(float multiplier) const { return Vector3(x * multiplier, y * multiplier, z * multiplier); }
		inline void operator*=(float multiplier) { x *= multiplier; y *= multiplier; z *= multiplier; }

		inline Vector3 operator/(float divisor) const { return Vector3(x / divisor, y / divisor, z / divisor); }
		inline void operator/=(float divisor) { x /= divisor; y /= divisor; z /= divisor; }

		const float& operator[](int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
		}
		float& operator[](int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			}
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

	private:
		float x;
		float y;
		float z;
	};

	struct Vector4
	{
	public:
		Vector4(const glm::vec4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) { }
		Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }

		inline std::string ToString() const
		{
			std::ostringstream ss;
			ss << "(" << x << ", " << y << ", " << z << ", " << w << ")";
			return ss.str();
		}

		inline bool operator==(const Vector4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }

		inline Vector4 operator+(const Vector4& other) const { return Vector4(x + other.x, y + other.y, z + other.z, w + other.w); }
		inline Vector4 operator-(const Vector4& other) const { return Vector4(x - other.x, y - other.y, z - other.z, w - other.w); }

		inline void operator+=(const Vector4& other) { x += other.x; y += other.y; z += other.z; w += other.w; }
		inline void operator-=(const Vector4& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; }

		inline Vector4 operator*(float multiplier) const { return Vector4(x * multiplier, y * multiplier, z * multiplier, w * multiplier); }
		inline void operator*=(float multiplier) { x *= multiplier; y *= multiplier; z *= multiplier; w *= multiplier; }

		inline Vector4 operator/(float divisor) const { return Vector4(x / divisor, y / divisor, z / divisor, w / divisor); }
		inline void operator/=(float divisor) { x /= divisor; y /= divisor; z /= divisor; w /= divisor; }

		const float& operator[](int index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}
		float& operator[](int index)
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			case 3:
				return w;
			}
		}

		operator glm::vec4() const { return glm::vec4(x, y, z, w); }

		float x;
		float y;
		float z;
		float w;
	};
}