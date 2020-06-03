project "GLSL Shader Includes"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    files {
        "GLSL-Shader-Includes/*.h"
    }
