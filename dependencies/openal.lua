project "OpenAl"
    kind "StaticLib"
    language "C"
    architecture "x86_64"

    targetdir "../build/bin/%{cfg.buildcfg}"
    objdir "../build/obj/%{cfg.buildcfg}"

    defines {
        "AL_BUILD_LIBRARY",
        "AL_ALEXT_PROTOTYPES",
    }

    files {
        "openal-soft/include/**",
        "openal-soft/al/**",
        "openal-soft/alc/*",
        "openal-soft/alc/backends/base.*",
        "openal-soft/alc/effects/*",
        "openal-soft/alc/filters/*",
        "openal-soft/alc/mixer/*",
        "openal-soft/common/*",
    }

    includedirs {
        "configurations/openal",
        "openal-soft/include",
        "openal-soft/common",
        "openal-soft/",
        "openal-soft/alc",
    }

    disablewarnings {
        "5030",
        "4065",
        "4307",
    }

    filter "system:windows"
        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "NOMINMAX",
        }

        files {
            "openal-soft/alc/backends/dsound.*",
            "openal-soft/alc/backends/loopback.*",
            "openal-soft/alc/backends/null.*",
            "openal-soft/alc/backends/wasapi.*",
            "openal-soft/alc/backends/wave.*",
            "openal-soft/alc/backends/winmm.*",
        }

        removefiles {
            "openal-soft/alc/mixer/mixer_neon.cpp",
        }
