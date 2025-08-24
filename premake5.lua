package.path = package.path .. ";./Code/_Premake/?.lua"
require "SmartArguments"

workspace "ZEngine"
	location "Solution"
	architecture "x86_64"
	configurations { "Debug" }
	dependson { "ZERO_CHECK" }
	language "C++"
	cppdialect "C++20"
	buildoptions { "/Zc:__cplusplus" }
	platforms { "x64" }
	startproject "Game"
	inheritdependencies "On"

	targetdir "%{wks.location}/_Build/%{prj.name}/%{cfg.buildcfg}_%{cfg.platform}/"
	objdir "%{wks.location}/_Intermediate/%{prj.name}/%{cfg.buildcfg}_%{cfg.platform}/"
	debugdir "%{wks.location}/_Build/%{prj.name}/%{cfg.buildcfg}_%{cfg.platform}/"

	defines { "_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING", "_SILENCE_CXX20_CISO646_REMOVED_WARNING" }
	disablewarnings { "26812" }

	filter "Debug*"
		defines { "_DEBUG", "Z_DEBUG", "USE_OPTICK", "ASSERTS_ENABLED", "LOGGING_ENABLED" }
		flags { "FatalCompileWarnings" }
		optimize "Off"
		runtime "Debug"
		symbols "On"
	filter {} -- disable the filter

	files 
	{ 
		"%{wks.location}/../Code/%{prj.name}/*.natvis",
		"%{wks.location}/../Code/%{prj.name}/premake5.*",
		"%{wks.location}/../Code/%{prj.name}/Resource/**.*",
		"%{wks.location}/../Code/%{prj.name}/%{prj.name}/**.h",
		"%{wks.location}/../Code/%{prj.name}/%{prj.name}/**.cpp",
		"%{wks.location}/../Code/%{prj.name}/%{prj.name}/**.inl",
		"%{wks.location}/../Code/Application/%{prj.name}/*.natvis",
		"%{wks.location}/../Code/Application/%{prj.name}/premake5.*",
		"%{wks.location}/../Code/Application/%{prj.name}/%{prj.name}/**.h",
		"%{wks.location}/../Code/Application/%{prj.name}/%{prj.name}/**.cpp",
		"%{wks.location}/../Code/Application/%{prj.name}/%{prj.name}/**.inl",
		"%{wks.location}/../Code/Framework/%{prj.name}/*.natvis",
		"%{wks.location}/../Code/Framework/%{prj.name}/premake5.*",
		"%{wks.location}/../Code/Framework/%{prj.name}/%{prj.name}/**.h",
		"%{wks.location}/../Code/Framework/%{prj.name}/%{prj.name}/**.cpp",
		"%{wks.location}/../Code/Framework/%{prj.name}/%{prj.name}/**.inl",
	}

	vpaths 
	{ 
		{ ["./"] = { "**premake5.lua", "**.natvis" } },
	}

	-- projects
	group "Application"
		include "Code/Application/Game/premake5.lua"
	group "Framework"
		include "Code/Framework/Core/premake5.lua"
		include "Code/Framework/ECS/premake5.lua"
		include "Code/Framework/Engine/premake5.lua"
		include "Code/Framework/Input/premake5.lua"
		include "Code/Framework/Math/premake5.lua"
	group ""

project "ZERO_CHECK"
	kind "ConsoleApp"
	language "C++"
	location "%{wks.location}/ZERO_CHECK"
	files { "%{wks.location}/../premake5.lua" }

	-- we must run change to the batch file directory to run it
	buildcommands { "cd %{wks.location}..\\ & call generate.bat" }
	-- by setting a build output that doesn't exist it will always run
	buildoutputs { "unused.txt" }
