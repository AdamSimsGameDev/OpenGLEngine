#pragma once

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <functional>

namespace Cy
{
	struct String
	{
	public:
		String();
		String(const char* chr) 
		{ 
			_StringInternal = std::string(chr); 
			printf("from char");
		}
		String(const String& other) 
		{ 
			*this = other;
			printf("from str");
		}
		String(const std::string& other) 
		{ 
			_StringInternal = std::string(other); 
			printf("from std");
		}

		// Overrides from std::string
		typedef std::string::iterator StringItr;
		typedef std::string::const_iterator StringItrConst;
		typedef std::string::const_reverse_iterator StringRItrConst;
		StringItr Erase(const StringItrConst _First, const StringItrConst _Last) noexcept { return _StringInternal.erase(_First, _Last); }
		bool Contains(const String& other) const { return _StringInternal.find(*other) != std::string::npos; }

		// Statics
		static Array<String> Split(const String& str, const char& separator);
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
		static inline String TrimLeft_Copy(String s)
		{
			TrimLeft(s);
			return s;
		}
		static inline String TrimRight_Copy(String s)
		{
			TrimRight(s);
			return s;
		}
		static inline String Trim_Copy(String s)
		{
			Trim(s);
			return s;
		}

		template<class... Args>
		static String Format(const String& format, Args&&... args)
		{
			int size_s = std::snprintf(nullptr, 0, *format, args ...) + 1; // Extra space for '\0'
			if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
			auto size = static_cast<size_t>(size_s);
			std::unique_ptr<char[]> buf(new char[size]);
			std::snprintf(buf.get(), size, *format, args ...);
			return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
		}

		inline String Substring(int position, int length) const
		{
			return _StringInternal.substr(position, length);
		}

		// Members
		void Empty() { _StringInternal = ""; }
		bool IsEmpty() const { return _StringInternal.empty(); }
		uint32_t Length() const { return (uint32_t)_StringInternal.length(); }

		bool operator==(const String& other) const { return other._StringInternal == _StringInternal; }
		bool operator!=(const String& other) const { return !(other == _StringInternal); }

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

		_NODISCARD StringItrConst begin() const { return _StringInternal.begin(); }
		_NODISCARD StringItrConst end() const { return _StringInternal.end(); }
		_NODISCARD StringRItrConst rbegin() const { return _StringInternal.rbegin(); }
		_NODISCARD StringRItrConst rend() const { return _StringInternal.rend(); }
	private:
		std::string _StringInternal;
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