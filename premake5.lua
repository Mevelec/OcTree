workspace "OcTree"
   configurations { "Debug", "Release" }
   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
   
project "OcTree"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"OcTree/**.h",
		"OcTree/**.cpp",
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
		defines { "NDEBUG" }
        runtime "Release"
        optimize "on"