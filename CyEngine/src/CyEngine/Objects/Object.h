#pragma once

namespace Cy
{
#define GENERATE_OBJECT(type)\
public:\
	virtual std::string ClassName() const { return #type; }\
	static std::string ClassNameStatic() { return #type; }

	class Component;

	class Object
	{
		GENERATE_OBJECT(Object);

	public:
		Object() : m_Parent(nullptr) { }

		virtual void Start();
		virtual void End();

		virtual void SetParent(Object* parent);
		
		template<typename ObjectType>
		ObjectType* GetParent() const { return Cast<ObjectType>(m_Parent); }
		template<typename ObjectType>
		ObjectType* GetParentChecked() const { return CastChecked<ObjectType>(m_Parent); }

	private:
		Object* m_Parent;
	};
}
