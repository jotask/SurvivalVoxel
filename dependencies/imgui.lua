project "ImGui"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    includedirs {
        "imgui/",
        "imgui/examples/",
        "glad/include",
        "glfw/include/"
    }

    files {
        "imgui/*.cpp",
        "imgui/examples/imgui_impl_glfw.cpp",
        "imgui/examples/imgui_impl_opengl3.cpp"
    }

    defines {
        "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    }

    filter "system:linux"
        pic "On"

        systemversion "latest"
        staticruntime "Off"

        defines {
            "_IMGUI_X11"
        }

    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"

        defines {
            "_IMGUI_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"