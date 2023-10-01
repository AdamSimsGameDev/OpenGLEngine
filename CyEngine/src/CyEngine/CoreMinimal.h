#pragma once

#define CLASS()
#define PROPERTY()
#define GENERATED_CLASS(type) public:\
	static Class* GetStaticClass() { return type##Class::Get(); }\
	virtual Class* GetClass() const { return type##::GetStaticClass(); }