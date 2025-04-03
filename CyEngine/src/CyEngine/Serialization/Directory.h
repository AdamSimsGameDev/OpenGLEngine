#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/String.h"

namespace Cy
{
	struct Directory
	{
	public:
		Directory();
		Directory(const String& InDirectory);
		Directory(const Directory& Other);

		String ToString() const { return String::Combine(Path, "\\"); }
		bool RelativeTo(const Directory& Other, Directory& OutDirectory) const;

		int Length() const { return Path.Count(); }
		
		bool IsFile() const { return m_IsFile; }
		String GetFileExtension() const { return m_FileExtension; }
		String GetName() const { return m_Name; }

		Directory operator+(const Directory& rhs) const;
		Directory operator+(const String& rhs) const;
		Directory& operator+=(const Directory& other);
		Directory& operator+=(const String& other);

		void Append(const Directory& other);
		void Append(const String& other);

		String Pop();
		String PopFirst();

		static Directory PoppedFirst( const Directory& Source );

		const String& First() const { return Path.First(); }
		String& First() { return Path.First(); }

		const String& Last() const { return Path.Last(); }
		String& Last() { return Path.Last(); }

		Directory SubPath() const;

		static Directory AssetsPath;
		static Directory AssetsPathRelative;
		static Directory ProjectPath;

	private:
		Array<String> Path;
		String m_Name;

		bool m_IsFile;
		String m_FileExtension;
	};
}