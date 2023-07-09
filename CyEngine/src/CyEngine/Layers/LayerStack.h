#pragma once

#include "CyEngine/Core.h"
#include "Layer.h"

namespace Cy
{
	using LayerStackCont = std::vector<Layer*>;
	using LayerStackItr = LayerStackCont::iterator;

	class CY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		LayerStackItr begin() { return m_Layers.begin(); }
		LayerStackItr end() { return m_Layers.end(); }

	private:
		LayerStackCont m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}