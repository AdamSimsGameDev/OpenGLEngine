#pragma once

#include "CoreMinimal.h"

namespace Cy
{
	struct guid
	{
	public:
		static guid Make();

		bool operator==(const guid& other) const { return Value == other.Value; }
		bool operator!=(const guid& other) const { return !(*this == other); }

		String Value;
	};
}

template<>
struct std::hash<Cy::guid>
{
	std::size_t operator()(const Cy::guid& k) const
	{
		return std::hash<std::string>()(*k.Value);
	}
};
