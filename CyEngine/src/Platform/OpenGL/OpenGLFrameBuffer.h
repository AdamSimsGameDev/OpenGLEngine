#pragma once

#include "CyEngine/Renderer/FrameBuffer.h"

namespace Cy
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpec& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual FrameBufferSpec& GetSpecification_Mutable() override { return m_Specification; }
		virtual const FrameBufferSpec& GetSpecification() const override { return m_Specification; }

		virtual uint32_t GetColorAttachmentRendererId() const override { return m_ColorAttachment; }

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t m_RendererId = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		FrameBufferSpec m_Specification;
	};
}

