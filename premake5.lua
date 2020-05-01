workspace "SurvivalVoxelGame"
    location "build"
    configurations {
        "Debug",
        "Release"
    }

    startproject "SurvivalVoxel"

    flags {
        "MultiProcessorCompile"
    }

    filter "configurations:Debug"
        defines {
            "DEBUG",
            "DEBUG_SHADER"
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "RELEASE"
        }
        optimize "Speed"
        flags {
            "LinkTimeOptimization"
        }

project "SurvivalVoxel"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "build/bin/%{cfg.buildcfg}"
    objdir "build/obj/%{cfg.buildcfg}"

    includedirs {
        "src/",
        "dependencies/glad/include/",
        "dependencies/glfw/include/",
        "dependencies/glm/",
        "dependencies/imgui/",
        "dependencies/imgui/examples",
        "dependencies/soil2/src/SOIL2",
        "dependencies/PerlinNoise/"
    }

    files {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
    }

    links {
        "GLFW",
        "GLM",
        "GLAD",
        "ImGui",
        "Soil2"
    }

    filter "system:linux"
        links {
            "dl",
            "pthread"
        }

        defines {
            "_X11"
        }

    filter "system:windows"
        defines {
            "_WINDOWS"
        }

include "dependencies/glfw.lua"
include "dependencies/glad.lua"
include "dependencies/glm.lua"
include "dependencies/imgui.lua"
include "dependencies/soil2.lua"