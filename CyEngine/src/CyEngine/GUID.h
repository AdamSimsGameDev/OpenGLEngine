#pragma once

#include "CoreMinimal.h"

namespace Cy
{
	struct GUID
	{
	public:
		static GUID Make();

		bool operator==(const GUID& other) const { return Value == other.Value; }
		bool operator!=(const GUID& other) const { return !(*this == other); }

		String Value;
	};
}

template<>
struct std::hash<Cy::GUID>
{
	std::size_t operator()(const Cy::GUID& k) const
	{
		return std::hash<std::string>()(*k.Value);
	}
};
