#pragma once
#include "Directory.h"

namespace Cy
{
	class File
	{
	public:
		static Array<String> GetAllFilesInDirectory(const Directory& Dir, bool bRecurse);
		static Array<String> GetAllFoldersInDirectory(const Directory& Dir, bool bRecurse );

		static bool ReadFromTextFile( const String& path, String& outString );
		static bool WriteToTextFile( const String& path, const String& inString );
	};
}
