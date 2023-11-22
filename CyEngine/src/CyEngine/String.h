#pragma once
#include "Core.h"
#include <string>
#include <vector>
#include <functional>
#include "Serialization/Serialization.h"
#include "generated/String.gen.h"

namespace Cy
{
	STRUCT()
	struct String
	{
		GENERATED_CLASS(String);

	public:
		String();
		String(const char* chr) { _StringInternal = std::string(chr); }
		String(const String& other) { _StringInternal = other._StringInternal; }
		String(const std::string& other) { _StringInternal = other; }

		// Overrides from std::string
		typedef std::string::iterator StringItr;
		typedef std::string::const_iterator StringItrConst;
		typedef std::string::const_reverse_iterator StringRItrConst;
		StringItr Erase(const StringItrConst _First, const StringItrConst _Last) noexcept { return _StringInternal.erase(_First, _Last); }
		bool Contains(const String& other) const { return _StringInternal.find(*other) != std::string::npos; }

		// Statics
		static std::vector<String> Split(const String& str, const char& separator);
		static inline void TrimLeft(String& s) 
		{
			s.Erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
				return !std::isspace(ch);
				}));
		}
		static inline void TrimRight(String& s) {
			s.Erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
				return !std::isspace(ch);
				}).base(), s.end());
		}
		static inline void Trim(String& s)
		{
			TrimRight(s);
			TrimLeft(s);
		}
		static inline std::string TrimLeft_Copy(String s)
		{
			TrimLeft(s);
			return s;
		}
		static inline std::string TrimRight_Copy(String s)
		{
			TrimRight(s);
			return s;
		}
		static inline std::string Trim_Copy(String s) 
		{
			Trim(s);
			return s;
		}

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

		char* operator *() { return &_StringInternal[0]; }
		const char* operator *() const { return &_StringInternal[0]; }

		std::string GetStringInternal() { return _StringInternal; }
		std::string GetStringInternal() const { return _StringInternal; }

	private:
		_NODISCARD StringItrConst begin() const { return _StringInternal.begin(); }
		_NODISCARD StringItrConst end() const { return _StringInternal.end(); }
		_NODISCARD StringRItrConst rbegin() const { return _StringInternal.rbegin(); }
		_NODISCARD StringRItrConst rend() const { return _StringInternal.rend(); }
	private:
		std::string _StringInternal;
	};

	struct SerializableString : Serializable<SerializableString, String>
	{
		virtual std::string GetType() const { return "String"; }
		virtual void Serialize(const String val, std::string& buffer) const override;
		virtual void Deserialize(const std::string& buffer, String& out) const override;
	};
}

template<>
struct std::hash<Cy::String>
{
	std::size_t operator()(const Cy::String& k) const
	{
		return std::hash<std::string>()(*k);
	}
};