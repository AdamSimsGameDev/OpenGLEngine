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

project "CyEngine"
	location "CyEngine"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
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
		symbols "On"

	filter "configurations:Development"
		defines "CY_DEVELOPMENT"
		optimize "On"

	filter "configurations:Release"
		defines "CY_RELEASE"
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
		symbols "On"

	filter "configurations:Development"
		defines "CY_DEVELOPMENT"
		optimize "On"

	filter "configurations:Release"
		defines "CY_RELEASE"
		optimize "On"

