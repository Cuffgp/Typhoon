workspace "Typhoon"
	architecture "x64"
	startproject "Typhoon"

	configurations 
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

Library = {}
Library["Vulkan"] = "%{VULKAN_SDK}/Lib/vulkan-1.lib"

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

group "Dependencies"
	include "Typhoon/vendor/glfw"

project "Typhoon"
	location "Typhoon"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "typch.h"
	pchsource "Typhoon/src/typch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/glfw/include",
		"%{IncludeDir.VulkanSDK}"
	}
	
	links
	{
		"GLFW",
		"%{Library.Vulkan}",
	}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"
		
		links
		{

		}

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "On"
		
		links
		{

		}
