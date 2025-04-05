#pragma once
#include "CyEngine/Core.h"

#define DEFINE_PROPERTY_FIELD(FieldType) bool FieldType##::reg = FieldType##::Init();

namespace Cy
{
	class Object;

	static String FormatDisplayName(const String& Name)
	{
		String OutName = Name;
		if (Name.Length() > 1 && Name[0] == 'b' && std::isupper(Name[1]))
		{
			OutName.Erase(0, 1);
		}
		if (Name.Length() > 2 && Name[0] == 'm' &&  Name[1] == '_')
		{
			OutName.Erase(0, 2);
		}
		return OutName;
	}
	
	struct PropertyFieldBase
	{
	public:
		virtual String GetType() const { return "NULL"; }
		virtual bool IsPointerType() const { return false; }
		virtual bool RenderProperty(void* obj, const Class* cl, const String& displayName, const ClassProperty& info, int arrayIndex = -1) const { return false; }

		static bool RenderPropertyOfType(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop, const String* overrideType = nullptr)
		{
			bool found = false;

			String type = overrideType ? *overrideType : (prop.second.GetClass() ? prop.second.GetClass()->Name : prop.second.Type);
			const Class* TargetClass = prop.second.GetClass();
			while (!found)
			{
				if (PropertyFields.find(type) == PropertyFields.end())
				{
					if (overrideType != nullptr)
					{
						return false;
					}

					if (!TargetClass || !TargetClass->ParentClass)
					{
						return false;
					}

					type = TargetClass->ParentClass->Name;
					TargetClass = TargetClass->ParentClass;
				}
				else
				{
					found = true;
				}
			}

			if (!found) return false;

			// Check to see if we're working with an array.
			int arrayIndex = -1;
			const Array<String>& splitName = String::Split(prop.first, '.');
			if (splitName.Count() > 1)
			{
				arrayIndex = std::stoi(splitName[1]);
			}

			const MetaDataProperty* displayName = prop.second.GetMetaData("DisplayName");
			if (PropertyFields[type]->RenderProperty(obj, cl, displayName ? displayName->GetValue<String>() : FormatDisplayName(prop.first), prop.second, arrayIndex))
			{
				OnPropertyChanged(obj, cl, prop);
			}
			return true;
		}
		static void OnPropertyChanged(void* Obj, const Class* Cl, const std::pair<String, ClassProperty>& Property);

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

		virtual bool RenderProperty(void* obj, const Class* cl, const String& displayName, const ClassProperty& info, int arrayIndex = -1) const override final
		{
			String propertyName = arrayIndex == -1 ? info.Name : String(info.Name) + "." + Cy::String::ToString(arrayIndex);
			if (T2* i = cl->GetPropertyValueFromName<T2>(propertyName, obj))
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

	struct PropertyFieldColour : PropertyField<PropertyFieldColour, Colour>
	{
		virtual String GetType() const override { return "Colour"; }
		virtual bool RenderProperty(Colour* data, const String& displayName, const ClassProperty& info) const override;
	};

	// custom fields, for custom rendering
	struct PropertyFieldEnum : PropertyField<PropertyFieldEnum, uint8_t>
	{
		virtual String GetType() const override { return "Enum"; }
		virtual bool RenderProperty(uint8_t* data, const String& displayName, const ClassProperty& info) const override;
	};

	struct PropertyFieldObject : PropertyField<PropertyFieldObject, Object*>
	{
		virtual String GetType() const override { return "Object"; }
		virtual bool IsPointerType() const override { return true; }
		virtual bool RenderProperty(Object** data, const String& displayName, const ClassProperty& info) const override;
	};
}
