#include "cypch.h"
#include "String.h"

namespace Cy
{
	String::String()
	{
		_StringInternal = "";
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
				cur += ch;
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
}