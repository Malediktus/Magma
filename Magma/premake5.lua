project "Magma"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	-- pchheader "src/Magma/Core/pch.h"
	-- pchsource "src/Magma/Core/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	defines
	{
		-- "_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"src"
	}

	links
	{
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MG_DIST"
		runtime "Release"
		optimize "on"