project "Gainput"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    disablewarnings {
        "4267",
        "4244",
        "4996"
    }

    files {
        "gainput/lib/source/**.h",
        "gainput/lib/source/**.cpp"
    }

    includedirs {
        "gainput/lib/include"
    }
