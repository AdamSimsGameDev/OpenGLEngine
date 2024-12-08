#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/Layers/EditorTab.h"

namespace Cy
{
	class ObjectSelectorTab : public EditorTab
	{
	public:
		ObjectSelectorTab(const Class* assetType, Object** targetData);
		virtual void OnRender() override;

	protected:
		virtual void RenderAsset(class Object* asset);

	private:
		const Class* TargetAssetType;
		Object** TargetDataPtr;

		char m_FilterBuffer[64];
		String m_Filter;
	};
}
