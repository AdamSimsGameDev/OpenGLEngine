workspace "CyEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Development",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "CyEngine/vendor/GLFW/include";
IncludeDirs["glad"] = "CyEngine/vendor/glad/include";

include "CyEngine/vendor/GLFW"
include "CyEngine/vendor/glad"

project "CyEngine"
	location "CyEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "cypch.h"
	pchsource "CyEngine/src/cypch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CyEngine/src",
		"CyEngine/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.glad}"
	}

	links
	{
		"GLFW",
		"glad",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows" 
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CY_PLATFORM_WINDOWS",
			"CY_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CY_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Development"
		defines "CY_DEVELOPMENT"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Release"
		defines "CY_RELEASE"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"CyEngine/vendor/spdlog/include",
		"CyEngine/src"
	}

	links
	{
		"CyEngine"
	}

	filter "system:windows" 
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CY_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Development"
		defines "CY_DEVELOPMENT"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Release"
		defines "CY_RELEASE"
		buildoptions "/MD"
		optimize "On"

