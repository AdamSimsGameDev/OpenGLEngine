#include "cypch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Cy
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		}
		CY_CORE_ASSERT(false, "Unknown ShaderDataType");
		return GL_BOOL;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererId);
		m_IndexBuffer->Bind();
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
		m_IndexBuffer->Unbind();
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		CY_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "VertexBuffer has no layout! ");

		glBindVertexArray(m_RendererId);
		buffer->Bind();

		uint32_t index = 0;
		const auto& l = buffer->GetLayout();
		for (const auto& element : l)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				l.GetStride(),
				(const void*)static_cast<uint64_t>(element.Offset)
			);
			index++;
		}

		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		glBindVertexArray(m_RendererId);
		buffer->Bind();

		m_IndexBuffer = buffer;
	}
}
