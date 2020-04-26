project "GLM"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    includedirs {
        "glm/"
    }

    files {
        "glm/glm/**"
    }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "Off"

        defines {
            "_GLM_X11"
        }

    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"

        defines {
            "_GLM_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"