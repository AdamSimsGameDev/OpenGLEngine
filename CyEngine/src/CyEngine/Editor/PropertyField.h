#pragma once
#include "CyEngine/Core.h"

#define DEFINE_PROPERTY_FIELD(FieldType) bool FieldType##::reg = FieldType##::Init();

namespace Cy
{
	class Object;

	struct PropertyFieldBase
	{
	public:
		virtual String GetType() const { return "NULL"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const { return false; }

		static bool RenderPropertyOfType(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop)
		{
			if (PropertyFields.find(prop.second.Type) == PropertyFields.end())
			{
				return false;
			}
			const PropertyFieldBase* field = PropertyFields[prop.second.Type];
			field->RenderProperty(obj, path, prop);
			return true;
		}

		static std::unordered_map<std::string, PropertyFieldBase*> PropertyFields;
	};

	template<typename T>
	struct PropertyField : PropertyFieldBase
	{	
	public:
		PropertyField()
		{
			reg;
		}
		static bool reg;
		static bool Init()
		{
			T* t = new T();
			PropertyFieldBase::PropertyFields.emplace(t->GetType(), t);
			return true;
		}
	};

	template<class T>
	bool PropertyField<T>::reg = PropertyField<T>::Init();

	struct PropertyFieldInt : PropertyField<PropertyFieldInt>
	{
		virtual String GetType() const override { return "int"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};

	struct PropertyFieldFloat : PropertyField<PropertyFieldFloat>
	{
		virtual String GetType() const override { return "float"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};

	struct PropertyFieldBool : PropertyField<PropertyFieldBool>
	{
		virtual String GetType() const override { return "bool"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};	
	
	struct PropertyFieldString : PropertyField<PropertyFieldString>
	{
		virtual String GetType() const override { return "String"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};

	struct PropertyFieldVector2 : PropertyField<PropertyFieldVector2>
	{
		virtual String GetType() const override { return "Vector2"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};

	struct PropertyFieldVector3 : PropertyField<PropertyFieldVector3>
	{
		virtual String GetType() const override { return "Vector3"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};

	struct PropertyFieldVector4 : PropertyField<PropertyFieldVector4>
	{
		virtual String GetType() const override { return "Vector4"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};

	struct PropertyFieldQuat : PropertyField<PropertyFieldQuat>
	{
		virtual String GetType() const override { return "Quat"; }
		virtual bool RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const override;
	};
}