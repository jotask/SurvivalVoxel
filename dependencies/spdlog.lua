project "SpdLog"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    defines {
        "SPDLOG_COMPILED_LIB"
    }

    files {
        "spdlog/src/*.cpp"
    }

    includedirs {
        "spdlog/include"
    }
