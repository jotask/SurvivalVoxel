project "Jsoncpp"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    files {
        "jsoncpp/src/lib_json/*.h",
        "jsoncpp/src/lib_json/*.cpp",
        "jsoncpp/src/lib_json/*.inl"
    }

    includedirs {
        "jsoncpp/include"
    }
