#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/AssetManager/AssetInfo.h"
#include "generated/TextAsset.gen.h"

namespace Cy
{
	CLASS()
	class TextAsset : public AssetInfo
	{
		GENERATED_CLASS(TextAsset)

	public:
		const String& GetContent() const { return m_Content; }

	protected:
		virtual bool OnSave() override;

		virtual void OnLoad() override;
		virtual void OnUnload() override;

		virtual Array<String> GetSupportedFileTypes() const override;
	
	protected:
		PROPERTY(MultiLine)
		String m_Content;
	};
}
