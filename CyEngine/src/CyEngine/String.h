#pragma once
#include "Core.h"
#include <string>
#include <vector>
#include "generated/String.gen.h"

namespace Cy
{
	STRUCT()
	struct String
	{
		GENERATED_CLASS(String);

	public:
		String() { _StringInternal = ""; }
		String(const char* chr) { _StringInternal = std::string(chr); }
		String(const String& other) { _StringInternal = other._StringInternal; }
		String(const std::string& other) { _StringInternal = other; }

		// Statics
		static std::vector<String> Split(const String& str, const char& separator);

		// Members
		void Empty() { _StringInternal = ""; }
		bool IsEmpty() const { return _StringInternal.empty(); }
		uint32_t Length() const { return (uint32_t)_StringInternal.length(); }

		bool operator==(const String& other) const { return other._StringInternal == _StringInternal; }
		void operator+=(const String& other) { _StringInternal += other._StringInternal; }
		void operator+=(const char& chr) { _StringInternal += chr; }
		String operator+(const String& other) const { return _StringInternal + other._StringInternal; }
		String operator+(const char& chr) { return _StringInternal += chr; }

		String operator=(const char* chr) { _StringInternal = std::string(chr); return *this; }

		operator std::string() const { return _StringInternal; }
		operator const char*() const { return _StringInternal.c_str(); }

		const char* operator *() const { return _StringInternal.c_str(); }

	private:
		_NODISCARD std::string::const_iterator begin() const { return _StringInternal.begin(); }
		_NODISCARD std::string::const_iterator end() const { return _StringInternal.end(); }

	private:
		std::string _StringInternal;
	};
}