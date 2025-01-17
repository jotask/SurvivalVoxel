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

    defines {
        "AL_LIBTYPE_STATIC"
    }

    includedirs {
        "src/",
        "dependencies/glad/include/",
        "dependencies/glfw/include/",
        "dependencies/glm/",
        "dependencies/imgui/",
        "dependencies/imgui/examples",
        "dependencies/soil2/src/SOIL2",
        "dependencies/PerlinNoise/",
        "dependencies/bullet3/src",
        "dependencies/assimp/include",
        "dependencies/assimp/config/",
        "dependencies/GLSL-Shader-Includes/",
        "dependencies/jsoncpp/include",
        "dependencies/spdlog/include",
        "dependencies/openal-soft/include",
        "dependencies/gainput/lib/include"
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
        "Soil2",
        "Bullet3",
        "assimp",
        "Jsoncpp",
        "SpdLog",
        "OpenAl",
        "Gainput"
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

group "Dependencies"
    include "dependencies/glfw.lua"
    include "dependencies/glad.lua"
    include "dependencies/glm.lua"
    include "dependencies/imgui.lua"
    include "dependencies/soil2.lua"
    include "dependencies/bullet3.lua"
    include "dependencies/assimp.lua"
    include "dependencies/jsoncpp.lua"
    include "dependencies/spdlog.lua"
    include "dependencies/openal.lua"
    include "dependencies/gainput.lua"
