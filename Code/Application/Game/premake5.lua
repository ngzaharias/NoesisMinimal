project "Game"
	kind "ConsoleApp"
	pchheader "GamePCH.h"
	pchsource "Game/GamePCH.cpp"
	location "%{wks.location}/Application/Game"

	files 
	{ 
		"%{wks.location}/../Code/Application/Game/*.natvis",
		"%{wks.location}/../Code/Application/Game/premake5.*",
		"%{wks.location}/../Code/Application/Game/Game/**.h",
		"%{wks.location}/../Code/Application/Game/Game/**.cpp",
		"%{wks.location}/../Code/Application/Game/Game/**.inl",
	}

	vpaths 
	{ 
		{ ["Source/*"] = {  
			"Game/**.h", 
			"Game/**.cpp", 
			"Game/**.inl" } },
	}

	includedirs 
	{ 
		"%{wks.location}/../3rdParty/",
		"%{wks.location}/../3rdParty/glew/2.1.0/Include/",
		"%{wks.location}/../3rdParty/glfw/3.3.4/Include/",
		"%{wks.location}/../3rdParty/magic_enum/0.8.0/Include/",
		"%{wks.location}/../3rdParty/NoesisGUI/3.2.8-Indie/Include/",
		"%{wks.location}/../3rdParty/optick/1.3.1/Include/",
		"%{wks.location}/../Code/Application/Game/",
		"%{wks.location}/../Code/Framework/Core/",
		"%{wks.location}/../Code/Framework/ECS/",
		"%{wks.location}/../Code/Framework/Engine/",
		"%{wks.location}/../Code/Framework/Input/",
		"%{wks.location}/../Code/Framework/Math/",
	}

	libdirs 
	{
		"%{wks.location}/../3rdParty/",
		"%{wks.location}/../3rdParty/glew/2.1.0/Library/",
		"%{wks.location}/../3rdParty/glfw/3.3.4/Library/",
		"%{wks.location}/../3rdParty/NoesisGUI/3.2.8-Indie/Library/",
		"%{wks.location}/../3rdParty/optick/1.3.1/Library/",
	}

	links 
	{ 
		"Core",
		"ECS",
		"Engine",
		"Math",

		"glew32.lib",
		"glfw3.lib",
		"Noesis.lib",
		"NoesisApp.lib",
		"OptickCore.lib",

		"Dbghelp.lib",
		"flac.lib",
		"gdi32.lib",
		"ogg.lib",
		"openal32.lib",
		"opengl32.lib",
		"vorbis.lib",
		"vorbisenc.lib",
		"vorbisfile.lib",
		"winmm.lib",
		"ws2_32.lib",
		"winmm.lib",
	}

	filter { "kind:*App" }
		postbuildcommands 
		{ 
			"{COPY} %{wks.location}/../3rdParty/*.dll $(OutDir)",
			"{COPY} %{wks.location}/../3rdParty/glew/2.1.0/Binary/*.dll $(OutDir)",
			"{COPY} %{wks.location}/../3rdParty/NoesisGUI/3.2.8-Indie/Binary/*.dll $(OutDir)",
			"{COPY} %{wks.location}/../3rdParty/optick/1.3.1/Binary/*.dll $(OutDir)",
		}
	filter {} -- disable the filter
