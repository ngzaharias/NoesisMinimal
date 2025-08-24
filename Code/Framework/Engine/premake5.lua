project "Engine"
	kind "StaticLib"
	pchheader "EnginePCH.h"
	pchsource "Engine/EnginePCH.cpp"
	location "%{wks.location}/Framework/Engine"

	vpaths 
	{ 
		{ ["Source/*"] = {  
			"Engine/**.h", 
			"Engine/**.cpp", 
			"Engine/**.inl" } },
	}

	includedirs 
	{ 
		"%{wks.location}/../3rdParty/",
		"%{wks.location}/../3rdParty/glew/2.1.0/Include/",
		"%{wks.location}/../3rdParty/glfw/3.3.4/Include/",
		"%{wks.location}/../3rdParty/magic_enum/0.8.0/Include/",
		"%{wks.location}/../3rdParty/NoesisGUI/3.2.8-Indie/Include/",
		"%{wks.location}/../3rdParty/optick/1.3.1/Include/",
		"%{wks.location}/../Code/Framework/Core/",
		"%{wks.location}/../Code/Framework/ECS/",
		"%{wks.location}/../Code/Framework/Engine/",
		"%{wks.location}/../Code/Framework/Input/",
		"%{wks.location}/../Code/Framework/Math/",
	}

	links 
	{ 
		"Core", 
		"Math", 
	}