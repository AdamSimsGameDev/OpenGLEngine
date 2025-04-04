#include "cypch.h"
#include "Directory.h"

namespace Cy
{
	Directory Directory::AssetsPath = Directory("C:\\Users\\adams\\Documents\\OpenGLEngine\\Sandbox\\Assets");
	Directory Directory::AssetsPathRelative = Directory("\\Assets");
	Directory Directory::ProjectPath = Directory("C:\\Users\\adams\\Documents\\OpenGLEngine\\Sandbox");

	Directory::Directory()
	{
	}

	Directory::Directory(const String& InDirectory)
	{
		String Parsed = InDirectory;
		Parsed.ReplaceAll("/", "\\");
		Path = String::Split(Parsed, '\\');

		if ( Path.Count() == 0 )
		{
			return;
		}

		Array<String> FileSplit = String::Split(Path.Last(), '.');
		if (FileSplit.Count() == 1)
		{
			m_IsFile = false;
			m_Name = FileSplit.Last();
		}
		else
		{
			m_IsFile = true;
			m_FileExtension = FileSplit.Last();
			FileSplit.Pop();
			m_Name = String::Combine(FileSplit);
		}
	}

	Directory::Directory(const Directory& Other)
	{
		Path = Other.Path;
		m_IsFile = Other.m_IsFile;
		m_Name = Other.m_Name;
		m_FileExtension = Other.m_FileExtension;
	}

	bool Directory::RelativeTo(const Directory& Other, Directory& OutDirectory) const
	{
		if (Other.Length() == 0)
		{
			return false;
		}

		if ( Other.Length() >= Length() )
		{
			return false;
		}

		// Check that this directory contains the other directory
		for ( int i = 0; i < Other.Length(); i++ )
		{
			if ( Path[ i ] != Other.Path[ i ] )
			{
				return false;
			}
		}

		// If we reach here then anything past the other's length is the relative path
		for ( int i = Other.Length(); i < Length(); i++ )
		{
			OutDirectory.Append( Path[ i ] );
		}

		return true;
	}

	Directory Directory::operator+(const Directory& rhs) const
	{
		Directory Cpy = *this;
		Cpy += rhs;
		return Cpy;
	}

	Directory Directory::operator+(const String& rhs) const
	{
		return *this + Directory(rhs);
	}

	Directory& Directory::operator+=(const Directory& other)
	{
		Append(other);
		return *this;
	}

	Directory& Directory::operator+=(const String& other)
	{
		return (*this) += Directory(other);
	}

	void Directory::Append(const Directory& other)
	{
		Path.Add(other.Path);
	}

	void Directory::Append(const String& other)
	{
		Path.Add(Directory(other).Path);
	}

	String Directory::Pop()
	{
		return Path.Pop();
	}	

	String Directory::PopFirst()
	{
		return Path.PopFirst();
	}

	Directory Directory::PoppedFirst( const Directory& Source )
	{
		Directory D( Source );
		D.PopFirst();
		return D;
	}

	Directory Directory::SubPath() const
	{
		Directory Cpy = Directory(*this);
		Cpy.Path.RemoveAt(0);
		return Cpy;
	}
}
