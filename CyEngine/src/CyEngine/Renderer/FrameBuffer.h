#pragma once

namespace Cy 
{
	struct FrameBufferSpec
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual FrameBufferSpec& GetSpecification_Mutable() = 0;
		virtual const FrameBufferSpec& GetSpecification() const = 0;

		virtual uint32_t GetColorAttachmentRendererId() const = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpec& spec);
	};
}