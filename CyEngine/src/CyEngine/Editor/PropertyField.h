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
		virtual bool RenderProperty(void* obj, const Class* cl, const String& displayName, const ClassProperty& info) const { return false; }

		static bool RenderPropertyOfType(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop, const String* overrideType = nullptr)
		{
			String type = overrideType ? *overrideType : prop.second.Type;
			if (PropertyFields.find(type) == PropertyFields.end())
			{
				return false;
			}
			const ClassPropertyMetaData* displayName = prop.second.GetMetaData("DisplayName");
			return PropertyFields[type]->RenderProperty(obj, cl, displayName ? displayName->GetValue<String>() : prop.first, prop.second);
		}

		static std::unordered_map<String, PropertyFieldBase*> PropertyFields;
	};

	template<typename T1, typename T2>
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
			T1* t = new T1();
			PropertyFieldBase::PropertyFields.emplace(t->GetType(), t);
			return true;
		}

		virtual bool RenderProperty(void* obj, const Class* cl, const String& displayName, const ClassProperty& info) const override final
		{
			if (T2* i = cl->GetPropertyValueFromName<T2>(info.Name, obj))
			{
				return RenderProperty(i, displayName, info);
			}
			return false;
		}
		virtual bool RenderProperty(T2* data, const String& displayName, const ClassProperty& info) const { return false; }
	};

	struct PropertyFieldInt : PropertyField<PropertyFieldInt, int>
	{
		virtual String GetType() const override { return "int"; }
		virtual bool RenderProperty(int* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldFloat : PropertyField<PropertyFieldFloat, float>
	{
		virtual String GetType() const override { return "float"; }
		virtual bool RenderProperty(float* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldBool : PropertyField<PropertyFieldBool, bool>
	{
		virtual String GetType() const override { return "bool"; }
		virtual bool RenderProperty(bool* data, const String& displayName, const ClassProperty& info) const override;
	};
	
	struct PropertyFieldString : PropertyField<PropertyFieldString, String>
	{
		virtual String GetType() const override { return "String"; }
		virtual bool RenderProperty(String* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldVector2 : PropertyField<PropertyFieldVector2, Vector2>
	{
		virtual String GetType() const override { return "Vector2"; }
		virtual bool RenderProperty(Vector2* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldVector3 : PropertyField<PropertyFieldVector3, Vector3>
	{
		virtual String GetType() const override { return "Vector3"; }
		virtual bool RenderProperty(Vector3* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldVector4 : PropertyField<PropertyFieldVector4, Vector4>
	{
		virtual String GetType() const override { return "Vector4"; }
		virtual bool RenderProperty(Vector4* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldQuat : PropertyField<PropertyFieldQuat, Quat>
	{
		virtual String GetType() const override { return "Quat"; }
		virtual bool RenderProperty(Quat* data, const String& displayName, const ClassProperty& info) const override;
	};

	// custom fields, for custom rendering
	struct PropertyFieldEnum : PropertyField<PropertyFieldEnum, uint8_t>
	{
		virtual String GetType() const override { return "Enum"; }
		virtual bool RenderProperty(uint8_t* data, const String& displayName, const ClassProperty& info) const override;
	};
}
