#include "cypch.h"
#include "Layer.h"

namespace Cy
{
	Layer::Layer(const String& name)
	{
		m_DebugName = name;

		CY_CORE_TRACE("Created Layer {0}", *m_DebugName);
	}

	Layer::~Layer()
	{
	}
}