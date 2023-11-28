#pragma once

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <functional>

namespace Cy
{
	class StringItr
	{
	public:
		StringItr(char* ptr)
			: m_Ptr(ptr) {}

		StringItr& operator++()
		{
			m_Ptr++;
			return *this;
		}
		StringItr& operator++(int)
		{
			StringItr itr = *this;
			++(*this);
			return itr;
		}

		StringItr& operator--()
		{
			m_Ptr++;
			return *this;
		}
		StringItr& operator--(int)
		{
			StringItr itr = *this;
			--(*this);
			return itr;
		}

		char& operator[](size_t index)
		{
			return m_Ptr[index];
		}

		char* operator->()
		{
			return m_Ptr;
		}
		char& operator*()
		{
			return *m_Ptr;
		}

		bool operator==(const StringItr& other) const { return m_Ptr == other.m_Ptr; }
		bool operator!=(const StringItr& other) const { return !(*this == other); }

	private:
		char* m_Ptr;
	};

	class StringItrConst
	{
	public:
		StringItrConst(const char* ptr)
			: m_Ptr(ptr) {}

		StringItrConst& operator++()
		{
			m_Ptr++;
			return *this;
		}
		StringItrConst& operator++(int)
		{
			StringItrConst itr = *this;
			++(*this);
			return itr;
		}

		StringItrConst& operator--()
		{
			m_Ptr++;
			return *this;
		}
		StringItrConst& operator--(int)
		{
			StringItrConst itr = *this;
			--(*this);
			return itr;
		}

		const char& operator[](size_t index)
		{
			return m_Ptr[index];
		}

		const char* operator->()
		{
			return m_Ptr;
		}
		const char& operator*()
		{
			return *m_Ptr;
		}

		bool operator==(const StringItrConst& other) const { return m_Ptr == other.m_Ptr; }
		bool operator!=(const StringItrConst& other) const { return !(*this == other); }

	private:
		const char* m_Ptr;
	};

	struct String
	{
	public:
		String();
		String(const char* val);
		String(const std::string& val);
		String(const String& other);
		String(String&& other) noexcept;
		~String();

		size_t Length() const { return strlen(str); }

		// Operators
		char& operator[](size_t index) { return str[index]; }
		const char& operator[](size_t index) const { return str[index]; }
		char* operator*() { return str; }
		const char* operator*() const { return str; }
		operator std::string() const { return str; }

		// Add Operations
		String operator+(const String& rhs) const;
		String operator+(const char* rhs) const;
		String operator+(const char& rhs) const;
		String& operator+=(const String& other);
		String& operator+=(const char* other);
		String& operator+=(const char& other);

		// Comparisons
		bool operator==(const char* other) const;
		bool operator!=(const char* other) const { return !(*this == other); }
		bool operator==(const String& other) const;
		bool operator!=(const String& other) const { return !(*this == other); }

		// Copy assignment
		String& operator=(const String& other);
		String& operator=(String&& other) noexcept;

		// Non-const functions
		String& Erase(size_t position, size_t length) noexcept;
		void Empty() { Erase(0, strlen(str)); }

		// Const functions
		String Substring(size_t position, size_t length) const;
		bool Contains(const String& other) const { return strstr(str, other.str) != nullptr; }
		bool IsEmpty() const { return strlen(str) == 0; }

		// Statics
		static Array<String> Split(const String& str, const char& separator);
		static Array<String> SplitUnquoted(const String& str, const char& separator);
		static String ToString(int value);
		static String ToString(float value);
		static String ToString(bool value);

		static inline void TrimLeft(String& s) 
		{
			if (s.Length() == 0 || s[0] != ' ')
				return;
			size_t p = 0;
			while (p + 1 < s.Length())
			{
				if (s[p] != ' ')
					break;
				p++;
			}
			s.Erase(0, p);
		}
		static inline void TrimRight(String& s) 
		{
			size_t p = s.Length();
			while (p >= 0)
			{
				if (s[--p] != ' ')
					break;
			}
			s.Erase(p, s.Length() - p);
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
			auto size = static_cast<int>(size_s);
			std::unique_ptr<char[]> buf(new char[size]);
			std::snprintf(buf.get(), size, *format, args ...);
			return std::string(buf.get(), buf.get() + size - 1).c_str(); // We don't want the '\0' inside
		}

		StringItr begin()
		{
			return StringItr(str);
		}
		StringItr end()
		{
			return StringItr(str + strlen(str));
		}

		StringItrConst begin() const
		{
			return StringItrConst(str);
		}
		StringItrConst end() const
		{
			return StringItrConst(str + strlen(str));
		}
	private:
		char* str = nullptr;

	private:
		void resize(size_t capacity);
		void fill(size_t length, size_t pos, char c);
		void clear(size_t pos);
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