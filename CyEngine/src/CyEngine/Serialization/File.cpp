#include "cypch.h"
#include "File.h"
#include <filesystem>
#include <sstream>

namespace Cy
{
	Array<String> File::GetAllFilesInDirectory(const Directory& Dir, bool bRecurse )
	{
		Array<String> OutPaths;
		if ( bRecurse )
		{
			for ( const auto& entry : std::filesystem::recursive_directory_iterator( *Dir.ToString() ) )
			{
				const String& path = entry.path().string();
				if ( !entry.is_directory() )
				{
					OutPaths.Add( path );
				}
			}
		}
		else
		{
			for ( const auto& entry : std::filesystem::directory_iterator( *Dir.ToString() ) )
			{
				const String& path = entry.path().string();
				if ( !entry.is_directory() )
				{
					OutPaths.Add( path );
				}
			}
		}
		return OutPaths;
	}

	Array<String> File::GetAllFoldersInDirectory( const Directory& Dir, bool bRecurse )
	{
		const String& DirectoryStr = Dir.ToString();
		Array<String> OutPaths;
		if ( bRecurse )
		{
			for ( const auto& entry : std::filesystem::recursive_directory_iterator( *DirectoryStr ) )
			{
				const String& path = entry.path().string();
				if ( entry.is_directory() )
				{
					OutPaths.Add( path );
				}
			}
		}
		else
		{
			for ( const auto& entry : std::filesystem::directory_iterator( *DirectoryStr ) )
			{
				const String& path = entry.path().string();
				if ( entry.is_directory() )
				{
					OutPaths.Add( path );
				}
			}
		}
		return OutPaths;
	}

	bool File::ReadFromTextFile( const String& path, String& outString )
	{
		std::ifstream infile;
		infile.open( path );

		if ( infile.fail() )
		{
			return false;
		}

		std::stringstream buffer;
		buffer << infile.rdbuf();

		outString = buffer.str();

		return true;
	}

	bool File::WriteToTextFile( const String& path, const String& inString )
	{
		std::ofstream outfile;
		outfile.open( path );

		if ( outfile.fail() )
		{
			CY_CORE_LOG( "Failed to open at path {0}", *path );
			return false;
		}

		outfile << *inString;

		outfile.close();

		return true;
	}
}
