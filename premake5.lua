workspace "ProjectAlpha"
	architecture "x86_64"
	startproject "Game"

	configurations { "Debug", "Release" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines { "PA_PLATFORM_WINDOWS" }

	filter "configurations:Debug"
		defines "PA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PA_RELEASE"
		optimize "On"
	filter {}

OUTPUT_DIR = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

-- ============================================ SFML ============================================
function includeSFML()
	includedirs { "Externals/SFML/Include/" }
end

function linkSFML()
	-- Use all lib-files within the Reslease or Debug folders depending on the configuration.
	libdirs "Externals/SFML/Lib/%{cfg.buildcfg}"

	-- If windows, link with opengl32
	filter "system:windows"
		links { "opengl32" }

	-- If not windows (Linux), link with GL
	filter "system:not windows"
		links { "GL" }
	
		
	-- SFML links
	filter "configurations:Debug"
		links { "sfml-system-s-d", "sfml-window-s-d", "sfml-graphics-s-d", "sfml-audio-s-d", "sfml-network-s-d", "sfml-main-d", "winmm", "gdi32" }
	filter "configurations:Release"
		links { "sfml-system-s", "sfml-window-s", "sfml-graphics-s", "sfml-audio-s", "sfml-network-s", "sfml-main", "winmm", "gdi32" }

	filter {} -- Reset the filters for other settings.
end
-- ==============================================================================================

-- =========================================== SPDLOG ===========================================

function includeSpdlog()
	includedirs { "Externals/SPDLOG/Include" }
end

function useSpdlog()
	includeSpdlog()

	filter "configurations:Debug"
		libdirs "Externals/SPDLOG/Lib/Debug/spdlogd.lib"

	filter "configurations:Release"
		libdirs "Externals/SPDLOG/Lib/Release/spdlog.lib"
	
	filter {}
end

-- ==============================================================================================

-- ============================================ MISC ============================================
function addFiles()
	files
	{
		"Projects/%{prj.name}/src/**.h",
		"Projects/%{prj.name}/src/**.hpp",
		"Projects/%{prj.name}/src/**.cpp"
	}
end

function setTargetAndObjDirs()
	targetdir ("Build/Bin/" .. OUTPUT_DIR .. "/%{prj.name}")
	objdir ("Build/Obj/" .. OUTPUT_DIR .. "/%{prj.name}")
end
-- ==============================================================================================

function useEngine()
	includeSFML()
	-- Include all projects (This should be changed to something else?)
	includedirs { "Projects/" }
	-- Link to the Engine Project and to SFML.
	links "Engine"
	linkSFML()
	includeSpdlog()
end

-- ========================================== PROJECTS ==========================================
project "Game"
	location "Projects/Game"
	filter "configurations:Release"
		kind "WindowedApp"
	filter "configurations:Debug"
		kind "ConsoleApp"
	filter {}
	
	language "C++"

	setTargetAndObjDirs()

	addFiles()

	useEngine()

	defines "SFML_STATIC"
	
	filter {}

project "Engine"
	location "Projects/Engine"
	kind "StaticLib"
	language "C++"

	setTargetAndObjDirs()

	addFiles()
	
	includeSFML()
	defines "SFML_STATIC"

	useSpdlog()

	filter {}
-- ==============================================================================================
