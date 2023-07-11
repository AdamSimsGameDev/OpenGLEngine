#include "cypch.h"
#include "FrameBuffer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Cy
{	
	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec& spec)
	{
		return std::make_shared<OpenGLFrameBuffer>(spec);
	}
}
