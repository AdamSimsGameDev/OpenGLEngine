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
}