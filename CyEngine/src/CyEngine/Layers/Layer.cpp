#include "cypch.h"
#include "Layer.h"

namespace Cy
{
	Layer::Layer(const std::string& name)
	{
		m_DebugName = name;
	}

	Layer::~Layer()
	{
	}
}