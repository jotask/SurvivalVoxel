project "Soil2"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    files {
        "soil2/src/SOIL2/*.c"
    }

    filter { "system:windows" }
        links { "OpenGL32" }

    filter { "system:not windows" }
        links { "GL" }

    filter "action:vs*"
        -- buildoptions { "/TC" }
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "action:not vs*"
        language "C"
        buildoptions { "-Wall" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"
        targetname "soil2-debug"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"
        targetname "soil2"

    filter "system:macosx"
        defines { "GL_SILENCE_DEPRECATION" }