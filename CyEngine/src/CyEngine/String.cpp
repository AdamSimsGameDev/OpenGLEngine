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

	DEFINE_SERIALIZABLE_OBJECT(SerializableString)
	void SerializableString::Serialize(const void* obj, SerializationBufferWrite& buffer) const
	{
		const String* data = reinterpret_cast<const String*>(obj);
		buffer.Write("\"" + data->GetStringInternal() + "\"");
	}
	void SerializableString::Deserialize(void* obj, const SerializationBufferRead& buffer) const
	{

	}
}