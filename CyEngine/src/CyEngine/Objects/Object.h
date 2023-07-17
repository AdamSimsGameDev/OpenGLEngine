#pragma once

namespace Cy
{
	class Component;

	class Object
	{
	public:
		Object() : m_Parent(nullptr) { }

		virtual void Start();
		virtual void End();

		virtual void SetParent(Object* parent);
		
		template<typename ObjectType>
		ObjectType* GetParent() const { return Cast<ObjectType>(m_Parent); }
		template<typename ObjectType>
		ObjectType* GetParentChecked() const { return CastChecked<ObjectType>(m_Parent); }

		virtual std::string ClassName() const { return "Object"; }

	private:
		Object* m_Parent;
	};
}
