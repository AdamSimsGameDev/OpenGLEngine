#include "cypch.h"
#include "String.h"

namespace Cy
{
	String::String()
	{
		str = new char[1];
		str[0] = '\0';
	}

	String::String(const char* val)
	{
		if (val == nullptr)
		{
			str = new char[1];
			str[0] = '\0';
			return;
		}
		str = new char[strlen(val) + 1];
		strcpy(str, val);
		str[strlen(val)] = '\0';
	}

	String::String(const std::string& val)
	{
		str = new char[strlen(val.c_str()) + 1];
		strcpy(str, val.c_str());
		str[strlen(val.c_str())] = '\0';
	}

	String::String(const String& other)
	{
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
		str[strlen(other.str)] = '\0';
	}

	String::String(String&& other) noexcept
	{
		str = other.str;
		other.str = nullptr;
	}

	String::~String()
	{
		delete[] str;
		str = nullptr;
	}

	String& String::Erase(size_t position, size_t length) noexcept
	{
		// iterate over the string
		for (size_t i = position + length; i < strlen(str); ++i)
		{
			// set the string characters at the position to 
			operator[](i - length) = operator[](i);
		}
		clear(strlen(str) - length);

		return *this;
	}

	String String::Substring(size_t position, size_t length) const
	{
		size_t l = strlen(str);
		size_t end = position + length;
		if (end > l)
			end = l;
		size_t size = end - position;
		if (size <= 0)
			return String();
		char* buffer = new char[size + 1];
		for (size_t i = 0; i < end - position; i++)
			buffer[i] = str[i + position];
		buffer[end] = '\0';
		return String(buffer);
	}

	String String::operator+(const String& rhs) const
	{
		size_t l = strlen(str) + strlen(rhs.str);
		char* buffer = new char[l + 1];
		strcpy(buffer, str);
		strcat(buffer, rhs.str);
		buffer[l] = '\0';
		String t{ buffer };
		delete[] buffer;
		buffer = nullptr;
		return t;
	}

	String String::operator+(const char* rhs) const
	{
		size_t l = strlen(str) + strlen(rhs);
		char* buffer = new char[l + 1];
		strcpy(buffer, str);
		strcat(buffer, rhs);
		buffer[l] = '\0';
		String t{ buffer };
		delete[] buffer;
		buffer = nullptr;
		return t;
	}

	String String::operator+(const char& rhs) const
	{
		size_t l = strlen(str) + 1;
		char* buffer = new char[l + 1];
		strcpy(buffer, str);
		buffer[l - 1] = rhs;
		buffer[l] = '\0';
		String t{ buffer };
		delete[] buffer;
		buffer = nullptr;
		return t;
	}

	String& String::operator+=(const String& other)
	{
		size_t l = strlen(str) + strlen(other.str);
		char* buffer = new char[l + 1];
		strcpy(buffer, str);
		strcat(buffer, other.str);
		buffer[l] = '\0';
		std::swap(str, buffer);
		delete[] buffer;
		buffer = nullptr;
		return *this;
	}

	String& String::operator+=(const char* other)
	{
		size_t l = strlen(str) + strlen(other);
		char* buffer = new char[l + 1];
		strcpy(buffer, str);
		strcat(buffer, other);
		buffer[l] = '\0';
		std::swap(str, buffer);
		delete[] buffer;
		buffer = nullptr;
		return *this;
	}

	String& String::operator+=(const char& other)
	{
		size_t l = strlen(str) + 1;
		char* buffer = new char[l + 1];
		strcpy(buffer, str);
		buffer[l - 1] = other;
		buffer[l] = '\0';
		std::swap(str, buffer);
		delete[] buffer;
		buffer = nullptr;
		return *this;
	}

	bool String::operator==(const char* other) const
	{
		return strcmp(str, other) == 0;
	}
	bool String::operator==(const String& other) const
	{
		return strcmp(str, other.str) == 0;
	}

	String& String::operator=(const String& other)
	{
		if (this == &other)
		{
			return *this;
		}
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
		str[strlen(other.str)] = '\0';
		return *this;
	}

	String& String::operator=(String&& other) noexcept
	{
		str = other.str;
		other.str = nullptr;
		return *this;
	}

	Array<String> String::Split(const String& str, const char& separator)
	{
		Array<String> outstr;
		String cur;
		for (const auto& ch : str)
		{
			if (ch == separator)
			{
				if (cur.Length() > 0)
					outstr.Add(cur);
				cur = "";
			}
			else
			{
				cur = cur + ch;
			}
		}
		if (cur.Length() > 0)
			outstr.Add(cur);
		return outstr;
	}

	Array<String> String::SplitUnquoted(const String& str, const char& separator)
	{
		Array<String> outstr;
		String cur;
		char l = ' ';
		bool is_quoted = false;
		bool is_double_quoted = false;
		for (const auto& ch : str)
		{
			if (ch == separator && (!is_quoted && !is_double_quoted))
			{
				if (cur.Length() > 0)
					outstr.Add(cur);
				cur = "";
				continue;
			}
			else if (ch == '\'' && l != '\\')
			{
				is_quoted = !is_quoted;
			}
			else if (ch == '"' && l != '\\')
			{
				is_double_quoted = !is_double_quoted;
			}
			cur += ch;
			l = ch;
		}
		if (cur.Length() > 0)
			outstr.Add(cur);
		return outstr;
	}

	String String::ToString(unsigned int value)
	{
		return String(std::to_string(value).c_str());
	}

	String String::ToString(int value)
	{
		return String(std::to_string(value).c_str());
	}

	String String::ToString(float value)
	{
		return String(std::to_string(value).c_str());
	}

	String String::ToString(bool value)
	{
		return value ? "true" : "false";
	}

	void String::resize(size_t capacity)
	{
		char* buffer = new char[capacity + 1];
		strcpy(buffer, str);
		buffer[capacity] = '\0';
		std::swap(str, buffer);
		delete[] buffer;
		buffer = nullptr;
	}

	void String::fill(size_t length, size_t pos, char c)
	{
		size_t s = pos;
		while (s != length)
			str[s++] = c;
		str[s] = '\0';
	}
	
	void String::clear(size_t pos)
	{
		fill(strlen(str), pos, '\0');
	}
}