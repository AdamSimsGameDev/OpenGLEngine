#include "cypch.h"
#include "String.h"

namespace Cy
{
	String::String()
	{
		_StringInternal = "";
	}

	std::vector<String> String::Split(const String& str, const char& separator)
	{
		std::vector<String> outstr;
		String cur;
		for (const auto& ch : str)
		{
			if (ch == separator)
			{
				if (cur.Length() > 0)
					outstr.push_back(cur);
				cur = "";
			}
			else
			{
				cur += ch;
			}
		}
		if (cur.Length() > 0)
			outstr.push_back(cur);
		return outstr;
	}

	//DEFINE_SERIALIZABLE_OBJECT(SerializableString)
	//void SerializableString::Serialize(const String val, std::string& buffer) const
	//{
	//	buffer += "\"" + val.GetStringInternal() + "\"";
	//}
	//void SerializableString::Deserialize(const std::string& buffer, String& out) const
	//{
	//	out = buffer.substr(1, buffer.length() - 2);
	//}
}