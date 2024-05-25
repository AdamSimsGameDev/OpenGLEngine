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
IncludeDirs["imgui"] = "CyEngine/vendor/imgui";
IncludeDirs["glm"] = "CyEngine/vendor/glm";

include "CyEngine/vendor/GLFW"
include "CyEngine/vendor/glad"
include "CyEngine/vendor/imgui"

project "CyEngine"
	location "CyEngine"
	kind "StaticLib"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("int/" .. outputdir .. "/%{prj.name}")

	pchheader "cypch.h"
	pchsource "CyEngine/src/cypch.cpp"

	prebuildcommands { "msbuild %{prj.location}/tools/CyEngineBuildTool/CyEngineBuildTool.sln /p:Configuration=Debug", "%{prj.location}/tools/CyEngineBuildTool/x64/Debug/CyEngineBuildTool.exe" }

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"CyEngine/src",
		"CyEngine/src/generated",
		"CyEngine/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.glad}",
		"%{IncludeDirs.imgui}",
		"%{IncludeDirs.glm}"
	}

	links
	{
		"GLFW",
		"glad",
		"opengl32.lib",
		"dwmapi.lib",
		"imgui"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
	}

	filter "system:windows" 
		systemversion "latest"

		defines
		{
			"CY_PLATFORM_WINDOWS",
			"CY_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
		}

	filter "configurations:Debug"
		defines "CY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Development"
		defines "CY_DEVELOPMENT"
		runtime "Release"
		optimize "On"

	filter "configurations:Release"
		defines "CY_RELEASE"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"CyEngine/src",
		"CyEngine/vendor",
		"%{IncludeDirs.glm}"
	}

	links
	{
		"CyEngine"
	}

	filter "system:windows" 
		systemversion "latest"

		defines
		{
			"CY_PLATFORM_WINDOWS",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
		}

	filter "configurations:Debug"
		defines "CY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Development"
		defines "CY_DEVELOPMENT"
		runtime "Release"
		optimize "On"

	filter "configurations:Release"
		defines "CY_RELEASE"
		runtime "Release"
		optimize "On"

