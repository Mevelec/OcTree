workspace "Chunk"
	-- We set the location of the files Premake will generate
	location "Generated"

	-- We indicate that all the projects are C++ only
	language "C++"

	-- We will compile for x86_64. You can change this to x86 for 32 bit builds.
	architecture "x86_64"

	-- Configurations are often used to store some compiler / linker settings together.
	-- The Debug configuration will be used by us while debugging.
	-- The optimized Release configuration will be used when shipping the app.
	configurations { "Debug", "Release" }

	-- We use filters to set options, a new feature of Premake5.

	-- We now only set settings for the Debug configuration
	filter { "configurations:Debug" }
		-- We want debug symbols in our debug config
		symbols "On"

	-- We now only set settings for Release
	filter { "configurations:Release" }
		-- Release should be optimized
		optimize "On"

	-- Reset the filter for other settings
	filter { }

	-- Here we use some "tokens" (the things between %{ ... }). They will be replaced by Premake
	-- automatically when configuring the projects.
	-- * %{prj.name} will be replaced by "ExampleLib" / "App" / "UnitTests"
	--  * %{cfg.longname} will be replaced by "Debug" or "Release" depending on the configuration
	-- The path is relative to *this* folder
	targetdir ("build/bin/%{prj.name}/%{cfg.longname}")
	objdir ("build/obj/%{prj.name}/%{cfg.longname}")
   


function includeDocTests()
	includedirs "Libraries/DocTests"
end

function includeLibmorton()
	includedirs "Libraries/libmorton/include"
end

project "Instumentor"
	kind "StaticLib"
	files
	{
		"Libraries/Instrumentor/**"
	}
function useInstumentorLib()
	includedirs "Libraries/Instrumentor/"
	links "Instumentor"
	includeLibmorton()
end
	

project "Chunk"
	kind "StaticLib"

	files
	{
		"Projects/Chunk/Chunk/**"
	}

	includeLibmorton()


function useChunkLib()
	includedirs "Projects/Chunk/Chunk"
	links "Chunk"
	includeLibmorton()
end



project "Chunk_Tests"
	kind "ConsoleApp"

	files 
	{
		"Projects/Chunk/Chunk_Tests/**"
	}

	includeDocTests()
	useChunkLib()

	postbuildcommands { 
		"../build/bin/%{prj.name}/%{cfg.longname}/%{prj.name}"
	}


project "PointCloudExport"
	kind "StaticLib"

	files 
	{
		"Projects/PointCloudExport/PointCloudExport/**"
	}

	useChunkLib()

function usePointCloudExportLib()
	includedirs "Projects/PointCloudExport/PointCloudExport"
	links "PointCloudExport"
	useChunkLib()
end

project "PointCloudExport_Tests"
	kind "ConsoleApp"

	files 
	{
		"Projects/PointCloudExport/PointCloudExport_Tests/**"
	}

	usePointCloudExportLib()
	includeDocTests()
	
	postbuildcommands { 
		"../build/bin/%{prj.name}/%{cfg.longname}/%{prj.name}"
	}
